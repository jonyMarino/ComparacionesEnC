/*
 ******************************
 * Pager implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: pager.c,v 1.8 2005/12/14 18:35:05 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/ooc/lib/page.h>
#include <ooc/ooc/lib/pager.h>
#include <ooc/utils/thread.h>

/*
 * -------------------
 * Block/Pager layouts
 * -------------------
 */

struct block {
  struct block *next;
  struct block *prev;
  struct block *next_free;
  struct block *prev_free;
  struct page  *first_free;
  unsigned      page_cnt;
};

struct pager {
  struct block *first_block;
  struct block *first_free;
};

/*
 * ------
 * Dummys
 * ------
 */

static struct block block_null[1];
static struct pager pager[1];

ooc_threadMutex(pager_mutex);

/*
 * -------------------
 * Block/Pager helpers
 * -------------------
 */

static inline void
block_init(struct block *block)
{
  struct page *first = ooc_page_get
    ((char*)block + sizeof(struct block) + OOC_POOL_PAGESIZE-1);
  char          *end = (char*)block + OOC_POOL_PAGECHUNK * OOC_POOL_PAGESIZE;
  struct page  *curr = first;
  struct page  *next = (struct page *)((char*)curr + OOC_POOL_PAGESIZE);
  
  while (end > (char*)next + OOC_POOL_PAGESIZE) {
    curr->block = block, curr->next = next;

    curr = next;
    next = (struct page*)((char*)curr + OOC_POOL_PAGESIZE);
  }

  curr->block = block, curr->next = 0;

  block->next       = block->prev      = 0;
  block->next_free  = block->prev_free = block;
  block->first_free = first;
  block->page_cnt   = 0;
}

static inline struct block*
pager_find_block_free(void)
{
  struct block *block = pager->first_free;
  
  if (block != block_null) {
    struct block *next = block->next_free;
  
    while (next != block) {
      next->prev_free = block->prev_free;
      block->prev_free->next_free = next;
      block->next_free = 0;

      if (next->first_free) {
	pager->first_free = next;

	return next;
      }

      block = next;
      next  = block->next_free;
    }

    block->next_free = 0;
  }
    
  return 0;
}

static inline void
pager_alloc_block(void)
{
  struct block *block = ooc_emalloc(OOC_POOL_PAGECHUNK * OOC_POOL_PAGESIZE);

  block_init(block);
      
  if (!pager->first_block)
    block->next = block->prev = block;
  else {
    struct block *first = pager->first_block;

    block->next = first;
    block->prev = first->prev;
    block->prev->next = block;
    first->prev = block;
  }
  
  pager->first_free = pager->first_block = block;
}

/*
 * --------------------
 * Pager implementation
 * --------------------
 */

struct pager*
ooc_pager_new(void)
{
  pager->first_block = 0;
  pager->first_free  = block_null;

  if (!block_null->prev_free)
    block_null->next_free = block_null->prev_free = block_null;

  OOC_DBG(("MEM: pager created"));
  
  return pager;
}

void
ooc_pager_del(void)
{
  size_t cnt = 0;

  if (pager->first_block) {
    struct block *first = pager->first_block;
    struct block  *curr = first;

    do {
      struct block *next = curr->next;

      cnt += curr->page_cnt;
      ooc_free(curr);

      curr = next;
    } while (curr != first);
  }
  
  if (cnt)
    ooc_warning("pager destroyed with %d pages", cnt);
  else
    OOC_DBG(("pager destroyed with 0 pages"));
}

struct page*
ooc_pager_alloc(void)
{
  struct block *block;
  struct page   *page;

  ooc_threadMutexLock(&pager_mutex);

  block = pager->first_free;
  page  = block->first_free;
  if (!page) {
    if (!pager_find_block_free())
      pager_alloc_block();
    
    block = pager->first_free;
    page  = block->first_free;
  }

  block->first_free = page->next;
  ++block->page_cnt;

  ooc_threadMutexUnlock(&pager_mutex);

  return page;
}

void
ooc_pager_dealloc(struct page *page)
{
  struct block *block;

  ooc_threadMutexLock(&pager_mutex);

  block = page->block;

  if (--block->page_cnt && block->next_free) {

    /* NOTE-DEV:
     * This code is executed in the following two cases:
     * - the page is not the last in the current block;
     * - the page is not the first page to be freed in the current block
     *   (equivalent with block->next_free != 0)
     */
    page->next = block->first_free;
    block->first_free = page;

    goto unlock_and_return;
  }
  
  if (!block->next_free) {
    /* add block to free blocks list */
    struct block *first = pager->first_free;

    block->next_free = first;
    block->prev_free = first->prev_free;
    block->prev_free->next_free = block;
    first->prev_free = block;
    
    block->first_free = page;
    page->next        = 0;

    goto unlock_and_return;
  }

  if (pager->first_free->next_free == pager->first_free) {
    /* last free block is never freed */
    struct page *first = block->first_free;
    
    page->next  = first->next;
    first->next = page;
    
    goto unlock_and_return;
  }
  
  /* free block */
  if (pager->first_free == block)
    pager->first_free = block->next_free;

  if (pager->first_block == block)
    pager->first_block = block->next;

  block->prev_free->next_free = block->next_free;
  block->next_free->prev_free = block->prev_free;

  block->prev->next = block->next;
  block->next->prev = block->prev;

  ooc_free(block);

 unlock_and_return:
  ooc_threadMutexUnlock(&pager_mutex);
}

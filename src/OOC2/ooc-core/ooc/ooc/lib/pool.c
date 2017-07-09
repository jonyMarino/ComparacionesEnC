/*
 ******************************
 * Pool implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: pool.c,v 1.21 2005/12/08 14:38:20 oachim Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/ooc/lib/context.h>
#include <ooc/ooc/lib/pager.h>

#include <ooc/ooc/lib/pool.h>

/*
 * ------
 * Dummys
 * ------
 */

struct page ooc_page_null[1];
struct pool ooc_pool_null[1] = {{ 0, 0, ooc_page_null, ooc_pool_null }};

/*
 * ------------
 * Pool helpers
 * ------------
 */

static inline struct page*
pool_find_page_free(struct pool *pool)
{
  struct page *page = pool->first_free;
    
  if (page != ooc_page_null) {
    struct page *next = page->next_free;
    
    while (next != page) {
      next->prev_free = page->prev_free;
      page->prev_free->next_free = next;
      page->next_free = 0;

      if (next->first_free) {
	pool->first_free = next;
	
	return next;
      }
	
      page = next;
      next = page->next_free;
    }
    
    page->next_free = 0;
  }
    
  return 0;
}

static inline void
pool_alloc_page(struct pool *pool, 
		void (*page_init)(struct page *page, struct pool *pool))
{
  struct page *page = ooc_pager_alloc();

  page_init(page, pool);

  if (!pool->first_page)
    page->next = page->prev = page;
  else {
    struct page *first = pool->first_page;

    page->next  = first;
    page->prev  = first->prev;
    page->prev->next = page;
    first->prev = page;
  }
  
  pool->first_free = pool->first_page = page;
}

static inline void
pool_del(struct pool *pool)
{
  if (pool != ooc_pool_null) {
    size_t obj_cnt = 0;
    size_t    size = pool->size;

    if (pool->first_page) {
      struct page *first = pool->first_page;
      struct page  *curr = first;
    
      do {
	struct page *next = curr->next;

	obj_cnt += curr->obj_cnt;
	ooc_pager_dealloc(curr);
      
	curr = next;
      } while (curr != first);
    }
  
    ooc_free(pool);

    if (obj_cnt)
      ooc_warning("pool(%d) destroyed with %d objects", size, obj_cnt);
    else
      OOC_DBG(("pool(%d) destroyed with 0 objects", size));
  }
}

/*
 * -------------------
 * Pool implementation
 * -------------------
 */

struct pool*
ooc_pool_new(size_t size)
{
  struct pool *pool = ooc_emalloc(sizeof(struct pool));

  pool->size       = size;
  pool->first_page = 0;
  pool->first_free = ooc_page_null;
  pool->raw        = ooc_pool_null;
  
  if (!ooc_page_null->prev_free)
    ooc_page_null->next_free = ooc_page_null->prev_free = ooc_page_null;
 
  return pool;
}

void
ooc_pool_del(struct pool *pool)
{
  pool_del(pool->raw);
  pool_del(pool);
}

void
ooc_pool_release(struct pool *pool, unsigned id)
{
  if (pool->first_page) {
    struct page *first = pool->first_page;
    struct page  *curr = first;
    size_t     obj_cnt = ooc_page_objectCnt(pool->size);

    do {
      struct page *next = curr->next;

      if (curr->tmp_cnt) {
	Object obj = ooc_page_firstObject(curr);
	size_t i;
	
	for (i = 0; i < obj_cnt; i++) {
	  if (obj->_isa) {
	    if ((obj->_cnt & ~OOC_REFCNT_MASK) == id) /* current context */
	      (ooc_delete)(obj);
	    else
	      (ooc_autorelease)(obj);                 /* new+drop+throw  */
	  
	    if (!curr->tmp_cnt)
	      break;
	  }

	  obj = (Object)((char*)obj + pool->size);
	}
      }
      
      curr = next;
    } while (curr != first);
  }
}

void
ooc_pool_releaseAll(struct pool *pool)
{
  if (pool->first_page) {
    struct page *first = pool->first_page;
    struct page  *curr = first;
    size_t     obj_cnt = ooc_page_objectCnt(pool->size);

    do {
      struct page *next = curr->next;

      if (curr->tmp_cnt) {
	Object obj = ooc_page_firstObject(curr);
	size_t i;
	
	for (i = 0; i < obj_cnt; i++) {
	  if (obj->_isa) {
	    if (obj->_cnt & OOC_ATTACH_MASK) /* current context */
	      (ooc_delete)(obj);
	    else
	      (ooc_autorelease)(obj);        /* new+drop+throw  */
	    
	    if (!curr->tmp_cnt)
	      break;
	  }

	  obj = (Object)((char*)obj + pool->size);
	}
      }
      
      curr = next;
    } while (curr != first);
  }
}

bool
ooc_pool_isObject(struct pool *pool, Object obj)
{
  if (obj->_isa && pool->first_page) {
    struct page *page = ooc_page_get(obj);

    if (ooc_page_isAligned(obj, page, pool->size)) {
      struct page *first = pool->first_page;
      struct page  *curr = first;
      
      do {
	if (curr == page)
	  break;
	
	curr = curr->next;
      } while (curr != first);
      
      return curr == page;
    }
  }

  return false;
}

/* 
 * ---------------------------
 * Raw pointer implementation
 * ---------------------------
 */

/*
 * ------------
 * Pool helpers
 * ------------
 */

static inline struct pool*
pool_rawAlloc(struct pool *pool, size_t size)
{
  if (pool == ooc_pool_null)
    pool = ooc_pool_new(size);
  
  if (pool->raw == ooc_pool_null)
    pool->raw = ooc_pool_new(size);
  
  if (!pool_find_page_free(pool->raw))
    pool_alloc_page(pool->raw, ooc_page_rawInit);

  return pool;
}

static inline void
pool_rawDealloc(struct page *page, struct page_rawCell *cell)
{
  struct pool *pool = page->pool;

  if (!page->next_free) {
    /* add page to free pages list */
    struct page *first = pool->first_free;

    page->next_free  = first;
    page->prev_free  = first->prev_free;
    page->prev_free->next_free = page;
    first->prev_free = page;

    page->first_free = (struct page_cell*)cell;
    cell->hdr.next   = 0;

    return;
  }

  if (pool->first_free->next_free == pool->first_free) {
    /* last free page is never freed */
    struct page_rawCell *first = (struct page_rawCell*)page->first_free;
    
    cell->hdr.next  = first->hdr.next;
    first->hdr.next = cell;
    
    return;
  }
  
  /* free page */
  if (pool->first_free == page)
    pool->first_free = page->next_free;
  
  if (pool->first_page == page)	
    pool->first_page = page->next;
  
  page->prev_free->next_free = page->next_free;
  page->next_free->prev_free = page->prev_free;
  
  page->prev->next = page->next;
  page->next->prev = page->prev;
  
  ooc_pager_dealloc(page);
}

/*
 * -------------------
 * Pool implementation
 * -------------------
 */

void*
ooc_pool_rawAlloc(size_t unrounded_size)
{
  struct pool        **pool = ooc_contextGet()->allocator->pool;
  size_t               size = (unrounded_size + OOC_ALLOCATOR_SIZE_MASK) & 
                              ~OOC_ALLOCATOR_SIZE_MASK;
  size_t               slot = OOC_ALLOCATOR_SLOT(size);
  struct page         *page = pool[slot]->raw->first_free;
  struct page_rawCell *cell = (struct page_rawCell*)page->first_free;
  
  if (!cell) {
    pool[slot] = pool_rawAlloc(pool[slot], size);
    page       = pool[slot]->raw->first_free;
    cell       = (struct page_rawCell*)page->first_free;
  }
  
  page->first_free = (struct page_cell*)cell->hdr.next;
  ++page->obj_cnt;
  
  cell->hdr.dealloc_srv = ooc_pool_rawDealloc;

  return ooc_page_rawGetPtr(cell);
}

void
ooc_pool_rawDealloc(void *ptr)
{
  struct page_rawCell *cell = ooc_page_rawGetCell(ptr);
  struct page         *page = ooc_page_get(cell);

  if (--page->obj_cnt && page->next_free) {

    /* NOTE-DEV:
     * This code is executed in the following two cases:
     * - the memory chunk is not the last in the current page;
     * - the memory chunk is not the first object to be freed in the 
     *   current page (equivalent with page->next_free != 0)
     */
 
    cell->hdr.next   = (struct page_rawCell*)page->first_free;
    page->first_free = (struct page_cell   *)cell;
  } else
    pool_rawDealloc(page, cell);
}

bool
ooc_pool_rawIsAllocated(struct pool *pool_obj, void *ptr)
{
  struct pool *pool = pool_obj->raw;

  if (pool->first_page) {
    struct page_rawCell *cell = ooc_page_rawGetCell(ptr);
    struct page         *page = ooc_page_get(cell);
    
    if (ooc_page_isAligned(cell, page, pool->size)) {
      struct page *first = pool->first_page;
      struct page *curr  = first;

      do {
	if (curr == page) {
	  struct page_rawCell *curr_cell = 
	    (struct page_rawCell*)page->first_free;

	  while (curr_cell) {
	    if (curr_cell == cell)
	      break;
	    
	    curr_cell = curr_cell->hdr.next;
	  }

	  return curr_cell == 0;
	}
	
	curr = curr->next;
      } while (curr != first);
    }
  }

  return false;
}

/* 
 * -------------------
 * Object sub-services
 * -------------------
 */

struct pool*
ooc_pool_alloc(struct pool *pool, size_t size)
{
  if (pool == ooc_pool_null)
    pool = ooc_pool_new(size);

  if (!pool_find_page_free(pool))
    pool_alloc_page(pool, ooc_page_init);

  return pool;
}

void
ooc_pool_dealloc(struct page *page, struct page_cell *cell)
{
  struct pool *pool = page->pool;

  if (!page->next_free) {
    /* add page to free pages list */
    struct page *first = pool->first_free;

    page->next_free  = first;
    page->prev_free  = first->prev_free;
    page->prev_free->next_free = page;
    first->prev_free = page;

    page->first_free = cell;
    cell->next       = 0;

    return;
  }

  if (pool->first_free->next_free == pool->first_free) {
    /* last free page is never freed */
    struct page_cell *first = page->first_free;
    
    cell->next  = first->next;
    first->next = cell;
    
    return;
  }

  /* free page */
  if (pool->first_free == page)
    pool->first_free = page->next_free;

  if (pool->first_page == page)	
    pool->first_page = page->next;

  page->prev_free->next_free = page->next_free;
  page->next_free->prev_free = page->prev_free;

  page->prev->next = page->next;
  page->next->prev = page->prev;

  ooc_pager_dealloc(page);
}

/* 
 * -------------------
 * Statistics services
 * -------------------
 */

struct pool_statistics
ooc_pool_statistics(struct pool *pool)
{
  struct pool_statistics stats = { 0, 0 };

  if (pool->first_page) {
    struct page *first = pool->first_page;
    struct page  *curr = first;
  
    do {
      stats.obj_cnt += curr->obj_cnt;
      stats.page_cnt++;
      
      curr = curr->next;
    } while (curr != first);
  }

  return stats;
}

size_t
ooc_pool_classObjectCnt(struct pool *pool, constClass cls)
{
  size_t obj_cnt = 0;

  if (pool->first_page) {
    struct page *first = pool->first_page;
    struct page  *curr = first;
    size_t   total_cnt = ooc_page_objectCnt(pool->size);
  
    do {
      if (curr->obj_cnt) {
	Object obj = ooc_page_firstObject(curr);
	size_t i;
	
	for (i = 0; i < total_cnt; i++) {
	  if ((Class)obj->_isa == cls)
	    ++obj_cnt;

	  obj = (Object)((char*)obj + pool->size);
	}
      }

      curr = curr->next;
    } while (curr != first);
  }
  
  return obj_cnt;
}

/*
 * ---------------------
 * Multi-thread services
 * ---------------------
 */

#if OOC_THREAD_USE

static inline void
pool_merge(struct pool *pool, struct pool *other)
{
  if (!other->first_page)
    return;

  if (!pool->first_page) {
    pool->first_page = other->first_page;
    pool->first_free = other->first_free;
  } else {
    struct page *end       = pool->first_page->prev;
    struct page *other_end = other->first_page->prev;
    
    struct page *end_free       = pool->first_free->prev;
    struct page *other_end_free = other->first_free->prev;
    
    end->next               = other->first_page;
    other_end->next         = pool->first_page;
    pool->first_page->prev  = other_end;
    other->first_page->prev = end;
    
    end_free->next_free          = other->first_free;
    other_end_free->next_free    = pool->first_free;
    pool->first_free->prev_free  = other_end_free;
    other->first_free->prev_free = end_free;
  }
  
  other->first_page = 0;
  other->first_free = ooc_page_null;
}

struct pool*
ooc_pool_merge(struct pool *pool, struct pool *other)
{
  if (other != ooc_pool_null) {
    if (pool == ooc_pool_null)
      pool = ooc_pool_new(other->size);
    
    pool_merge(pool     , other     );
    pool_merge(pool->raw, other->raw);
  }
    
  return pool;
}

#endif

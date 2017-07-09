/*
 ******************************
 * Page interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: page.c,v 1.2 2005/12/06 17:10:25 oachim Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/ooc/lib/pool.h>

#include <ooc/ooc/lib/page.h>

void
ooc_page_init(struct page *page, struct pool *pool)
{
  struct page_cell *first = ooc_page_firstObject(page);
  struct page_cell  *curr = first;
  size_t i,       obj_cnt = ooc_page_objectCnt(pool->size);

  for (i = 0; i < obj_cnt - 1; i++) {
    struct page_cell *next = (struct page_cell*)((char*)curr + pool->size);

    curr->isa  = 0;
    curr->next = next;

    curr = next;
  }

  curr->isa = 0, curr->next = 0;
  
  page->pool       = pool;
  page->next       = page->prev      = 0;
  page->next_free  = page->prev_free = page;
  page->first_free = first;
  page->obj_cnt    = 0;
  page->tmp_cnt    = 0;
}

void
ooc_page_rawInit(struct page *page, struct pool *pool)
{
  struct page_rawCell *first = ooc_page_firstObject(page);
  struct page_rawCell  *curr = first;
  size_t i,          chk_cnt = ooc_page_objectCnt(pool->size);

  for (i = 0; i < chk_cnt - 1; i++) {
    struct page_rawCell *next = (struct page_rawCell*)((char*)curr+pool->size);

    curr->hdr.next = next;

    curr = next;
  }

  curr->hdr.next = 0;
  
  page->pool       = pool;
  page->next       = page->prev      = 0;
  page->next_free  = page->prev_free = page;
  page->first_free = (struct page_cell*)first;
  page->obj_cnt    = 0;
  page->tmp_cnt    = 0;
}

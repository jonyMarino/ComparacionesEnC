/*
 ******************************
 * Pool Services implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: pool_srv.c,v 1.11 2006/11/27 16:59:38 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/ooc/lib/context.h>
#include <ooc/ooc/lib/allocator.h>
#include <ooc/ooc/lib/page.h>

#include <ooc/ooc/lib/pool.h>

/*
 * --------------------
 * Objects services
 * --------------------
 */

static Object
obj_alloc(classObject cls)
{
  struct allocator *alloc = ooc_contextGet()->allocator;
  struct pool      **pool = alloc->pool;
  size_t             size = ooc_classInstanceSize(cls);
  size_t             slot = OOC_ALLOCATOR_SLOT(size);
  struct page       *page = pool[slot]->first_free;
  struct page_cell  *cell = page->first_free;
  Object obj;

  if (!cell) {
    pool[slot] = ooc_pool_alloc(pool[slot], size);
    page       = pool[slot]->first_free;
    cell       = page->first_free;
  }
  
  obj = (Object)cell;

  page->first_free = cell->next;
  ++page->obj_cnt, ++page->tmp_cnt;
  
  OOC_CONST_CAST(classObject, obj->_isa) = cls;
  OOC_CONST_CAST(unsigned   , obj->_cnt) = alloc->id;

  return obj;
}

static void
obj_dealloc(Object obj)
{
  struct page *page = ooc_page_get(obj);

  if (obj->_cnt)
    --page->tmp_cnt;
  
  OOC_CONST_CAST(classObject, obj->_isa) = 0;

  if (--page->obj_cnt && page->next_free) {
    struct page_cell *cell = (struct page_cell*)obj;

    /* NOTE-DEV:
     * This code is executed in the following two cases:
     * - the object is not the last in the current page;
     * - the object is not the first object to be freed in the current page
     *   (equivalent with page->next_free != 0)
     */
    cell->next = page->first_free; 
    page->first_free = cell;

  } else
    ooc_pool_dealloc(page, (struct page_cell*)obj);
}

static void
obj_detach(Object obj)
{
  struct page *page = ooc_page_get(obj);

  --page->tmp_cnt; 
}

/*
 * --------------------
 * Pool public services
 * --------------------
 */

struct ooc_memsrv ooc_memStdSrv[1] = {{
  obj_alloc,
  obj_dealloc,
  obj_detach
}};

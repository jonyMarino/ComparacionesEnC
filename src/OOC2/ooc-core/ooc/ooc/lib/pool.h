#ifndef OOC_OOC_LIB_POOL_H
#define OOC_OOC_LIB_POOL_H

/*
 ******************************
 * Pool interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: pool.h,v 1.13 2005/12/08 14:38:21 oachim Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/Object.h>
#include <ooc/ooc/lib/page.h>

/*
 * --------------
 * Pool iterface
 * --------------
 */

/* NOTE-DEV:
 * Use a simple segregated fit algorithm to implementation fast allocation.
 */

struct pool *ooc_pool_new           (size_t size);
void         ooc_pool_del           (struct pool *pool);
void         ooc_pool_release       (struct pool *pool, unsigned id);
void         ooc_pool_releaseAll    (struct pool *pool);
bool         ooc_pool_isObject      (struct pool *pool, Object  obj);

/* Raw Pointers Interface */
void        *ooc_pool_rawAlloc      (size_t size);
void         ooc_pool_rawDealloc    (void   *ptr);
bool         ooc_pool_rawIsAllocated(struct pool *pool, void *ptr);


/* Objects sub-services */
struct pool* ooc_pool_alloc         (struct pool *pool, size_t size);
void         ooc_pool_dealloc       (struct page *page,
				     struct page_cell *cell);
/* Statistics services */
struct pool_statistics {
  size_t obj_cnt;
  size_t page_cnt;
};

struct pool_statistics ooc_pool_statistics    (struct pool *pool);
size_t                 ooc_pool_classObjectCnt(struct pool *pool, 
					       constClass    cls);

/* Multi-thread services */
#if OOC_THREAD_USE
struct pool *ooc_pool_merge(struct pool *pool, struct pool *other_pool);
#endif

/*
 * -----------
 * Pool layout
 * -----------
 */

struct pool {
  size_t       size;
  struct page *first_page;
  struct page *first_free;
  struct pool *raw;
};

/*
 * ----------
 * Dummy pool
 * ----------
 */

extern struct pool ooc_pool_null[1];

#endif /* OOC_OOC_LIB_POOL_H */

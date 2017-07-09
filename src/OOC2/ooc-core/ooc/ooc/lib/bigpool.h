#ifndef OOC_OOC_LIB_BIGPOOL_H
#define OOC_OOC_LIB_BIGPOOL_H

/*
 ******************************
 * Big Pool implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: bigpool.h,v 1.10 2005/12/08 14:38:20 oachim Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/Object.h>
#include <ooc/ooc/lib/bigpage.h>

/*
 * --------------
 * Pool iterface
 * --------------
 */

struct bigpool *ooc_bigpool_new           (void);
void            ooc_bigpool_del           (struct bigpool *pool);
void            ooc_bigpool_release       (struct bigpool *pool, unsigned id);
void            ooc_bigpool_releaseAll    (struct bigpool *pool);
bool            ooc_bigpool_isObject      (struct bigpool *pool, Object  obj);

/* Raw Pointers Interface */
void*           ooc_bigpool_rawAlloc      (size_t size);
void            ooc_bigpool_rawDealloc    (void   *ptr);
bool            ooc_bigpool_rawIsAllocated(struct bigpool *pool, void *ptr);

/* Statistics */
size_t          ooc_bigpool_objectCnt     (struct bigpool *pool, size_t size);
size_t          ooc_bigpool_classObjectCnt(struct bigpool *pool, 
					   constClass       cls);

/* Objects sub-services */
struct bigpool *ooc_bigpool_alloc         (struct bigpool *pool, size_t size);
void            ooc_bigpool_dealloc       (struct bigpage *page);

/* 
 * ----------------------
 * Multi-thread interface 
 * ----------------------
 */

#if OOC_THREAD_USE

struct bigpool *ooc_bigpool_merge(struct bigpool *pool, struct bigpool *other);

#endif

/*
 * -------------------
 * Pool Data Structure
 * -------------------
 */

struct bigpool {
  struct bigpage *first_page;
  struct bigpool *raw;
};

extern struct bigpool ooc_bigpool_null[1];

#endif /* OOC_OOC_LIB_BIGPOOL_H */

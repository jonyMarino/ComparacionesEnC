#ifndef OOC_OOC_LIB_ALLOCATOR_H
#define OOC_OOC_LIB_ALLOCATOR_H

/*
 ******************************
 * Allocator interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: allocator.h,v 1.9 2005/12/08 14:38:20 oachim Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

/*
 * --------------------
 * Allocator parameters
 * --------------------
 */

#define OOC_ALLOCATOR_BIN         sizeof(void*)
#define OOC_ALLOCATOR_SLOT(size) (size/OOC_ALLOCATOR_BIN)
#define OOC_ALLOCATOR_SIZE_MASK  (OOC_ALLOCATOR_BIN-1)

/*
 * ------------------
 * Allocator services
 * ------------------
 */

/* Standard services */
struct allocator *
       ooc_allocator_new       (void);
void   ooc_allocator_del       (struct allocator *alloc);

/* Find services */
bool   ooc_allocator_findObject(struct allocator *alloc, Object obj);
bool   ooc_allocator_findPtr   (struct allocator *alloc, void  *ptr);

/* Special services */
void   ooc_allocator_release   (struct allocator *alloc);
void   ooc_allocator_releaseAll(struct allocator *alloc);

/* Debug services */
size_t ooc_allocator_objectCnt     (struct allocator *alloc, size_t    size);
size_t ooc_allocator_classObjectCnt(struct allocator *alloc, constClass cls);

/* Multi-thread services */
#if OOC_THREAD_USE

void   ooc_allocator_merge(struct allocator *alloc, struct allocator *other);
#endif

/*
 * ----------------
 * Allocator layout
 * ----------------
 */

struct allocator {
  struct pool   **pool;
  struct bigpool *bigpool;
  unsigned        id;
};

#endif /* OOC_OOC_LIB_ALLOCATOR_H */

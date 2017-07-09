/*
 ******************************
 * Allocator implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: allocator.c,v 1.14 2005/12/08 14:38:20 oachim Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/ooc/lib/pool.h>
#include <ooc/ooc/lib/bigpool.h>

#include <ooc/ooc/lib/allocator.h>

/*
 * ------------------------
 * Allocator implementation
 * ------------------------
 */

#define ALLOC_SLOTS (OOC_PAGE_MAX_CHUNKSIZE/OOC_ALLOCATOR_BIN+1)

struct allocator*
ooc_allocator_new(void)
{
  struct allocator *alloc = ooc_emalloc(sizeof(struct allocator));
  
#if !OOC_GC_USE
  alloc->pool = ooc_emalloc(ALLOC_SLOTS * sizeof(struct pool*));

  { size_t i;
    
    for (i = 0; i < ALLOC_SLOTS; i++)
      alloc->pool[i] = ooc_pool_null;
  }
#endif
  
  alloc->bigpool = ooc_bigpool_null;

  OOC_DBG(("MEM: allocator created"));

  return alloc;
}

void
ooc_allocator_del(struct allocator *alloc)
{
  ooc_bigpool_del(alloc->bigpool);

#if !OOC_GC_USE
  { size_t i;
  
    for (i = 0; i < ALLOC_SLOTS; i++)
      ooc_pool_del(alloc->pool[i]);
    
    ooc_free(alloc->pool);
  }
#endif

  ooc_free(alloc);

  OOC_DBG(("MEM: allocator destroyed"));
}

/* Find services */
bool
ooc_allocator_findObject(struct allocator *alloc, Object obj)
{
#if !OOC_GC_USE
  size_t i;
    
  for (i = 0; i < ALLOC_SLOTS; i++)
    if (ooc_pool_isObject(alloc->pool[i], obj))
      return true;
#endif
  
  return ooc_bigpool_isObject(alloc->bigpool, obj);
}

bool
ooc_allocator_findPtr(struct allocator *alloc, void *ptr)
{
#if !OOC_GC_USE
  size_t i;
    
  for (i = 0; i < ALLOC_SLOTS; i++)
    if (ooc_pool_rawIsAllocated(alloc->pool[i], ptr))
      return true;
#endif
  
  return ooc_bigpool_rawIsAllocated(alloc->bigpool, ptr);
}

/* Special services */
void
ooc_allocator_release(struct allocator *alloc)
{
#if !OOC_GC_USE
  size_t i;
    
  for (i = 0; i < ALLOC_SLOTS; i++)
    ooc_pool_release(alloc->pool[i], alloc->id);
#endif
  
  ooc_bigpool_release(alloc->bigpool, alloc->id);
}

void
ooc_allocator_releaseAll(struct allocator *alloc)
{
#if !OOC_GC_USE
  size_t i;
    
  for (i = 0; i < ALLOC_SLOTS; i++)
    ooc_pool_releaseAll(alloc->pool[i]);
#endif
  
  ooc_bigpool_releaseAll(alloc->bigpool);
}

/* Statistics services */
size_t
ooc_allocator_objectCnt(struct allocator *alloc, size_t size)
{
#if !OOC_GC_USE
  size_t slot = OOC_ALLOCATOR_SLOT(size);

  if (slot < ALLOC_SLOTS)
    return ooc_pool_statistics(alloc->pool[slot]).obj_cnt;
#endif

  return ooc_bigpool_objectCnt(alloc->bigpool, size);
}

size_t
ooc_allocator_classObjectCnt(struct allocator *alloc, constClass cls)
{
#if !OOC_GC_USE
  size_t slot = OOC_ALLOCATOR_SLOT(ooc_classInstanceSize(cls));

  if (slot < ALLOC_SLOTS)
    return ooc_pool_classObjectCnt(alloc->pool[slot], cls);
#endif

  return ooc_bigpool_classObjectCnt(alloc->bigpool, cls);
}

/* Multi-thread services */
#if OOC_THREAD_USE

void
ooc_allocator_merge(struct allocator *alloc, struct allocator *other)
{
#if !OOC_GC_USE
  size_t i;
  
  for (i = 0; i < ALLOC_SLOTS; i++)
    alloc->pool[i] = ooc_pool_merge(alloc->pool[i], other->pool[i]);
#endif

  alloc->bigpool = ooc_bigpool_merge(alloc->bigpool, other->bigpool);

  OOC_DBG(("MEM: allocators merged"));
}

#endif /* OOC_THREAD_USE */

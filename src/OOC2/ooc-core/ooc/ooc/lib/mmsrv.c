/*
 ******************************
 * Memory module implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: mmsrv.c,v 1.6 2005/12/08 14:38:20 oachim Exp $
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
#include <ooc/ooc/lib/pool.h>
#include <ooc/ooc/lib/bigpool.h>

/* Object services */
bool
ooc_memIsObject(Object obj)
{
  struct allocator *alloc = ooc_contextGet()->allocator;

  if (ooc_allocator_findObject(alloc, obj))
    return true;

#if OOC_THREAD_USE
  alloc = ooc_contextGetGlobalAllocator();

  if (alloc && ooc_allocator_findObject(alloc, obj))
    return true;
#endif
  
  return false;
}

/* Raw pointer services */
void*
ooc_memAlloc(size_t size)
{
  return ooc_page_rawFitSize(size)
    ? ooc_pool_rawAlloc(size)
    : ooc_bigpool_rawAlloc(size);
}

void
ooc_memFree(void *ptr)
{
  struct page_rawCell *cell = ooc_page_rawGetCell(ptr);

  cell->hdr.dealloc_srv(ptr);
}

bool
ooc_memIsAllocated(void *ptr)
{
  struct allocator *alloc = ooc_contextGet()->allocator;

  if (ooc_allocator_findPtr(alloc, ptr))
    return true;

#if OOC_THREAD_USE
  alloc = ooc_contextGetGlobalAllocator();

  if (alloc && ooc_allocator_findPtr(alloc, ptr))
    return true;
#endif
  
  return false;
}

/* Statistics services */
size_t
ooc_memObjectCnt(size_t size)
{
  struct allocator *alloc = ooc_contextGet()->allocator;
  size_t obj_cnt = ooc_allocator_objectCnt(alloc, size);

#if OOC_THREAD_USE
  alloc = ooc_contextGetGlobalAllocator();

  if (alloc)
    obj_cnt += ooc_allocator_objectCnt(alloc, size);
#endif

  return obj_cnt;
}

size_t
ooc_memClassObjectCnt(constClass cls)
{
  struct allocator *alloc = ooc_contextGet()->allocator;
  size_t obj_cnt = ooc_allocator_classObjectCnt(alloc, cls);

#if OOC_THREAD_USE
  alloc = ooc_contextGetGlobalAllocator();

  if (alloc)
    obj_cnt += ooc_allocator_classObjectCnt(alloc, cls);
#endif

  return obj_cnt;
}

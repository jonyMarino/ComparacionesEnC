/*
 ******************************
 * Alloc implementation
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: alloc.c,v 1.6 2005/11/16 17:59:08 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/ex/ExBadAlloc.h>

#include <string.h>

/*
 * Global implementation
 */

#if OOC_GC_USE /* GC */

#include OOC_GC_HDR

void* (*ooc_malloc  )(size_t)        = GC_malloc;
void* (*ooc_rawalloc)(size_t)        = GC_malloc_atomic;
void* (*ooc_realloc )(void*, size_t) = GC_realloc;
void  (*ooc_free    )(void*)         = GC_free;

#else          /* LIBC */

#include <stdlib.h>

void* (*ooc_malloc  )(size_t)        = malloc;
void* (*ooc_rawalloc)(size_t)        = malloc;
void* (*ooc_realloc )(void*, size_t) = realloc;
void  (*ooc_free    )(void*)         = free;

#endif

void*
(ooc_emalloc)(size_t size, const char *file, int line)
{
  void *ptr = ooc_malloc(size);

  if (!ptr)
    throwLoc(new(ExBadAlloc), file, line);

  return ptr;
}

void*
(ooc_erawalloc)(size_t size, const char *file, int line)
{
  void *ptr = ooc_rawalloc(size);

  if (!ptr)
    throwLoc(new(ExBadAlloc), file, line);

  return ptr;
}

void*
(ooc_erealloc)(void *ptr, size_t size, const char *file, int line)
{
  ptr = ooc_realloc(ptr, size);

  if (!ptr)
    throwLoc(new(ExBadAlloc), file, line);

  return ptr;
}

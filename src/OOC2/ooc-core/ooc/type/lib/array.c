/*
 ******************************
 * Raw Array implementation
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: array.c,v 1.4 2005/11/16 17:59:08 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/assert.h>
#include <ooc/utils/memint.h>
#include <ooc/ex/ExBadRange.h>
#include <ooc/ex/ExOverflow.h>

#include <string.h>

#define OOC_TYPE_ARRAY_C
#define array_T

#include <ooc/type/array_t.h>

typedef struct {
  size_t cnt;
} *T; 

/*
 * -------------------------------
 *  Array implementation
 * -------------------------------
 */

#define B(p) ((T)((char*)(p) - hsize))

static inline size_t
ceil_size(size_t size)
{
  return size + sizeof(int) - size%sizeof(int);
}

/* globals */

void*
ooc_array_new_ (size_t cnt, size_t esize, size_t hsize, bool ex)
{
  size_t size = ceil_size(cnt*esize);
  T self;

  ooc_assert(hsize % sizeof(int) == 0);

  if (cnt > 1 && (size < cnt || size < esize)) {
    if (ex)
      throw(new(ExOverflow));
    else
      return 0;
  }

  if (ex)
    self = ooc_emalloc(hsize + size);
  else
    self = ooc_malloc (hsize + size);
  
  if (self) {
    self->cnt = cnt;
    self = (T)((char*)self + hsize);
  }
  
  return self;
}

void*
ooc_array_cpy_(void *dst_, const void *src_, size_t esize, size_t hsize)
{
  T src = B(src_);
  T dst = B(dst_);

  ooc_assert(dst->cnt == src->cnt);

  ooc_memint_copy((int*)dst_, (int*)src_,
		  ceil_size(dst->cnt*esize)/sizeof(int));

  return dst_;
}

void*
ooc_array_rawcpy_(void* dst_, const void* src, size_t esize, size_t hsize, size_t cnt)
{
  T dst = B(dst_);

  ooc_assert(dst->cnt == cnt);

  return memcpy(dst_, src, cnt*esize);
}

void*
ooc_array_dup_(const void *src_, size_t esize, size_t hsize)
{
  T src = B(src_);
  T dst_ = ooc_array_new_(src->cnt, esize, hsize, true);
  
  ooc_memint_copy((int*)dst_, (int*)src_,
		  ceil_size(src->cnt*esize)/sizeof(int));
  
  return dst_;
}

void*
ooc_array_rawdup_(const void* src, size_t esize, size_t hsize, size_t cnt)
{
  T dst_ = ooc_array_new_(cnt, esize, hsize, true);
  
  return memcpy(dst_, src, cnt*esize);
}

void*
ooc_array_resize_ (void *self_, size_t cnt, size_t esize, size_t hsize, bool ex)
{
  size_t size = ceil_size(cnt*esize);
  T self = B(self_);

  if (ceil_size(self->cnt*esize) == size)
    return self_;

  if (cnt > 1 && (size < cnt || size < esize)) {
    if (ex)
      throw(new(ExOverflow));
    else
      return 0;
  }

  if (ex)
    self = ooc_erealloc(self, hsize + size);
  else
    self = ooc_realloc (self, hsize + size);

  if (self) {
    self->cnt = cnt;
    self = (T)((char*)self + hsize);
  }
   
  return self;
}

void
ooc_array_badrng_(const char *file, int line)
{
  throwLoc(new(ExBadRange), file, line);
}

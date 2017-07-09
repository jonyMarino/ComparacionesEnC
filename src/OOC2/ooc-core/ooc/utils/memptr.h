#ifndef OOC_UTILS_MEMPTR_H
#define OOC_UTILS_MEMPTR_H

/*
 *******************************
 * Pointer memory block interface
 * -----
 * Object Oriented C progamming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: memptr.h,v 1.3 2005/08/26 16:50:04 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

/* NOTE-USER: fast set, copy and swap
 * Fast set/copy/swap of pointer array using Duff's device optimization.
 *
 * Useful to process memory blocks with pointer alignment and size
 * multiple of sizeof(void*).
 */

static inline
void
ooc_memptr_set(void* *restrict dst, void* val, size_t cnt)
{
  size_t rem = cnt % 8;
  cnt = (cnt / 8) + 1;

  switch (rem)
    do {  *dst++ = val;
  case 7: *dst++ = val;
  case 6: *dst++ = val;
  case 5: *dst++ = val;
  case 4: *dst++ = val;
  case 3: *dst++ = val;
  case 2: *dst++ = val;
  case 1: *dst++ = val;
  case 0: ;
    } while(--cnt);
}

static inline
void
ooc_memptr_copy(void* *restrict dst, const void* *restrict src, size_t cnt)
{
  size_t rem = cnt % 8;
  cnt = (cnt / 8) + 1;

  switch (rem)
    do {  *dst++ = *src++;
  case 7: *dst++ = *src++;
  case 6: *dst++ = *src++;
  case 5: *dst++ = *src++;
  case 4: *dst++ = *src++;
  case 3: *dst++ = *src++;
  case 2: *dst++ = *src++;
  case 1: *dst++ = *src++;
  case 0: ;
    } while(--cnt);
}

static inline
void
ooc_memptr_swap(void* *restrict dst, void* *restrict src, size_t cnt)
{
  size_t rem = cnt % 8;
  cnt = (cnt / 8) + 1;

  switch (rem)
    do {  void *tmp;
          tmp = *dst, *dst++ = *src, *src++ = tmp;
  case 7: tmp = *dst, *dst++ = *src, *src++ = tmp;
  case 6: tmp = *dst, *dst++ = *src, *src++ = tmp;
  case 5: tmp = *dst, *dst++ = *src, *src++ = tmp;
  case 4: tmp = *dst, *dst++ = *src, *src++ = tmp;
  case 3: tmp = *dst, *dst++ = *src, *src++ = tmp;
  case 2: tmp = *dst, *dst++ = *src, *src++ = tmp;
  case 1: tmp = *dst, *dst++ = *src, *src++ = tmp;
  case 0: ;
    } while(--cnt);
}

static inline
void
ooc_memptr_rcopy(void* *restrict dst,
		 const void* *restrict src, size_t cnt)
{
  size_t rem = cnt % 8;
  src += cnt;
  dst += cnt;
  cnt = (cnt / 8) + 1;

  switch (rem)
    do {  *--dst = *--src;
  case 7: *--dst = *--src;
  case 6: *--dst = *--src;
  case 5: *--dst = *--src;
  case 4: *--dst = *--src;
  case 3: *--dst = *--src;
  case 2: *--dst = *--src;
  case 1: *--dst = *--src;
  case 0: ;
    } while(--cnt);
}

static inline
void
ooc_memptr_rswap(void* *restrict dst, void* *restrict src, size_t cnt)
{
  size_t rem = cnt % 8;
  src += cnt;
  dst += cnt;
  cnt = (cnt / 8) + 1;

  switch (rem)
    do {  void *tmp;
          tmp = *dst, *--dst = *src, *--src = tmp;
  case 7: tmp = *dst, *--dst = *src, *--src = tmp;
  case 6: tmp = *dst, *--dst = *src, *--src = tmp;
  case 5: tmp = *dst, *--dst = *src, *--src = tmp;
  case 4: tmp = *dst, *--dst = *src, *--src = tmp;
  case 3: tmp = *dst, *--dst = *src, *--src = tmp;
  case 2: tmp = *dst, *--dst = *src, *--src = tmp;
  case 1: tmp = *dst, *--dst = *src, *--src = tmp;
  case 0: ;
    } while(--cnt);
}

#endif

#ifndef OOC_UTILS_MEMCHR_H
#define OOC_UTILS_MEMCHR_H

/*
 *******************************
 * Char memory block interface
 * -----
 * Object Oriented C progamming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: memchr.h,v 1.3 2005/08/26 16:50:04 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

/* NOTE-USER: fast set, copy and swap
 * Fast set/copy/swap of char array using Duff's device optimization.
 *
 * Useful to process memory blocks with char alignment and size
 * multiple of sizeof(char).
 */

static inline
void
ooc_memchr_set(char *restrict dst, char val, size_t cnt)
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
ooc_memchr_copy(char *restrict dst, const char *restrict src, size_t cnt)
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
ooc_memchr_swap(char *restrict dst, char *restrict src, size_t cnt)
{
  size_t rem = cnt % 8;
  cnt = (cnt / 8) + 1;

  switch (rem)
    do {  char tmp;
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
ooc_memchr_rcopy(char *restrict dst, const char *restrict src, size_t cnt)
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
ooc_memchr_rswap(char *restrict dst, char *restrict src, size_t cnt)
{
  size_t rem = cnt % 8;
  src += cnt;
  dst += cnt;
  cnt = (cnt / 8) + 1;

  switch (rem)
    do {  char tmp;
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

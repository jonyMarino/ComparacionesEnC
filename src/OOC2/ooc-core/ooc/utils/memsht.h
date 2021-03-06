#ifndef OOC_UTILS_MEMSHT_H
#define OOC_UTILS_MEMSHT_H

/*
 *******************************
 * Short integer memory block interface
 * -----
 * Object Oriented C progamming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: memsht.h,v 1.2 2005/08/26 16:50:04 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

/* NOTE-USER: fast set, copy and swap
 * Fast set/copy/swap of short integer array using Duff's device
 * optimization.
 *
 * Useful to process memory blocks with short integer alignment and size
 * multiple of sizeof(short).
 */

static inline
void
ooc_memsht_set(short *restrict dst, short val, size_t cnt)
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
ooc_memsht_copy(short *restrict dst, const short *restrict src, size_t cnt)
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
ooc_memsht_swap(short *restrict dst, short *restrict src, size_t cnt)
{
  size_t rem = cnt % 8;
  cnt = (cnt / 8) + 1;

  switch (rem)
    do {  short tmp;
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
ooc_memsht_rcopy(short *restrict dst,
		 const short *restrict src, size_t cnt)
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
ooc_memsht_rswap(short *restrict dst, short *restrict src, size_t cnt)
{
  size_t rem = cnt % 8;
  src += cnt;
  dst += cnt;
  cnt = (cnt / 8) + 1;

  switch (rem)
    do {  short tmp;
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

#ifndef OOC_UTILS_HASH_H
#define OOC_UTILS_HASH_H

/*
 *******************************
 * Character string hash interface
 * -----
 * Object Oriented C progamming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: hash.h,v 1.1 2005/07/04 13:52:10 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

static inline
size_t
ooc_memhash(const char *str_, size_t len)
{
  const unsigned char *restrict str = (void*)str_;
  size_t h = 0;

  if (len) {
    size_t n = (len+7)/8;

    switch(len%8){
    case 0: do { h = (h*32 - h) + *str++;
    case 7:      h = (h*32 - h) + *str++;
    case 6:      h = (h*32 - h) + *str++;
    case 5:      h = (h*32 - h) + *str++;
    case 4:      h = (h*32 - h) + *str++;
    case 3:      h = (h*32 - h) + *str++;
    case 2:      h = (h*32 - h) + *str++;
    case 1:      h = (h*32 - h) + *str++;
               } while(--n > 0);
    }
  }

  return h;
}

static inline
size_t
ooc_strhash(const char *str_)
{
  const unsigned char *restrict str = (void*)str_;
  size_t h = 0;

  while (*str)
    h = (h*32 - h) + *str++;
  
  return h;
}

#define OOC_HASH_LITTERAL(str) \
        ooc_strhash((str), sizeof(str)-1)

#endif

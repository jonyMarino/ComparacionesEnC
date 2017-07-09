/*
 ******************************
 * Size Implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: size.c,v 1.1 2005/07/04 13:52:10 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <limits.h>
#include <ooc/utils/size.h>

/*
 * --------------
 *  2^n functions
 * --------------
 */

bool
ooc_size_isPow2(size_t s)
{
  return (s & ~(s+1)) == s;
}

int
ooc_size_LSBlog2(size_t s)
{
  int p;

  if (s == 0)
    return -1;

  p = 0;

#if ULONG_MAX >= 4294967296
#if ULONG_MAX >= 18446744073709551616
  if ((s & 0xfffffffffffffffful) == 0) {
    s >>= 64;
    p += 64;
  }
#endif

  if ((s & 0xfffffffful) == 0) {
    s >>= 32;
    p += 32;
  }
#endif

  if ((s & 0xfffful) == 0) {
    s >>= 16;
    p += 16;
  }

  if ((s & 0xfful) == 0) {
    s >>= 8;
    p += 8;
  }

  if ((s & 0x0ful) == 0) {
    s >>= 4;
    p += 4;
  }

  if ((s & 0x03ul) == 0) {
    s >>= 2;
    p += 2;
  }

  if ((s & 0x01ul) == 0)
    p += 1;

  return p;
}

int
ooc_size_GSBlog2(size_t s)
{
  int p = 0;

  if (s == 0)
    return -1;

#if ULONG_MAX >= 4294967296
#if ULONG_MAX >= 18446744073709551616
  if (s & ~0xfffffffffffffffful) {
    s >>= 64;
    p += 64;
  }
#endif

  if (s & ~0xfffffffful) {
    s >>= 32;
    p += 32;
  }
#endif

  if (s & ~0xfffful) {
    s >>= 16;
    p += 16;
  }

  if (s & ~0xfful) {
    s >>= 8;
    p += 8;
  }

  if (s & ~0x0ful) {
    s >>= 4;
    p += 4;
  }

  if (s & ~0x03ul) {
    s >>= 2;
    p += 2;
  }

  if (s & ~0x01ul)
    p += 1;

  return p;
}

/*
 * -----------
 *  Power of 2
 * -----------
 */

size_t
ooc_size_prevPow2(size_t s)
{
  return s <= 4 ? 4 : 1 << (ooc_size_GSBlog2(s-1));
}

size_t
ooc_size_nextPow2(size_t s)
{
  return s <= 4 ? 4 : 1 << (ooc_size_GSBlog2(s)+1);
}

/*
 * ---------------------
 *  Primes following 2^n
 * ---------------------
 */

static const size_t prime[] = {
  5ul,          13ul,         29ul,         53ul,         97ul,
  193ul,        389ul,        769ul,        1543ul,       3079ul,
  6151ul,       12289ul,      24593ul,      49157ul,      98317ul,
  196613ul,     393241ul,     786433ul,     1572869ul,    3145739ul,
  6291469ul,    12582917ul,   25165843ul,   50331653ul,   100663319ul,
  201326611ul,  402653189ul,  805306457ul,  1610612741ul, 3221225473ul,
  4294967291ul, 0ul
};

size_t
ooc_size_prevPrimeSize(size_t s)
{
  int i = 1;

  while (s > prime[i] && prime[i] != 0)
    ++i;

  return prime[i-1];
}


size_t
ooc_size_nextPrimeSize(size_t s)
{
  int i = 0;

  while (s >= prime[i] && prime[i+1] != 0)
    ++i;

  return prime[i];
}

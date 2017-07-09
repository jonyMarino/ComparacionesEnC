#ifndef OOC_UTILS_SIZE_H
#define OOC_UTILS_SIZE_H

/*
 ******************************
 * Size Interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: size.h,v 1.1 2005/07/04 13:52:10 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/Object.h>

bool   ooc_size_isPow2       (size_t s);

int    ooc_size_LSBlog2      (size_t s);
int    ooc_size_GSBlog2      (size_t s);

size_t ooc_size_prevPow2     (size_t s);
size_t ooc_size_nextPow2     (size_t s);

size_t ooc_size_prevPrimeSize(size_t s);
size_t ooc_size_nextPrimeSize(size_t s);

#endif /* OOC_UTILS_SIZE_H */

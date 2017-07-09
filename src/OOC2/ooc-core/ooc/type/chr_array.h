#ifndef OOC_TYPE_CHR_ARRAY_T_H
#define OOC_TYPE_CHR_ARRAY_T_H

/*
 *******************************
 * Char array type interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: chr_array.h,v 1.1 2005/07/04 13:52:09 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#define array_T      char
#define array_PREFIX chr
#include <ooc/type/array_t.h>

#define array_T      signed char
#define array_PREFIX schr
#include <ooc/type/array_t.h>

#define array_T      unsigned char
#define array_PREFIX uchr
#include <ooc/type/array_t.h>

#endif /* OOC_TYPE_CHR_ARRAY_T_H */

#ifndef OOC_TYPE_LLNG_ARRAY_T_H
#define OOC_TYPE_LLNG_ARRAY_T_H

/*
 *******************************
 * Long long integer array type interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: llng_array.h,v 1.2 2005/11/16 12:33:50 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#include <ooc/type/llong.h>

#define array_T      ooc_llong
#define array_PREFIX llng
#include <ooc/type/array_t.h>

#define array_T      ooc_ullong
#define array_PREFIX ullng
#include <ooc/type/array_t.h>

#endif /* OOC_TYPE_LLNG_ARRAY_T_H */

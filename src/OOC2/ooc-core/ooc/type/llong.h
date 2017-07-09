#ifndef OOC_TYPE_LLONG_T_H
#define OOC_TYPE_LLONG_T_H

/*
 *******************************
 * Long long type interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: llong.h,v 1.1 2005/11/16 12:33:50 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#if defined(LLONG_MAX) || defined(LONG_LONG_MAX) || defined(OOC_GNU_C)

#define OOC_LLONG 1
typedef          long long int ooc_llong;
typedef unsigned long long int ooc_ullong;

#elif LONG_MAX == 2147483647

#define OOC_LLONG 0
typedef struct {          long int _[2]; } ooc_llong;
typedef struct { unsigned long int _[2]; } ooc_ullong;

#elif LONG_MAX >= 9223372036854775807

#define OOC_LLONG 1
typedef          long int ooc_llong;
typedef unsigned long int ooc_ullong;

#else
  #error "libooc: (unsigned) long long int type not supported"
#endif

#endif /* OOC_TYPE_LLONG_T_H */

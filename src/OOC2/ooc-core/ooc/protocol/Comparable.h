#ifndef OOC_PROTOCOL_COMPARABLE_H
#define OOC_PROTOCOL_COMPARABLE_H

/*
 ******************************
 * Comparable interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Comparable.h,v 1.1 2005/07/04 13:52:06 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/Object.h>

#include ooc_Interface

#define PROTOCOL Comparable

#define PROTODEF_Comparable				\
        PROTODEF_Protocol				\
 ooc_constMethod0(size_t, hash)				\
 ooc_constMethod1(bool  , equal  , constTYPE obj)	\
 ooc_constMethod1(int   , compare, constTYPE obj)

#include ooc_End

#endif /* OOC_PROTOCOL_COMPARABLE_H */

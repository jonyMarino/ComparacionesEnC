#ifndef OOC_PROTOCOL_COPIABLE_H
#define OOC_PROTOCOL_COPIABLE_H

/*
 ******************************
 * Copiable interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Copiable.h,v 1.1 2005/07/04 13:52:06 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/Object.h>

#include ooc_Interface

#define PROTOCOL Copiable

#define PROTODEF_Copiable			\
        PROTODEF_Protocol			\
  ooc_method1(void, copy, constTYPE)		\
  ooc_method1(void, swap, TYPE)

#include ooc_End

#endif /* OOC_PROTOCOL_COPIABLE_H */

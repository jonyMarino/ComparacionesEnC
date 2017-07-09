#ifndef OOC_TYPE_NUMBER_H
#define OOC_TYPE_NUMBER_H

/*
 *******************************
 * Number abstract interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Number.h,v 1.4 2005/12/20 15:17:20 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#ifndef OOC_TYPE_BASICTYPE_H
#include <ooc/type/BasicType.h>
#endif

#include <ooc/protocol/Copiable.h>
#include <ooc/protocol/Comparable.h>

#include ooc_Interface

#define ABSTRACT_CLASS Number
#define SUPER_CLASS BasicType

#define CLASSDEF_Number				\
        CLASSDEF_BasicType			\
        PROTODEF(Comparable)			\
        PROTODEF(Copiable)

#include ooc_End

#endif /* OOC_TYPE_NUMBER_H */

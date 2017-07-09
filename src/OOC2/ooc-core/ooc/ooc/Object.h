#ifndef OOC_OOC_OBJECT_H
#define OOC_OOC_OBJECT_H

#ifndef OOC_OBJECT_H
#error "libooc: use ooc/Object.h instead of ooc/ooc/Object.h directly"
#endif

/*
 *******************************
 * Object interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Object.h,v 1.4 2005/12/14 18:35:05 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

/*
 * -------------------------
 *  Object interface
 *  Root of all OOC objects
 * -------------------------
 */

#include ooc_Interface

#define ABSTRACT_CLASS Object

#define CLASSDEF_Object	\
        /* must be empty */

#include ooc_End

#endif /* OOC_OOC_OBJECT_H */

#ifndef OOC_OOC_METACLASS_H
#define OOC_OOC_METACLASS_H

#ifndef OOC_OBJECT_H
#error "libooc: use ooc/Object.h instead of ooc/ooc/MetaClass.h directly"
#endif

/*
 *******************************
 * MetaClass interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: MetaClass.h,v 1.3 2006/11/27 16:59:38 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

/*
 * -------------------------
 *  MetaClass interface
 *  Root of all OOC MetaClasses
 * -------------------------
 */

#include ooc_Interface

#define ABSTRACT_METACLASS MetaClass
#define ROOT_CLASS Class

#define CLASSDEF_MetaClass			\
        CLASSDEF_Class				\
  ooc_visible(classObject, root)

#define CLASSINIT_MetaClass			\
        CLASSINIT_Class				\
        (void*)ooc_classDesc(ROOT_CLASS),

#include ooc_End

#endif /* OOC_OOC_METACLASS_H */

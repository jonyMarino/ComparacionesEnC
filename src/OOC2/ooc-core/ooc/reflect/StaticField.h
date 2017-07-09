#ifndef OOC_REFLECT_STATICFIELD_H
#define OOC_REFLECT_STATICFIELD_H

/*
 *******************************
 * StaticField interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: StaticField.h,v 1.5 2005/12/20 15:17:19 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#include <ooc/reflect/Field.h>
#include <ooc/reflect/staticmeta.h>

#include ooc_Interface

#define FINAL_CLASS StaticField
#define SUPER_CLASS Field

#define CLASSDEF_StaticField					\
        CLASSDEF_Field						\
								\
  ooc_method2(TYPE, initWith, constClass cls,			\
                              struct ooc_meta_fld *meta)	\
								\
        StaticField_PRIVATE_DEF	

#ifndef StaticField_PRIVATE_DEF
#define StaticField_PRIVATE_DEF
#endif

#include ooc_End

#endif /* OOC_REFLECT_STATICFIELD_H */

#ifndef OOC_REFLECT_STATICMETHOD_H
#define OOC_REFLECT_STATICMETHOD_H

/*
 *******************************
 * StaticMethod interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: StaticMethod.h,v 1.7 2005/12/20 15:17:19 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#include <ooc/reflect/Method.h>
#include <ooc/reflect/staticmeta.h>

#include ooc_Interface

#define FINAL_CLASS StaticMethod
#define SUPER_CLASS Method

#define CLASSDEF_StaticMethod						 \
        CLASSDEF_Method							 \
									 \
  ooc_method2(TYPE, initWith, constClass cls, struct ooc_meta_mth *meta) \
									 \
        StaticMethod_PRIVATE_DEF	

#ifndef StaticMethod_PRIVATE_DEF
#define StaticMethod_PRIVATE_DEF
#endif

#include ooc_End

#endif /* OOC_REFLECT_STATICMETHOD_H */

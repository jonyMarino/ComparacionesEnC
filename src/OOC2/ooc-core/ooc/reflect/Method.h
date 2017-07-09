#ifndef OOC_REFLECT_METHOD_H
#define OOC_REFLECT_METHOD_H

/*
 *******************************
 * Method interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Method.h,v 1.5 2005/12/20 15:17:19 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#include <ooc/Object.h>
#include <ooc/type/Type.h>

#include ooc_Interface

#define ABSTRACT_CLASS Method

#define CLASSDEF_Method						\
 ooc_constMethod0(const char*, getName     )			\
 ooc_constMethod0(constClass , getClass    )			\
 ooc_constMethod0(int        , getQualifier)			\
 ooc_constMethod0(constType  , getRtnType  )			\
 ooc_constMethod0(size_t     , getRtnSize  )			\
 ooc_constMethod0(size_t     , getParamCnt )			\
 ooc_constMethod1(constType  , getParamType, size_t idx)	\
 ooc_constMethod1(size_t     , getParamSize, size_t idx)	\
								\
 ooc_constMethod1(Object     , invoke, Object args[])

#include ooc_End

/* NOTE-USER: method type and qualifier 

Method type summary:
 see <ooc/type/type.h> and <ooc/type/stdType.h>

Method qualifier:
 'W' method
 'R' constMethod
 'S' staticMethod

*/

#endif /* OOC_REFLECT_METHOD_H */

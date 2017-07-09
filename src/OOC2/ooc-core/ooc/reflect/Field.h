#ifndef OOC_REFLECT_FIELD_H
#define OOC_REFLECT_FIELD_H

/*
 *******************************
 * Field interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Field.h,v 1.7 2005/12/20 15:17:19 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#include <ooc/Object.h>
#include <ooc/type/Type.h>
#include <ooc/type/llong.h>
#include <ooc/type/complex.h>

#include ooc_Interface

#define ABSTRACT_CLASS Field

#define CLASSDEF_Field						\
 ooc_constMethod0(const char*, getName     )			\
 ooc_constMethod0(constClass , getClass    )			\
 ooc_constMethod0(int        , getQualifier)			\
 ooc_constMethod0(constType  , getType     )			\
 ooc_constMethod0(size_t     , getSize     )			\
 ooc_constMethod0(size_t     , getCnt      )			\
								\
								\
 ooc_constMethod1(constObject , get     , constObject obj)	\
 ooc_constMethod1(bool        , getBool , constObject obj)	\
 ooc_constMethod1(int         , getChr  , constObject obj)	\
 ooc_constMethod1(int         , getInt  , constObject obj)	\
 ooc_constMethod1(long        , getLng  , constObject obj)	\
 ooc_constMethod1(ooc_llong   , getLLng , constObject obj)	\
 ooc_constMethod1(float       , getFlt  , constObject obj)	\
 ooc_constMethod1(double      , getDbl  , constObject obj)	\
 ooc_constMethod1(long double , getLDbl , constObject obj)	\
 ooc_constMethod1(ooc_complex , getCpx  , constObject obj)	\
 ooc_constMethod1(void*       , getPtr  , constObject obj)	\
 ooc_constMethod1(ooc_function, getFct  , constObject obj)	\
								\
								\
 ooc_constMethod2(void, set     , Object obj, Object       val)	\
 ooc_constMethod2(void, setBool , Object obj, bool         val)	\
 ooc_constMethod2(void, setChr  , Object obj, int          val)	\
 ooc_constMethod2(void, setInt  , Object obj, int          val)	\
 ooc_constMethod2(void, setLng  , Object obj, long         val)	\
 ooc_constMethod2(void, setLLng , Object obj, ooc_llong    val)	\
 ooc_constMethod2(void, setFlt  , Object obj, float        val)	\
 ooc_constMethod2(void, setDbl  , Object obj, double       val)	\
 ooc_constMethod2(void, setLDbl , Object obj, long double  val)	\
 ooc_constMethod2(void, setCpx  , Object obj, ooc_complex  val)	\
 ooc_constMethod2(void, setPtr  , Object obj, void*        ptr)	\
 ooc_constMethod2(void, setFct  , Object obj, ooc_function fct)	\
								\
								\
 ooc_constMethod2(void, getByRef , constObject obj,  void* dst)	\
 ooc_constMethod2(void, setByRef , Object obj, const void* src)

#include ooc_End

/* NOTE-USER: field type and qualifier summary

Field type summary:
 see <ooc/type/type.h> and <ooc/type/stdType.h>
 getTypeChr also returns some extra types:
 'o' an object (shortcut from Type).
 '[' an array (a reference).
 '(' a function pointer.

Field qualifier:
 'W' public
 'R' visible
 'P' private

Field reference:
  getByRef and setByRef use 'copy by reference' to manipulate field
  content and therefore allow to manipulate any field types as raw memory,
  including unknown types (i.e. typedef, struct, union and enum).
*/

#endif /* OOC_REFLECT_FIELD_H */

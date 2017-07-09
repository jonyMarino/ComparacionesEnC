#ifndef OOC_TYPE_CLOSURE_H
#define OOC_TYPE_CLOSURE_H

/*
 ******************************
 * Closure interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Closure.h,v 1.6 2005/12/20 15:17:20 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <stdarg.h>
#include <ooc/Object.h>

#include ooc_Interface

#define CLASS Closure

#define CLASSDEF_Closure						 \
									 \
      ooc_visible (ooc_closure, fct    )				 \
      ooc_visible (size_t     , obj_cnt)				 \
      ooc_visibleN(Object     , obj     , [Closure_maxObj])		 \
									 \
       ooc_method2(TYPE , initWith      , ooc_closure fct, Object obj[]) \
       ooc_method2(TYPE , initWithVA    , ooc_closure fct, ...         ) \
       ooc_method2(TYPE , initWithVAList, ooc_closure fct, va_list va  ) \
									 \
  ooc_constMethod1(Object, invoke       , Object args[])

enum { Closure_maxObj = 10 };

#include ooc_End

/* NOTE-USER:
 - Array of objects must be 0 terminated.
 - va list must be (Object)0 terminated.

 - initWithXXX process only the first Closure_maxObj objects of obj[]
   or va_list.

 - init throws eNotSupported
*/

#endif /* OOC_TYPE_CLOSURE_H */

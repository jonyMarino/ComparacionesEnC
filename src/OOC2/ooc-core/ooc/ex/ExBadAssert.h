#ifndef OOC_EX_EXBADASSERT_H
#define OOC_EX_EXBADASSERT_H

/*
 ******************************
 * ExBadAssert interface
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: ExBadAssert.h,v 1.2 2005/12/20 15:17:18 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/ex/Exception.h>

#include ooc_Interface

#define CLASS ExBadAssert
#define SUPER_CLASS Exception

#define CLASSDEF_ExBadAssert				\
        CLASSDEF_Exception				\
							\
 ooc_visible(const char*, str)				\
							\
 ooc_method1(TYPE, initWithStr, const char *str)

#include ooc_End

#endif /* OOC_EX_EXBADASSERT_H */

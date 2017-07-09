#ifndef OOC_EX_EXTESTASSERT_H
#define OOC_EX_EXTESTASSERT_H

/*
 ******************************
 * ExTestAssert interface
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: ExTestAssert.h,v 1.4 2005/12/20 15:17:18 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/ex/ExBadAssert.h>

#include ooc_Interface

#define CLASS ExTestAssert
#define SUPER_CLASS ExBadAssert

#define CLASSDEF_ExTestAssert			\
        CLASSDEF_ExBadAssert	

#include ooc_End

#endif /* OOC_EX_ExTESTASSERT_H */

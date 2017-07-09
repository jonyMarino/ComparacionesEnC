#ifndef OOC_EX_EXBADALLOC_H
#define OOC_EX_EXBADALLOC_H

/*
 ******************************
 * ExBadAlloc interface
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: ExBadAlloc.h,v 1.4 2005/12/20 15:17:18 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/ex/Exception.h>

#include ooc_Interface

#define CLASS ExBadAlloc
#define SUPER_CLASS Exception

#define CLASSDEF_ExBadAlloc			\
        CLASSDEF_Exception	

#include ooc_End

#endif /* OOC_EX_EXBADALLOC_H */

#ifndef OOC_EX_EXNOTFOUND_H
#define OOC_EX_EXNOTFOUND_H

/*
 ******************************
 * ExNotFound interface
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: ExNotFound.h,v 1.4 2005/12/20 15:17:18 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/ex/Exception.h>

#include ooc_Interface

#define CLASS ExNotFound
#define SUPER_CLASS Exception

#define CLASSDEF_ExNotFound			\
        CLASSDEF_Exception	

#include ooc_End

#endif /* OOC_EX_EXNOTFOUND_H */

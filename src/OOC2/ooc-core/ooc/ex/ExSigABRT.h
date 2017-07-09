#ifndef OOC_EX_EXSIGABRT_H
#define OOC_EX_EXSIGABRT_H

/*
 ******************************
 * Abort signal interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: ExSigABRT.h,v 1.4 2005/12/20 15:17:18 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

/* NOTE-USER: Warning: uncaught exception quits using abort()

   This is the default behavior of the exception termination handler
   and may cause infinite loops if this signal is trapped. You should
   either not trap this signal or set a user-defined exception
   termination handler which must quit in a different way (e.g. using
   exit()).
*/

#include <ooc/ex/ExSignal.h>

#include ooc_Interface

#define FINAL_CLASS ExSigABRT
#define SUPER_CLASS ExSignal

#define CLASSDEF_ExSigABRT			\
        CLASSDEF_ExSignal	

#include ooc_End

#endif /* OOC_EX_EXSIGABRT_H */

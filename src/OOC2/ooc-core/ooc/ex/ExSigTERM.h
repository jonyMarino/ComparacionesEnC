#ifndef OOC_EX_EXSIGTERM_H
#define OOC_EX_EXSIGTERM_H

/*
 ******************************
 * Termination signal interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: ExSigTERM.h,v 1.4 2005/12/20 15:17:18 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/ex/ExSignal.h>

#include ooc_Interface

#define FINAL_CLASS ExSigTERM
#define SUPER_CLASS ExSignal

#define CLASSDEF_ExSigTERM			\
        CLASSDEF_ExSignal	

#include ooc_End

#endif /* OOC_EX_EXSIGTERM_H */

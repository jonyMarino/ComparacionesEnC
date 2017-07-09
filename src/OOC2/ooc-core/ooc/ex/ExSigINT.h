#ifndef OOC_EX_EXSIGINT_H
#define OOC_EX_EXSIGINT_H

/*
 ******************************
 * Interruption signal interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: ExSigINT.h,v 1.4 2005/12/20 15:17:18 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/ex/ExSignal.h>

#include ooc_Interface

#define FINAL_CLASS ExSigINT
#define SUPER_CLASS ExSignal

#define CLASSDEF_ExSigINT			\
        CLASSDEF_ExSignal	

#include ooc_End

#endif /* OOC_EX_EXSIGINT_H */

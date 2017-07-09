#ifndef OOC_TESTSUITE_MEM_BIGOBJ_H
#define OOC_TESTSUITE_MEM_BIGOBJ_H

/*
 ******************************
 * BigObj interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: BigObj.h,v 1.1 2005/10/25 12:11:34 oachim Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/Object.h>

#include ooc_Interface

#define FINAL_CLASS BigObj

#define CLASSDEF_BigObj	 \
        BigObj_PRIVATE_DEF

#ifndef BigObj_PRIVATE_DEF
#define BigObj_PRIVATE_DEF
#endif

#include ooc_End

#endif /* OOC_TESTSUITE_MEM_BIGOBJ_H */

#ifndef OOC_TESTSUITE_MEM_DUMMYOBJ_H
#define OOC_TESTSUITE_MEM_DUMMYOBJ_H

/*
 ******************************
 * DummyObj interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: DummyObj.h,v 1.1 2005/10/25 12:12:11 oachim Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/Object.h>

#include ooc_Interface

#define FINAL_CLASS DummyObj

#define CLASSDEF_DummyObj			\
						\
    ooc_public(size_t, cnt0)			\
    ooc_public(size_t, cnt1)			\
						\
        DummyObj_PRIVATE_DEF

#ifndef DummyObj_PRIVATE_DEF
#define DummyObj_PRIVATE_DEF
#endif

#include ooc_End

#endif /* OOC_TESTSUITE_MEM_DUMMYOBJ_H */

#ifndef OOC_TEST_TEST_H
#define OOC_TEST_TEST_H

/*
 ******************************
 * Test Interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Test.h,v 1.2 2005/12/20 15:17:20 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/Object.h>

#ifndef CLASSDEF_TestResult
    OOC_CLASSDECL(TestResult);
#define CLASSDECL_TestResult OOC_DONE
#endif

#include ooc_Interface

#define PROTOCOL Test

#define PROTODEF_Test						\
      ooc_method1(void       , run    , TestResult result)	\
      ooc_method1(void       , setNext, Test test)		\
 ooc_constMethod0(Test       , getNext)				\
 ooc_constMethod0(const char*, getName)

#include ooc_End

#endif /* OOC_TEST_TEST_H */

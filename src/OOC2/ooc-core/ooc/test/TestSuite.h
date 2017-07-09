#ifndef OOC_TEST_TESTSUITE_H
#define OOC_TEST_TESTSUITE_H

/*
 ******************************
 * TestSuite interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: TestSuite.h,v 1.5 2005/12/20 15:17:20 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/Object.h>
#include <ooc/test/Test.h>
#include <ooc/test/TestResult.h>

#include ooc_Interface

#define FINAL_CLASS TestSuite

#define CLASSDEF_TestSuite						\
        PROTODEF(Test)							\
									\
    ooc_method1(TYPE      , initWith     , const char *name)		\
									\
    ooc_method0(TestResult, newRun       )				\
    ooc_method1(void      , addTest      , Test test)			\
    ooc_method1(void      , addClassTest , constClass cls)		\
    ooc_method2(void      , addMethodTest, constClass cls,		\
                                           const char *mth_name)	\
									\
        TestSuite_PRIVATE_DEF	

#ifndef TestSuite_PRIVATE_DEF
#define TestSuite_PRIVATE_DEF
#endif

#include ooc_End

#endif /* OOC_TEST_TESTSUITE_H */

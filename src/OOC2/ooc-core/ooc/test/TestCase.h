#ifndef OOC_TEST_TESTCASE_H
#define OOC_TEST_TESTCASE_H

/*
 ******************************
 * TestCase interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: TestCase.h,v 1.7 2005/12/20 15:17:20 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/Object.h>
#include <ooc/test/Test.h>

#include ooc_Interface

#define ABSTRACT_CLASS TestCase

#define CLASSDEF_TestCase				\
        PROTODEF(Test)					\
							\
    ooc_method0(void  , setup   )			\
    ooc_method0(int   , runBare )			\
    ooc_method0(void  , cleanup )			\
							\
    ooc_method1(void  , setName , const char *fName)	\
							\
    ooc_visible(char* , name)				\
							\
    ooc_private(Test  , next)

#include ooc_End

/*
 * -------------------------
 *  TestCase Assert Macros
 * -------------------------
 */

#define ooc_testAssert(cond) \
  ((void)((cond) || TestCase_throwTestFailure_(#cond, __FILE__, __LINE__)))

bool TestCase_throwTestFailure_(const char *str, const char *file, int line);

#endif /* OOC_TEST_TESTCASE_H */

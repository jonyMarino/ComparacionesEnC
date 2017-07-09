#ifndef OOC_TEST_TESTRESULT_H
#define OOC_TEST_TESTRESULT_H

/*
 ******************************
 * TestResult interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: TestResult.h,v 1.7 2005/12/20 15:17:20 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/Object.h>
#include <ooc/test/Test.h>
#include <ooc/test/TestCase.h>
#include <ooc/test/TestMessage.h>

#include ooc_Interface

#define CLASS TestResult

#define CLASSDEF_TestResult						\
      ooc_method2(void, runProtected, Test test, int (*fct_test)(Test))	\
      ooc_method1(void, startTest   , Test test)			\
      ooc_method1(void, endTest     , Test test)			\
									\
      ooc_method1(void, run         , TestCase test)			\
									\
      ooc_method1(void, pushMessage , TestMessage msg)			\
      ooc_method0(void, popMessage  )					\
									\
      ooc_method0(void, print       )					\
									\
      ooc_visible(size_t     , successCnt)				\
      ooc_visible(size_t     , failCnt   )				\
      ooc_visible(size_t     , errorCnt  )				\
 ooc_constMethod0(size_t     , testCnt   )				\
 ooc_constMethod0(bool       , successful)				\
									\
      ooc_private(TestMessage, first)					\
      ooc_private(TestMessage, last )

#include ooc_End

#endif /* OOC_TEST_TESTRESULT_H */

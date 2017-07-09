#ifndef OOC_TEST_SPEEDTESTRESULT_H
#define OOC_TEST_SPEEDTESTRESULT_H

/*
 ******************************
 * SpeedTestResult interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: SpeedTestResult.h,v 1.5 2005/12/20 15:17:20 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/Object.h>
#include <ooc/test/TestResult.h>

#include ooc_Interface

#define ABSTRACT_CLASS SpeedTestResult
#define SUPER_CLASS    TestResult

#define CLASSDEF_SpeedTestResult		\
        CLASSDEF_TestResult			\
    ooc_private(size_t, repeat)			\
						\
    ooc_method1(TYPE, initWith, size_t repeat)

#include ooc_End

#endif /* OOC_TEST_SPEEDTESTRESULT_H */

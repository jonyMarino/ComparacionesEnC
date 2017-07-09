#ifndef OOC_TEST_TESTERROR_H
#define OOC_TEST_TESTERROR_H

/*
 ******************************
 * TestError interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: TestError.h,v 1.4 2005/12/20 15:17:20 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/Object.h>
#include <ooc/test/TestMessage.h>

#include ooc_Interface

#define FINAL_CLASS TestError
#define SUPER_CLASS TestMessage

#define CLASSDEF_TestError						\
        CLASSDEF_TestMessage						\
									\
    ooc_method3(TYPE, initWith, Object ex, const char *file, int line)	\
									\
    ooc_visible(const char*, file)					\
    ooc_visible(int        , line)					\
    ooc_visible(Object     , ex)

#include ooc_End

#endif /* OOC_TEST_TESTERROR_H */

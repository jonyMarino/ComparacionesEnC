#ifndef OOC_TEST_TESTSUCCESS_H
#define OOC_TEST_TESTSUCCESS_H

/*
 ******************************
 * TestSuccess interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: TestSuccess.h,v 1.4 2005/12/20 15:17:20 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/Object.h>
#include <ooc/test/TestMessage.h>

#include ooc_Interface

#define FINAL_CLASS TestSuccess
#define SUPER_CLASS TestMessage

#define CLASSDEF_TestSuccess					\
        CLASSDEF_TestMessage					\
								\
    ooc_method1(void, setIterDuration , double  duration)	\
    ooc_method1(void, setIteration    , int    iteration)	\
								\
    ooc_visible(double , iterDuration )				\
    ooc_visible(int    , iteration    )
    
#include ooc_End

#endif /* OOC_TEST_TESTSUCCESS_H */

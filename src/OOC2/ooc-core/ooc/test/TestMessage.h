#ifndef OOC_TEST_TESTMESSAGE_H
#define OOC_TEST_TESTMESSAGE_H

/*
 ******************************
 * TestMessage interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: TestMessage.h,v 1.8 2005/12/20 15:17:20 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/Object.h>
#include <time.h>

#include ooc_Interface

#define ABSTRACT_CLASS TestMessage

#define CLASSDEF_TestMessage					\
    ooc_method1(void, setTstName  , const char *name)		\
    ooc_method1(void, setMthName  , const char *name)		\
								\
    ooc_method1(void, setStartTime    , clock_t time    )	\
    ooc_method1(void, setEndTime      , clock_t time    )	\
    ooc_method1(void, setTotalDuration, double  duration)	\
								\
    ooc_visible(char*  , tstName      )				\
    ooc_visible(char*  , mthName      )				\
    ooc_visible(clock_t, startTime    )				\
    ooc_visible(clock_t, endTime      )				\
    ooc_visible(double , totalDuration)				\
								\
    ooc_private(TestMessage, next)

#include ooc_End

#endif /* OOC_TEST_TESTMESSAGE_H */

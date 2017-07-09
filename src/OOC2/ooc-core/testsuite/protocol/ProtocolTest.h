#ifndef OOC_TESTSUITE_PROTOCOL_PROTOCOLTEST_H
#define OOC_TESTSUITE_PROTOCOL_PROTOCOLTEST_H

#include <ooc/Object.h>
#include <ooc/test/TestCase.h>

#include ooc_Interface

#define FINAL_CLASS ProtocolTest
#define SUPER_CLASS TestCase

#define CLASSDEF_ProtocolTest			\
        CLASSDEF_TestCase			\
						\
     ooc_method0(Object, testCallMethod)	\
     ooc_method0(Object, testOverrideMethod)	\
						\
        ProtocolTest_PRIVATE_DEF

#ifndef ProtocolTest_PRIVATE_DEF
#define ProtocolTest_PRIVATE_DEF
#endif

#include ooc_End

#endif /* OOC_TESTSUITE_PROTOCOL_PROTOCOLTEST_H */

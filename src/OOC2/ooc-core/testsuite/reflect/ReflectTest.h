#ifndef OOC_TESTSUITE_REFLECT_REFLECTTEST_H
#define OOC_TESTSUITE_REFLECT_REFLECTTEST_H

#include <ooc/Object.h>
#include <ooc/test/TestCase.h>

#include ooc_Interface

#define FINAL_CLASS ReflectTest
#define SUPER_CLASS TestCase

/*
 * NOTE-TODO:
 * - add more types to test
 */

#define CLASSDEF_ReflectTest			\
        CLASSDEF_TestCase			\
						\
    ooc_method0(Object, testTypes           )	\
    ooc_method0(Object, testFieldAccess     )	\
    ooc_method0(Object, testFieldAccessArray)	\
    ooc_method0(Object, testMethods         )	\
    ooc_method0(Object, testInvoke          )	\
    ooc_method0(Object, testInvokeFFI       )	\
						\
    ReflectTest_PRIVATE_DEF

#ifndef ReflectTest_PRIVATE_DEF
#define ReflectTest_PRIVATE_DEF
#endif

#include ooc_End

#endif /* OOC_TESTSUITE_REFLECT_REFLECTTEST_H */

#ifndef OOC_TESTSUITE_REFLECT_CLASSTEST_H
#define OOC_TESTSUITE_REFLECT_CLASSTEST_H

#include <ooc/Object.h>

#include ooc_Interface

#define CLASS ClassTest

#define CLASSDEF_ClassTest				\
    ooc_public(int   , i)				\
    ooc_public(double, d)				\
    ooc_public(float , f)				\
    ooc_public(bool  , b)				\
    ooc_public(char  , c)				\
							\
    ooc_visible(Object, data_mth1)			\
							\
    ooc_publicN(int, array, [10])			\
							\
    ooc_method1(Object, mthd1, Object arg)		\
    ooc_method1(int   , mthd2, int i)			\
    ooc_method1(double, mthd3, double d)		\
    ooc_method1(ooc_complex, mthd4, ooc_complex c)	\
							\
    ooc_staticMethod1(int, mthd5, int i)

#include ooc_End

#endif /* OOC_TESTSUITE_REFLECT_CLASSTEST_H */

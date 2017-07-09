#ifndef OOC_TESTSUITE_MEMORY_MEMORYTEST_H
#define OOC_TESTSUITE_MEMORY_MEMORYTEST_H

#include <ooc/Object.h>
#include <ooc/test/TestCase.h>

#include ooc_Interface

#define FINAL_CLASS MemoryTest
#define SUPER_CLASS TestCase

#define CLASSDEF_MemoryTest					\
        CLASSDEF_TestCase					\
								\
  ooc_method0(Object, testAbstractPool                  )	\
								\
  ooc_method0(Object, testPoolAllocation                )	\
  ooc_method0(Object, testPoolNewRetainDeleteRelease    )	\
  ooc_method0(Object, testPoolNewRetainReleaseDelete    )	\
  ooc_method0(Object, testPoolOwn                       )	\
  ooc_method0(Object, testPoolManyObjects               )	\
								\
  ooc_method0(Object, testBigPoolAllocation             )	\
  ooc_method0(Object, testBigPoolNewRetainDeleteRelease )	\
  ooc_method0(Object, testBigPoolNewRetainReleaseDelete )	\
  ooc_method0(Object, testBigPoolOwn                    )	\
								\
  ooc_method0(Object, testProtectionSingleContext       )	\
  ooc_method0(Object, testProtectionMultiContext        )	\
  ooc_method0(Object, testProtectionDropUnRetainedObject)	\
  ooc_method0(Object, testProtectionDropRetainedObject  )	\
								\
  ooc_method0(Object, testIsObject                      )	\
  ooc_method0(Object, testIsObjectManyObjects           )	\
								\
  ooc_method0(Object, testRawAllocation                 )	\
  ooc_method0(Object, testRawIsAllocated                )	\
								\
  ooc_method0(Object, testClassObjCnt                   )	\
								\
        MemoryTest_PRIVATE_DEF

#ifndef MemoryTest_PRIVATE_DEF
#define MemoryTest_PRIVATE_DEF
#endif

#include ooc_End

#endif /* OOC_TESTSUITE_MEMORY_MEMORYTEST_H */

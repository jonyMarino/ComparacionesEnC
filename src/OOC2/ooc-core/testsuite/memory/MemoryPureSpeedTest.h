#ifndef OOC_TESTSUITE_MEMORY_MEMORYPURESPEEDTEST_H
#define OOC_TESTSUITE_MEMORY_MEMORYPURESPEEDTEST_H

#include <ooc/Object.h>
#include <ooc/test/TestCase.h>

#include ooc_Interface

#define FINAL_CLASS MemoryPureSpeedTest
#define SUPER_CLASS TestCase

#define CLASSDEF_MemoryPureSpeedTest			\
        CLASSDEF_TestCase				\
							\
     ooc_method0(Object, speedTestAlloc1       )	\
     ooc_method0(Object, speedTestAlloc3       )	\
     ooc_method0(Object, speedTestMultiAlloc1  )	\
     ooc_method0(Object, speedTestMultiAlloc3  )	\
							\
     ooc_method0(Object, speedTestMalloc1      )	\
     ooc_method0(Object, speedTestMalloc3      )	\
     ooc_method0(Object, speedTestMultiMalloc2 )	\
     ooc_method0(Object, speedTestMultiMalloc5 )	\
							\
     ooc_method0(Object, speedTestNew1         )	\
     ooc_method0(Object, speedTestNew3         )	\
     ooc_method0(Object, speedTestMultiNew1    )	\
     ooc_method0(Object, speedTestMultiNew3    )	\
     ooc_method0(Object, speedTestNewPoint1    )	\
     ooc_method0(Object, speedTestNewPoint3    )	\
							\
     ooc_method0(Object, speedTestInit1        )	\
     ooc_method0(Object, speedTestInit3        )	\
							\
     ooc_method0(Object, speedTestInitNotCheck1)	\
     ooc_method0(Object, speedTestInitNotCheck3)	\
							\
     ooc_method0(Object, speedTestMthd1)		\
     ooc_method0(Object, speedTestMthd3)		\
     ooc_method0(Object, speedTestMthdArg1)		\
     ooc_method0(Object, speedTestMthdArg3)		\
     ooc_method0(Object, speedTestMthdRetArg1)		\
     ooc_method0(Object, speedTestMthdRetArg3)		\
							\
        MemoryPureSpeedTest_PRIVATE_DEF

#ifndef MemoryPureSpeedTest_PRIVATE_DEF
#define MemoryPureSpeedTest_PRIVATE_DEF
#endif

#include ooc_End

#endif /* OOC_TESTSUITE_MEMORY_MEMORYPURESPEEDTEST_H */

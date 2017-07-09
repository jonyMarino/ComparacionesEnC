#ifndef OOC_TESTSUITE_MEMORY_MEMORYSPEEDTEST_H
#define OOC_TESTSUITE_MEMORY_MEMORYSPEEDTEST_H

#include <ooc/Object.h>
#include <ooc/test/TestCase.h>

#include ooc_Interface

#define FINAL_CLASS MemorySpeedTest
#define SUPER_CLASS TestCase

#define CLASSDEF_MemorySpeedTest			\
        CLASSDEF_TestCase				\
							\
     ooc_method0(Object, speedTest5000000xAUTO)		\
     ooc_method0(Object, speedTest5000000xMALLOC)	\
     ooc_method0(Object, speedTest5000000xNEW)		\
							\
     ooc_method0(Object, speedTest2500000xAUTO)		\
     ooc_method0(Object, speedTest2500000xMALLOC)	\
     ooc_method0(Object, speedTest2500000xNEW)		\
							\
     ooc_method0(Object, speedTest1000000xAUTO)		\
     ooc_method0(Object, speedTest1000000xMALLOC)	\
     ooc_method0(Object, speedTest1000000xNEW)		\
							\
        MemorySpeedTest_PRIVATE_DEF

#ifndef MemorySpeedTest_PRIVATE_DEF
#define MemorySpeedTest_PRIVATE_DEF
#endif

#include ooc_End

#endif /* OOC_TESTSUITE_MEMORY_MEMORYSPEEDTEST_H */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/assert.h>
#include <ooc/init_ooc.h>
#include <ooc/test/TestSuite.h>
#include <ooc/test/TestResult.h>
#include <ooc/ex/ExSigALRM.h>
#include <ooc/ex/ExSigBUS.h>
#include <ooc/ex/ExSigFPE.h>
#include <ooc/ex/ExSigILL.h>
#include <ooc/ex/ExSigINT.h>
#include <ooc/ex/ExSigQUIT.h>
#include <ooc/ex/ExSigSEGV.h>
#include <ooc/ex/ExSigTERM.h>
#include <string.h>
#include <stdio.h>

#include "memory/MemoryTest.h"
#include "protocol/ProtocolTest.h"
#include "reflect/ReflectTest.h"

#include "memory/MemorySpeedTest.h"
#include "memory/MemoryPureSpeedTest.h"

#include "memory/PureSpeedResult.h"

/*
 * -------------
 * List of Tests
 * -------------
 */

struct suite {
  const char *id;
  Class       cls_result;
  TestSuite   suite;
};

struct test {
  Class cls;
  const char *id;
};

/*
 * Testsuite Configuration
 */

static struct suite suites[] = 
  {
    /* Standard suites */
    { "Base" , 0                                    , 0 },
    { "Speed", 0                                    , 0 },

    /* Extended standard suite */
    { "Pure" , (void*)ooc_classDesc(PureSpeedResult), 0 }

    /* Add new extra suites */
  };

static struct test tests[] = 
  {
    { (void*)ooc_classDesc(MemoryTest),          "Base"  },
    { (void*)ooc_classDesc(ProtocolTest),        "Base"  },
    { (void*)ooc_classDesc(ReflectTest),         "Base"  },
						         
    { (void*)ooc_classDesc(MemorySpeedTest),     "Speed" },
						         
    { (void*)ooc_classDesc(MemoryPureSpeedTest), "Pure"  }
  };

/*
 * ---------------
 * Local Functions
 * ---------------
 */

static
void init_classes(void)
{
  size_t i;
  
  for (i = 0; i < OOC_ARRLEN(tests); i++)
    ooc_classDescInitialize(tests[i].cls);

  for (i = 0; i < OOC_ARRLEN(suites); i++)
    if (suites[i].cls_result)
      ooc_classDescInitialize(suites[i].cls_result);
}

static
TestSuite get_suite(const char*id)
{
  size_t i = 0;
  
  for (i = 0; i < OOC_ARRLEN(suites); i++)
    if (!strcmp(suites[i].id, id)) {
      if (!suites[i].suite)
	suites[i].suite = new1(TestSuite, initWith, id);

      return suites[i].suite;
    }

  return 0;
}

static
void add_test(char *name)
{
  constClass cls = (Class)Class(Object);
  constClass cls_test;
  TestSuite suite;
  char *sep = strchr(name, '.');
  size_t i;

  if (sep) {
    *sep = '\0';
    
    cls_test = call1(cls, findSubclass, name);
  } else
    cls_test = call1(cls, findSubclass, name);

  ooc_assert(cls_test);

  for (i = 0; i < OOC_ARRLEN(tests); i++)
    if (tests[i].cls == cls_test)
      break;

  ooc_assert(i != OOC_ARRLEN(tests));

  suite = get_suite(tests[i].id);
  
  ooc_assert(suite);
    
  if (sep) 
    call2(suite, addMethodTest, cls_test, sep+1);
  else
    call1(suite, addClassTest , cls_test);
}

static
void add_all_tests(const char *id)
{
  TestSuite suite = get_suite(id);
  size_t i;

  ooc_assert(suite);
  
  for (i = 0; i < OOC_ARRLEN(tests); i++)
    if (!strcmp(tests[i].id, id))
      call1(suite, addClassTest, (Class)tests[i].cls);
}

static
bool arg_is_option(const char *arg)
{
  return strspn(arg, "-+") == 1;
}

static 
bool arg_is_str(const char *arg, const char *str)
{
  return !strcmp(arg+1, str);
}

static
int add_single_test(int idx, int argc, char *argv[])
{
  int i = idx + 1;
  
  while (i < argc && !arg_is_option(argv[i])) {
    add_test(argv[i]);
    
    ++i;
  }

  return i-1;
}

/*
 * ----
 * Main
 * ----
 */

int main(int argc, char *argv[])
{
  ooc_init_ooc(), init_classes();

  Class(ExSigALRM)->trap();
  Class(ExSigBUS) ->trap();
  Class(ExSigFPE) ->trap();
  Class(ExSigILL) ->trap();
  Class(ExSigINT) ->trap();
  Class(ExSigQUIT)->trap();
  Class(ExSigSEGV)->trap();
  Class(ExSigTERM)->trap();

  if (argc <= 1)
    add_all_tests("Base");
  else { /* arguments lookup */
    int i;

    for (i = 1; i < argc; i++) {
      if (!arg_is_option(argv[i]))
	break;

      if      (arg_is_str(argv[i], "help")) {
	fprintf(stderr, "\nUsage:\n");
	fprintf(stderr, "\t%s -ct -cs -t [base_tests] -s [speed_tests] "
		"-e extra_tests\n", argv[0]);
	fprintf(stderr, " where:\n\n");
	fprintf(stderr, "   -ct = Test all core tests\n");
	fprintf(stderr, "   -cs = Test all speed core tests\n");
	fprintf(stderr, "   -t [base_tests]  = Test list of base tests\n");
	fprintf(stderr, "   -s [speed_tests] = Test list of speed tests\n");
	fprintf(stderr, "   -e  extra_tests  = Test list of extra tests\n\n");
	fprintf(stderr, "   List of tests = (Class|Class.Method)*\n\n");
      }
      else if (arg_is_str(argv[i], "ct"))
	/* NOTE-TODO: call core tests */;

      else if (arg_is_str(argv[i], "cs"))
	/* NOTE-TODO: call core speed tests */;

      else if (arg_is_str(argv[i], "t")) {
	if (i == argc-1 || arg_is_option(argv[i+1]))
	  add_all_tests("Base");
	else
	  i = add_single_test(i, argc, argv);
      }

      else if (arg_is_str(argv[i], "s")) {
	if (i == argc-1 || arg_is_option(argv[i+1])) {
	  add_all_tests("Speed");
	  add_all_tests("Pure");
	} else
	  i = add_single_test(i, argc, argv);
      }

      else if (arg_is_str(argv[i], "e")) {
	if (i == argc-1 || arg_is_option(argv[i+1])) {
	  ;
	} else
	  i = add_single_test(i, argc, argv);
      }
    }
  }

  {
    size_t i;
    
    for (i = 0; i < OOC_ARRLEN(suites); i++) {
      if (suites[i].suite) {
	TestResult res = !suites[i].cls_result ? 
	  new(TestResult) : (TestResult)newAs(suites[i].cls_result);
	
	call1(suites[i].suite, run, res);
	
	call0(res, print);
	delete(res);
	delete(suites[i].suite);
      }
    }
  }

#if OOC_DBG_POOL
  ooc_memLoad();
#endif
    
  return 0;
}

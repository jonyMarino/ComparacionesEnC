/*
 *******************************
 * TestSuite implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: TestSuite.c,v 1.8 2005/12/16 16:56:03 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/type/chr_array.h>
#include <ooc/reflect/Method.h>
#include <ooc/test/TestCase.h>
#include <ooc/ex/ExBadArgument.h>
#include <string.h>

#include Implementation

#define TestSuite_PRIVATE_DEF			\
        private(Test , first)			\
        private(Test ,  last)			\
        private(Test ,  next)			\
        private(char*,  name)

#include <ooc/test/TestSuite.h>

/*
 * Object methods
 */

method1(TYPE, initWith, const char *name)
{
  self->first = 0;
  self->last  = 0;
  self->name  = 0;
  self->name  = chr_array_rawdup(name, strlen(name)+1);

  return self;
}

method0(void, deinit)
{
  Test test = self->first;

  while (test) {
    Object test_ = (Object)test;
    Test next = pcall0(test_, Test, getNext);

    release(test);
    test = next;
  }

  chr_array_del(self->name), self->name = 0;
}

method1(void, addTest, Test test)
{
  Object test_ = (Object)test;

  retain(test);

  if (self->last) {
    Object last = (Object)self->last;
    pcall1(last, Test, setNext, test);
  } else
    self->first = test;

  pcall1(test_, Test, setNext, 0);
  self->last = test;
}

method1(void, addClassTest, constClass cls)
{
  TestCase test_case;

  if (!ooc_isSubclassOf(cls, TestCase))
    throw(new(ExBadArgument));

  test_case = (TestCase)newAs(cls);
    
  call1(self, addTest, (Test)test_case);
  
  delete(test_case);
}

method2(void, addMethodTest, constClass cls, const char *mth_name)
{  
  TestCase test_case;

  if (!ooc_isSubclassOf(cls, TestCase))
    throw(new(ExBadArgument));

  test_case = (TestCase)newAs(cls);
  
  call1(test_case, setName, mth_name);
  
  call1(self, addTest, (Test)test_case);
  
  delete(test_case);
}

method1(void, run, TestResult result)
{
  Test test = self->first;

  while (test) {
    Object test_ = (Object)test;

    pcall1(test_, Test, run, result);
    test = pcall0(test_, Test, getNext);
  }
}

method0(TestResult, newRun)
{
  TestResult result = new(TestResult);

  call1(self, run, result);

  return result;
}

/*
 * Protocol methods
 */

method1(void, setNext, Test test)
{
  self->next = test;
}

constMethod0(Test, getNext)
{
  return self->next;
}

constMethod0(const char*, getName)
{
  return self->name;
}

/*
 * Static methods
 */

staticMethod0(void, initialize)
{
  override( initWith      );
  override( deinit        );

  override( run           );
  override( newRun        );

  override( addTest       );
  override( addClassTest  );
  override( addMethodTest );

  override( getNext       );
  override( setNext       );
  override( getName       );
}

#include End

/*
 *******************************
 * TestCase implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: TestCase.c,v 1.9 2005/12/16 16:56:03 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/assert.h>
#include <ooc/reflect/Method.h>
#include <ooc/type/chr_array.h>
#include <ooc/type/Int.h>
#include <ooc/ex/ExBadArgument.h>

#include <string.h>

#include Implementation

#include <ooc/test/TestCase.h>
#include <ooc/test/TestResult.h>

/* reactivate TestCase scope */
#include ooc_CloseScope
#define ABSTRACT_CLASS TestCase
#include ooc_OpenScope

/*
 * Object methods
 */

method0(TYPE, init)
{
  self->name = 0;

  return self;
}

method0(void, deinit)
{
  chr_array_del(self->name), self->name = 0;
}

method0(int, runBare)
{
  volatile int res = 0;

  ooc_assert(self->name);

  call0(self, setup);

  try {
    Class  cls = (Class)self->_isa;
    constMethod mthd = call1(cls, newMethod, self->name);
    Object ret_obj, args[1];

    args[0] = (Object)self;

    ret_obj = call1(mthd, invoke, args);
    if (ret_obj) {
      if (!isA(ret_obj, Int))
	throw(new(ExBadArgument));
		  
      res = ((Int)ret_obj)->val;

      autorelease(ret_obj);
    }
    
    delete(mthd);
  } catch (Object, ex) {
    call0(self, cleanup);
    rethrow(ex);
  } endTry;

  call0(self, cleanup);

  return res;
}

method1(void, setName, const char *name)
{
  if (self->name)
    chr_array_del(self->name);

  if (name) 
    self->name = chr_array_rawdup(name, strlen(name)+1);
  else
    self->name = 0;
}

method0(void, setup)
{
  (void)self;
}

method0(void, cleanup)
{
  (void)self;
}

/*
 * Protocol methods
 */

method1(void, run, TestResult result)
{
  if (!self->name) {
    Class       cls = (Class)self->_isa;
    size_t mthd_cnt = call0(cls, methodCnt);
    size_t i;
    
    for (i = 0; i < mthd_cnt; i++) { /* loop on methods */
      constMethod mthd = call1(cls, newMethodAt, i);
      const char *name = call0(mthd, getName);
      
      if (!strncmp(name, "test", 4) || !strncmp(name, "speedTest", 9)) {
	call1(self, setName, name);
	
	call1(result, run, self);
      }
    }

    return;
  }

  call1(result, run, self);
}

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
  override( init     );
  override( deinit   );

  override( setup    );
  override( run      );
  override( runBare  );
  override( cleanup  );

  override( setName  );

  override( getNext  );
  override( setNext  );
  override( getName  );
}

#include End

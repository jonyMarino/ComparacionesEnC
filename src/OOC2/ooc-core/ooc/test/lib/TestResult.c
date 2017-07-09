/*
 *******************************
 * TestResult implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: TestResult.c,v 1.16 2005/12/18 19:04:41 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/reflect/Method.h>
#include <ooc/test/TestCase.h>
#include <ooc/ex/ExNotSupported.h>
#include <ooc/ex/ExBadAccess.h>
#include <stdio.h>
#include <string.h>

#include Implementation

#include <ooc/test/TestMessage.h> /* friend classes */
#include <ooc/test/TestSuccess.h>
#include <ooc/test/TestFailure.h>
#include <ooc/test/TestError.h>
#include <ooc/test/TestResult.h>

/*
 * Object method
 */

method0(TYPE, init)
{
  self->first      = 0;
  self->last       = 0;
  self->successCnt = 0;
  self->failCnt    = 0;
  self->errorCnt   = 0;

  return self;
}

method0(void, deinit)
{
  TestMessage msg = self->first;

  while (msg) {
    TestMessage next = msg->next;

    release(msg);
    msg = next;
  }
}

method2(void, runProtected, Test test, int (*fct_test)(Test))
{
  volatile clock_t start_time, end_time;
  volatile int iter = 0;
  size_t    old_cnt = self->successCnt;
  double   duration;

  call1(self, startTest, test);
  
  try {
    start_time = clock();
    iter = fct_test(test);
    end_time   = clock();

    ++self->successCnt;
  } catch (TestFailure, failure) {
    end_time = clock();
    ++self->failCnt;
    call1(self, pushMessage, (TestMessage)failure);
    
    delete(failure);
  } catch (Object, ex) {
    TestError error = 0;
    
    end_time = clock();
    
    ++self->errorCnt;
    error = new3(TestError, initWith, ex, ooc_exFile(), ooc_exLine());
    call1(self, pushMessage, (TestMessage)error);
    
    delete(error);
    delete(ex);
  } endTry;
  
  duration = (double)(end_time - start_time)/CLOCKS_PER_SEC;

  if (old_cnt != self->successCnt) {
    TestSuccess success = new(TestSuccess);
    
    call1(self, pushMessage, (TestMessage)success);

    call1(success, setIterDuration , iter > 0 ? duration/iter : 0);
    call1(success, setIteration    , iter    );

    delete(success);
  }
  
  {
    Object obj_test = (Object)test;
    
    call1(self->last, setTstName  , ooc_className(test->_isa));
    call1(self->last, setMthName  , pcall0(obj_test, Test, getName));
    
    call1(self->last, setStartTime, start_time);
    call1(self->last, setEndTime  , end_time  );

    call1(self->last, setTotalDuration, duration);
  }

  call1(self, endTest, test);
}

method1(void, run, TestCase test)
{
  call2(self, runProtected, (Test)test,(int(*)(Test))Class(TestCase)->runBare);
}  
 
method1(void, startTest, Test test)
{
  (void)self; (void)test;
}

method1(void, endTest  , Test test) 
{
  (void)self; (void)test;

  fprintf(stderr, ".");
}

constMethod0(size_t, testCnt)
{
  return self->successCnt + self->failCnt + self->errorCnt;
}

constMethod0(bool, successful)
{
  return !(self->failCnt || self->errorCnt);
}

method1(void, pushMessage, TestMessage msg)
{
  retain(msg);

  if (self->last)
    self->last->next = msg;
  else
    self->first = msg;

  msg->next  = 0;
  self->last = msg;
}

method0(void, popMessage)
{
  if (!self->first || !self->last)
    throw(new(ExBadAccess));
  
  if (self->first == self->last) {
    release(self->last);

    self->first = 0;
    self->last  = 0;
  } else {
    TestMessage msg = self->first;

    while (msg->next != self->last)
      msg = msg->next;

    release(self->last);

    msg->next  = 0;
    self->last = msg;
  }
}

method0(void, print)
{
  TestMessage msg = self->first;
  const char *curTstName = 0;

  while (msg) {

    if (!curTstName || strcmp(curTstName, msg->tstName)) {
      fprintf(stderr, "\n\n** TESTCASE \"%s\"\n\n", msg->tstName);
      curTstName = msg->tstName;
    }
      
    if (isA(msg, TestSuccess)) {
      TestSuccess suc = (TestSuccess)msg;

      if (suc->iteration)
	fprintf(stderr, " - %-35.35s (%.2f s, %12.2f iter/s) ", 
		suc->mthName, suc->totalDuration, 1/suc->iterDuration);
      else
	fprintf(stderr, " - %-35.35s (%.2f s, ---------.-- iter/s) ", 
		suc->mthName, suc->totalDuration);

      fprintf(stderr, "- \033[32mOK   \033[0m\n");
    }

    else if (isA(msg, TestFailure)) {
      TestFailure fail = (TestFailure)msg;
      
      fprintf(stderr, " - %-35.35s (%.2f s) ", fail->mthName, 
	      fail->totalDuration);
      fprintf(stderr, "- \033[31mFAIL\033[0m: ");
      fprintf(stderr, "condition '%s' in <%s, %d>\n",
	      fail->cond, fail->file,fail->line);

    }
    
    else if (isA(msg, TestError)) {
      TestError error = (TestError)msg;

      fprintf(stderr, " - %-35.35s (%.2f s) ", error->mthName,
	      error->totalDuration);
      fprintf(stderr, "- \033[35mERROR\033[0m: ");
      fprintf(stderr, "exception '%s' <%s, %d>\n", 
	      ooc_className(error->ex->_isa),
	      error->file, error->line);
    }
    
    else
      throw(new(ExNotSupported));

    msg = msg->next;
  }

  fprintf(stderr, "\nTest summary: %d fail(s), %d error(s), %d ok(s)\n\n",
	  self->failCnt, self->errorCnt, self->successCnt);
}

/*
 * Static method
 */

staticMethod0(void, initialize)
{
  override( init         );
  override( deinit       );

  override( runProtected );
  override( run          );
  override( startTest    );
  override( endTest      );

  override( testCnt      );
  override( successful   );
  
  override( pushMessage  );
  override( popMessage   );

  override( print        );
}

#include End

bool TestCase_throwTestFailure_(const char *str, const char *file, int line)
{
  throw(new3(TestFailure, initWith, str, file, line));

  return false;
}

/*
 *******************************
 * SpeedTestResult implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: SpeedTestResult.c,v 1.4 2005/12/06 15:12:56 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/type/chr_array.h>

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include Implementation

#include <ooc/test/SpeedTestResult.h>
#include <ooc/test/TestSuccess.h>

/* reactivate TestCase scope */
#include ooc_CloseScope
#define ABSTRACT_CLASS SpeedTestResult
#define SUPER_CLASS    TestResult
#include ooc_OpenScope

static inline
void group_messages(SpeedTestResult self)
{
  TestMessage  msg = self->first;
  TestSuccess prev = 0;
  unsigned long int prev_c = 0;
  size_t loop = 1;

  while (msg && strncmp(msg->mthName, "speedTest", 9))
    msg = msg->next;

  while (msg && !strncmp(msg->mthName, "speedTest", 9)) {
    size_t len, off;
    TestSuccess suc;

    if (!isA(msg, TestSuccess)) {
      prev_c = 0;

      msg = msg->next;
      
      continue;
    }

    suc = (TestSuccess)msg;
    if (suc->next && isA(suc->next, TestSuccess) && 
	!strcmp(suc->mthName, suc->next->mthName)) { /* do sum */
      TestSuccess next = (TestSuccess)suc->next;

      call1(suc, setStartTime, 0);
      call1(suc, setEndTime  , 0);
      call1(suc, setTotalDuration, suc->totalDuration + next->totalDuration);
      call1(suc, setIterDuration , suc->iterDuration  +  next->iterDuration);
      
      suc->next = next->next;
      release(next);
      
      ++loop;

      continue;
    }

    len = strlen(suc->mthName);
    off = len-1;
      
    if (loop > 1) { /* do average */
      call1(suc, setTotalDuration, suc->totalDuration/loop);
      call1(suc, setIterDuration , suc->iterDuration/loop);
      loop = 1;
    }
    
    while (isdigit(suc->mthName[off]))
      --off;
    
    if (off == len-1)
      prev_c = 0;
    else {
      unsigned int c = strtoul(suc->mthName+off+1, 0, 10);
      
      if (!prev_c || strncmp(prev->mthName, suc->mthName, off+1))
	prev_c = c;
      else { /* do factor rule */
	char *mth_name = chr_array_dup(prev->mthName);

	mth_name[off+1] = 0;
	call1(prev, setMthName , mth_name);
	chr_array_del(mth_name);
	
	call1(prev, setTotalDuration, 
	      (suc->totalDuration-prev->totalDuration)/(c-prev_c));
	call1(prev, setIterDuration, 
	      (suc->iterDuration-prev->iterDuration)/(c-prev_c));
	
	prev->next = suc->next;
	release(suc);
	
	prev_c = 0;
	
	suc = prev;
      }
    }
    
    prev = suc;
    msg  = msg->next;
  }
}


/*
 * Object methods
 */

method0(TYPE, init)
{
  scall0(init);

  self->repeat = 1;
  
  return self;
}

method1(TYPE, initWith, size_t repeat)
{
  scall0(init);

  self->repeat = repeat;
  
  return self;
}

method1(void, run, TestCase test)
{
  size_t i;

  for (i = 0; i < self->repeat; i++)
    scall1(run, test);
}

method0(void, print)
{
  group_messages(self);

  scall0(print);
}

staticMethod0(void, initialize)
{
  override( init     );
  override( initWith );

  override( run      );
  override( print    );
}

#include End

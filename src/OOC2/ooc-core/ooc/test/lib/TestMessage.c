/*
 *******************************
 * TestMessage implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: TestMessage.c,v 1.9 2005/12/16 16:56:03 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/type/chr_array.h>
#include <ooc/ex/ExNotSupported.h>

#include <string.h>
#include <stdio.h>

#include Implementation

#include <ooc/test/TestMessage.h>

/*
 * Object methods
 */

method0(TYPE, init)
{
  self->tstName = 0;
  self->mthName = 0;

  return self;
}

method0(void, deinit)
{
  chr_array_del(self->tstName), self->tstName = 0;
  chr_array_del(self->mthName), self->mthName = 0;
}

method1(void, setTstName, const char *name)
{
  if (self->tstName)
    chr_array_del(self->tstName);
  
  self->tstName = chr_array_rawdup(name, strlen(name)+1);
}

method1(void, setMthName, const char *name)
{
  if (self->mthName)
    chr_array_del(self->mthName);
    
  self->mthName = chr_array_rawdup(name, strlen(name)+1);
}

method1(void, setStartTime, clock_t startTime)
{
  self->startTime = startTime;
}

method1(void, setEndTime, clock_t endTime)
{
  self->endTime = endTime;
}

method1(void, setTotalDuration, double duration)
{
  self->totalDuration = duration;
}

/*
 * Class methods
 */

staticMethod0(void, initialize)
{
  override( init             );
  override( deinit           );

  override( setTstName       );
  override( setMthName       );

  override( setStartTime     );
  override( setEndTime       );
  override( setTotalDuration );
}

#include End

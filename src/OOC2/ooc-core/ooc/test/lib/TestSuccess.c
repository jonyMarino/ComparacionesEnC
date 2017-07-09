/*
 *******************************
 * TestSuccess implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: TestSuccess.c,v 1.2 2005/10/25 16:47:13 oachim Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#define USING_OOC

#include <ooc/Object.h>

#include Implementation

#include <ooc/test/TestSuccess.h>

/*
 * Object methods
 */

method1(void, setIterDuration, double duration)
{
  self->iterDuration = duration;
}

method1(void, setIteration, int iteration)
{
  self->iteration = iteration;
}

/*
 * Class methods
 */

staticMethod0(void, initialize)
{
  override( setIterDuration );
  override( setIteration    );
}

#include End

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/assert.h>

#include <stdio.h>

#include Implementation

#include "PureSpeedResult.h"
#include <ooc/test/TestSuccess.h>

/* reactivate TestCase scope */
#include ooc_CloseScope
#define ABSTRACT_CLASS PureSpeedResult
#define SUPER_CLASS    SpeedTestResult
#include ooc_OpenScope

/*
 * Test Parameter(s)
 */

#define REPEAT 5

/*
 * Helper(s)
 */

#define ITER_DURATION(time, msg)		\
   do {						\
     ooc_assert(msg && isA(msg, TestSuccess));	\
     time = ((TestSuccess)msg)->iterDuration;	\
   } while (0)

/*
 * Object methods
 */

method0(TYPE, init)
{
  scall1(initWith, REPEAT);

  return self;
}

method0(void, print)
{
  TestMessage msg;

  double da  = 0.0;
  double dma = 0.0;

  double dc  = 0.0;
  double di  = 0.0;

  double dm  = 0.0;
  double dmm = 0.0;

  double dn  = 0.0;
  double dnm = 0.0;
  double dnp = 0.0;

  double dcl   = 0.0;
  double dcla  = 0.0;
  double dclra = 0.0;

  scall0(print);

  msg = self->first; ITER_DURATION(da   , msg);
  msg = msg->next  ; ITER_DURATION(di   , msg);
  msg = msg->next  ; ITER_DURATION(dc   , msg);
  msg = msg->next  ; ITER_DURATION(dm   , msg);

  msg = msg->next  ; ITER_DURATION(dcla , msg);
  msg = msg->next  ; ITER_DURATION(dcl  , msg);
  msg = msg->next  ; ITER_DURATION(dclra, msg);

  msg = msg->next  ; ITER_DURATION(dma  , msg);
  msg = msg->next  ; ITER_DURATION(dmm  , msg);
  msg = msg->next  ; ITER_DURATION(dnm  , msg);
  msg = msg->next  ; ITER_DURATION(dn   , msg);
  msg = msg->next  ; ITER_DURATION(dnp  , msg);

  fprintf(stderr, " - GLIBC MALLOC       = %.2f * OOC ALLOC\n"      , dm /da);
  fprintf(stderr, " - GLIBC MULTI MALLOC = %.2f * OOC MULTI ALLOC\n", dmm/dma);
  fprintf(stderr, " - OOC INIT           = %.2f * OOC INIT without check\n", 
	  di/dc);
  fprintf(stderr, " - OOC INIT           = %.2f%% of OOC NEW \n\n", 
	  di/dn*100);
}

/*
 * Static method
 */

staticMethod0(void, initialize)
{
  override( init  );
  override( print );
}

#include End

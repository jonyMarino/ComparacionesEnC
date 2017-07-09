/*
 ******************************
 * Signal Implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Signal.c,v 1.4 2005/12/20 15:17:19 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <signal.h>

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/assert.h>
#include <ooc/ex/ExBadSignal.h>

#define SIGNAL_IMPLEMENTATION(sig)					\
									\
static void								\
OOC_CAT(sig,_handler)(int sig_id)					\
{									\
  if (signal(OOC_CAT(SIG,sig), OOC_CAT(sig,_handler)) == SIG_ERR)	\
    throwLoc(new(ExBadSignal), "unknown", 0);				\
									\
  ooc_assert(sig_id == OOC_CAT(SIG,sig));				\
									\
  throwLoc(new(OOC_CAT(ExSig,sig)), "unknown", 0);			\
}									\
									\
method0(TYPE, init)							\
{									\
  scall0(init);								\
									\
  self->sig_id = OOC_CAT(SIG,sig);					\
									\
  return self;								\
}									\
									\
staticMethod0(bool, trap)						\
{									\
  return signal(OOC_CAT(SIG,sig), OOC_CAT(sig,_handler)) != SIG_ERR;	\
}									\
									\
staticMethod0(void, initialize)						\
{									\
  override( init );							\
  override( trap );							\
}

/*
 * -------------------------
 *  Signals implementation
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExSignal.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExSigABRT.h>

SIGNAL_IMPLEMENTATION(ABRT)

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExSigALRM.h>

SIGNAL_IMPLEMENTATION(ALRM)

#include End

/*
 * -------------------------
 */

#ifndef SIGBUS
#if defined(SIG_BUS)
#define SIGBUS SIG_BUS
#else
#define SIGBUS 0
#endif
#endif

#include Implementation

#include <ooc/ex/ExSigBUS.h>

SIGNAL_IMPLEMENTATION(BUS)

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExSigFPE.h>

SIGNAL_IMPLEMENTATION(FPE)

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExSigILL.h>

SIGNAL_IMPLEMENTATION(ILL)

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExSigINT.h>

SIGNAL_IMPLEMENTATION(INT)

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExSigQUIT.h>

SIGNAL_IMPLEMENTATION(QUIT)

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExSigSEGV.h>

SIGNAL_IMPLEMENTATION(SEGV)

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExSigTERM.h>

SIGNAL_IMPLEMENTATION(TERM)

#include End

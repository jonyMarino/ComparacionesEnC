/* multiple inclusion allowed */

/*
 ******************************
 * Initialize_ definition
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: init_def.h,v 1.9 2005/12/14 18:35:06 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#if OOC_THREAD_USE

#include <ooc/utils/thread.h>

static void
ooc_methodName(_init__) (void)
{
  ooc_classInitialize_((Class)ooc_classDesc(CLASS));
}

static void
ooc_methodName(_once__) (void)
{
  ooc_threadOnce(once);
  ooc_threadOnceCall(&once, ooc_methodName(_init__));
}

#endif /* OOC_THREAD_USE */

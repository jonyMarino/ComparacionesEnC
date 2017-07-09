/* multiple inclusion allowed */

/*
 ******************************
 * Assertion interface
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: assert.h,v 1.2 2005/11/16 17:59:07 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#undef ooc_assert

/*
 * -------------------------
 *  Assert macros
 * -------------------------
 */

#if   defined(OOC_CASSERT) /* C behavior */

#include <assert.h>
#define ooc_assert(cond) assert(cond)

#elif defined(OOC_NDEBUG)  /* Empty behavior */

#define ooc_assert(cond) ((void)0)

#else                      /* OOC behavior */

#define ooc_assert(cond) \
 ((void)((cond) || ooc_assert_(#cond, __FILE__, __LINE__)))

#endif

int ooc_assert_(const char *cond, const char *file, int line);

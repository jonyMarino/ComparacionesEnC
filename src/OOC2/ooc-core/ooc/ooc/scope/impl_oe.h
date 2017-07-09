/* multiple inclusion allowed */

/*
 ******************************
 * Implementation extension openning
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: impl_oe.h,v 1.1 2005/07/04 13:52:05 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#undef   ooc_OpenImplementationExtension
#define  ooc_CloseImplementationExtension <ooc/ooc/scope/impl_ce.h>

#include ooc_OpenImplementation

#define ooc_implementationExtension(func)	\
   void ooc_methodName(func)(void);		\
   void ooc_methodName(func)(void)

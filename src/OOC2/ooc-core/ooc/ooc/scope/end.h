/* multiple inclusion allowed */

/*
 ******************************
 * Closure
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: end.h,v 1.1 2005/07/04 13:52:05 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#if   defined(ooc_CloseInterface)
#include      ooc_CloseInterface
#elif defined(ooc_CloseImplementationExtension)
#include      ooc_CloseImplementationExtension
#elif defined(ooc_CloseImplementation)
#include      ooc_CloseImplementation
#else
#error "libooc: invalid scope parity - missing interface or implementation"
#endif

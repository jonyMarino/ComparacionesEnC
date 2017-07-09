/* multiple inclusion allowed */

/*
 ******************************
 * Implementation extension closing
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: impl_ce.h,v 1.1 2005/07/04 13:52:05 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include ooc_CloseImplementation

#undef   ooc_implementationExtension

#undef   ooc_CloseImplementationExtension
#define  ooc_OpenImplementationExtension <ooc/ooc/scope/impl_oe.h>


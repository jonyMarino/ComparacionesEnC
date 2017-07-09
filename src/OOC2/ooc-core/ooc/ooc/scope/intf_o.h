/* multiple inclusion allowed */

/*
 ******************************
 * Interface openning
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: intf_o.h,v 1.1 2005/07/04 13:52:05 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#undef   ooc_OpenInterface
#define  ooc_CloseInterface <ooc/ooc/scope/intf_c.h>

#ifdef   ooc_CloseImplementation
#ifdef   ooc_CloseScope
#include ooc_CloseScope
#endif
#endif

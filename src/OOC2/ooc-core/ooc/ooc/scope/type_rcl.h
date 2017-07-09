/* multiple inclusion allowed */

/*
 ******************************
 * Type as ROOT_CLASS type
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: type_rcl.h,v 1.1 2005/12/14 18:35:06 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include ooc__TypeClear

#define      TYPE          ROOT_CLASS
#define constTYPE OOC_CAT(const, TYPE)
#define classTYPE OOC_CAT(class, TYPE)

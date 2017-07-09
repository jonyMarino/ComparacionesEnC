/* multiple inclusion allowed */

/*
 ******************************
 * Type as Object type
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: type_obj.h,v 1.2 2005/12/14 18:35:06 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include ooc__TypeClear

#define      TYPE                Object
#define constTYPE OOC_CAT(const, TYPE)
#define classTYPE OOC_CAT(class, TYPE)

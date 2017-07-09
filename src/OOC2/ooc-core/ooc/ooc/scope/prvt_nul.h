/* multiple inclusion allowed */

/*
 ******************************
 * Access control nullification
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: prvt_nul.h,v 1.3 2005/12/20 15:17:19 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#ifdef ooc_public
#include ooc__PrivacyClear
#endif

#define   ooc_public(T,fld)
#define  ooc_visible(T,fld)
#define  ooc_private(T,fld)

#define  ooc_publicN(T,fld,cnt)
#define ooc_visibleN(T,fld,cnt)
#define ooc_privateN(T,fld,cnt)

#define  ooc_publicP(T,fld,args)
#define ooc_visibleP(T,fld,args)
#define ooc_privateP(T,fld,args)

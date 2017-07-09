/* multiple inclusion allowed */

/*
 ******************************
 * Access control desactivation
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: prvt_off.h,v 1.3 2005/12/20 15:17:19 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#ifdef ooc_public
#include ooc__PrivacyClear
#endif

#define   ooc_public(T,fld)      T fld;
#define  ooc_visible(T,fld)      T fld;
#define  ooc_private(T,fld)      T fld;

#define  ooc_publicN(T,fld,cnt)  T fld cnt;
#define ooc_visibleN(T,fld,cnt)  T fld cnt;
#define ooc_privateN(T,fld,cnt)  T fld cnt;

#define  ooc_publicP(T,fld,args) T OOC_AMS (*fld) args;
#define ooc_visibleP(T,fld,args) T OOC_AMS (*fld) args;
#define ooc_privateP(T,fld,args) T OOC_AMS (*fld) args;

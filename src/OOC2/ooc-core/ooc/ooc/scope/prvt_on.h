/* multiple inclusion allowed */

/*
 ******************************
 * Access control activation
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: prvt_on.h,v 1.3 2005/12/20 15:17:19 ldeniau Exp $
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
#define  ooc_visible(T,fld)      T const fld;
#define  ooc_private(T,fld)      T const OOC_CAT3(_prv_,__LINE__,fld);

#define  ooc_publicN(T,fld,cnt)  T fld cnt;
#define ooc_visibleN(T,fld,cnt)  T const fld cnt;
#define ooc_privateN(T,fld,cnt)  T const OOC_CAT3(_prv_,__LINE__,fld) cnt;

#define  ooc_publicP(T,fld,args) T OOC_AMS (*fld) args;
#define ooc_visibleP(T,fld,args) T OOC_AMS (*const fld) args;
#define ooc_privateP(T,fld,args) T OOC_AMS (*const OOC_CAT3(_prv_,__LINE__,fld)) args;

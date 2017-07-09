/* multiple inclusion allowed */

/*
 ******************************
 * Privacy reflection
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: prvt_rft.h,v 1.4 2006/11/27 16:59:38 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#ifdef ooc_public
#include ooc__PrivacyClear
#endif

#define ooc_fieldMakeMeta(Tstr, Tsz, Tesz, fld, Qstr)	\
  { "\000" OOC_STR(Tstr) "\000" Qstr OOC_STR(fld) +	\
    sizeof(OOC_STR(Tstr) "\000" Qstr),			\
    { 0 },  offsetof(struct CLASS, fld),		\
    sizeof(Tesz), sizeof(Tsz)/sizeof(Tesz) },

#define   ooc_public(T,fld) \
  ooc_fieldMakeMeta(T, T, T, fld, "W")
#define  ooc_visible(T,fld) \
  ooc_fieldMakeMeta(T, T, T, fld, "R")
#define  ooc_private(T,fld) \
  ooc_fieldMakeMeta(T, T, T, fld, "P")

#define  ooc_publicN(T,fld,cnt) \
  ooc_fieldMakeMeta(T[], T cnt, T, fld, "W")
#define ooc_visibleN(T,fld,cnt) \
  ooc_fieldMakeMeta(T[], T cnt, T, fld, "R")
#define ooc_privateN(T,fld,cnt) \
  ooc_fieldMakeMeta(T[], T cnt, T, fld, "P")

#define  ooc_publicP(T,fld,args) \
  ooc_fieldMakeMeta(T OOC_AMS (*)args, T OOC_AMS (*)args, T OOC_AMS (*)args, fld, "W")
#define ooc_visibleP(T,fld,args) \
  ooc_fieldMakeMeta(T OOC_AMS (*)args, T OOC_AMS (*)args, T OOC_AMS (*)args, fld, "R")
#define ooc_privateP(T,fld,args) \
  ooc_fieldMakeMeta(T OOC_AMS (*)args, T OOC_AMS (*)args, T OOC_AMS (*)args, fld, "P")

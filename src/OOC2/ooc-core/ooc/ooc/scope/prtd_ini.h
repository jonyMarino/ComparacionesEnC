/* multiple inclusion allowed */

/*
 ******************************
 * Protodef initialization
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: prtd_ini.h,v 1.2 2006/11/27 16:59:38 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#ifdef PROTODEF
#include ooc__ProtodefsClear
#endif

#define PROTODEF(T)				\
  {{ (void*)ooc_classDesc(T),			\
     1						\
  }},						\
  OOC_CATP_(PROTODEF_,T)

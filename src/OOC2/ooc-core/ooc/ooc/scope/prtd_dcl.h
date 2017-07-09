/* multiple inclusion allowed */

/*
 ******************************
 * Protodef declaration
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: prtd_dcl.h,v 1.3 2006/11/27 16:59:38 ldeniau Exp $
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
  struct {					\
    struct Protocol _;				\
  } T;						\
  OOC_CATP_(PROTODEF_,T)

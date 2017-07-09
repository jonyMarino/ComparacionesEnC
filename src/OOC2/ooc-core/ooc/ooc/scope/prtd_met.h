/* multiple inclusion allowed */

/*
 ******************************
 * Protodef meta data
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: prtd_met.h,v 1.1 2005/07/04 13:52:05 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#ifdef PROTODEF
#include ooc__ProtodefsClear
#endif

#define PROTODEF(T) \
  (Protocol)&ooc_classDesc(CLASS)->T,

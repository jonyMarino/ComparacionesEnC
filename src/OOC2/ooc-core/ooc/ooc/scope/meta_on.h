/* multiple inclusion allowed */

/*
 ******************************
 * Meta data enabled
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: meta_on.h,v 1.1 2005/07/04 13:52:05 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

/*
 * Protocol reflection
 */

#include ooc__PrivacyNullify
#include ooc__MethodsNullify
#include ooc__ProtodefsMeta

static Protocol OOC_CAT(ooc_classDesc(CLASS),_proto__)[]={
  OOC_CATD_(CLASSDEF_,CLASS)
  0
};

#define OOC_PROTO_META \
  OOC_CAT(ooc_classDesc(CLASS),_proto__)

/*
 * Field and Method reflection
 */

#if defined(OOC_REFLECTION)
#include ooc__ClassReflect
#else
#define OOC_CLASS_META 0
#endif


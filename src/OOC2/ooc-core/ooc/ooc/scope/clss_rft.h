/* multiple inclusion allowed */

/*
 ******************************
 * Reflection activation
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: clss_rft.h,v 1.4 2005/11/28 17:42:03 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

/*
 * Fields reflection
 */

#ifdef OOC_REFLECT_FIELDS

#include ooc__PrivacyReflect
#include ooc__MethodsNullify
#include ooc__ProtodefsNullify

static struct ooc_meta_fld OOC_CAT(ooc_classDesc(CLASS),_fld__)[] = {
  OOC_CATD_(CLASSDEF_,CLASS)
};

static unsigned short OOC_CAT(ooc_classDesc(CLASS),_fld_lut__)
     [OOC_ARRLEN(OOC_CAT(ooc_classDesc(CLASS),_fld__))];

#endif

/*
 * Methods reflection
 */

#ifdef OOC_REFLECT_METHODS

#include ooc__PrivacyNullify
#include ooc__MethodsReflect
#include ooc__ProtodefsReflect
						       
static struct ooc_meta_mth OOC_CAT(ooc_classDesc(CLASS),_mth__)[] = {
  OOC_CATD_(CLASSDEF_,CLASS)
};

#endif

/*
 * Meta
 */

static struct ooc_reflect OOC_CAT(ooc_classDesc(CLASS),_meta__)[1] = {{
#if defined(OOC_REFLECT_FIELDS) && defined(OOC_REFLECT_METHODS)
  OOC_CAT(ooc_classDesc(CLASS),_mth__),
  OOC_CAT(ooc_classDesc(CLASS),_fld__),
  OOC_CAT(ooc_classDesc(CLASS),_fld_lut__),
  OOC_ARRLEN(OOC_CAT(ooc_classDesc(CLASS),_mth__)),
  OOC_ARRLEN(OOC_CAT(ooc_classDesc(CLASS),_fld__))
#elif defined(OOC_REFLECT_FIELDS)
  0,
  OOC_CAT(ooc_classDesc(CLASS),_fld__),
  OOC_CAT(ooc_classDesc(CLASS),_fld_lut__),
  0,
  OOC_ARRLEN(OOC_CAT(ooc_classDesc(CLASS),_fld__))
#elif defined(OOC_REFLECT_METHODS)
  OOC_CAT(ooc_classDesc(CLASS),_mth__),
  0, 0,
  OOC_ARRLEN(OOC_CAT(ooc_classDesc(CLASS),_mth__)),
  0
#endif
}};

#define OOC_CLASS_META \
  OOC_CAT(ooc_classDesc(CLASS),_meta__)

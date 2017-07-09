/* multiple inclusion allowed */

/*
 ******************************
 * Classinfo build
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: clss_inf.h,v 1.1 2005/08/26 17:09:15 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

enum {
  OOC_CAT(ooc_classDesc(CLASS),_info__) =
    OOC_CLASSINFO_STATIC

#if   defined(ABSTRACT_CLASS)
    | OOC_CLASSINFO_ABSTRACT
#elif defined(FINAL_CLASS)
    | OOC_CLASSINFO_FINAL
#endif

#if   defined(PROTOCOL)
    | OOC_CLASSINFO_PROTOCOL
#elif defined(METACLASS)
    | OOC_CLASSINFO_METACLASS
#endif
};

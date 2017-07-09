/* multiple inclusion allowed */

/*
 ******************************
 * Implementation openning
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: impl_o.h,v 1.3 2005/12/15 16:58:59 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#undef  ooc_OpenImplementation
#define ooc_CloseImplementation <ooc/ooc/scope/impl_c.h>

#include ooc__MethodsDefine

#define ooc_override(mthd) \
  ooc_override2(mthd, mthd)

#define ooc_override2(mthd1, mthd2) \
  (ooc_classDesc(CLASS)->mthd1 = ooc_methodName(mthd2))

#define ooc_inhibit(mthd) \
  (*(void (**)(Object))&ooc_classDesc(CLASS)->mthd = ooc_methodInhibited);

#define ooc_overrideMemServices(mmsrv) \
  (*(struct ooc_memsrv**)&ooc_classMemSrv(ooc_classDesc(CLASS)) = (mmsrv))

#define ooc_extendImplementation(func)		\
  { extern void ooc_methodName(func)(void);	\
    ooc_methodName(func)(); }

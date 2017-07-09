/* multiple inclusion allowed */

/*
 ******************************
 * Method initialization
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: mthd_ini.h,v 1.3 2005/11/15 14:36:35 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#ifdef ooc_method0_
#include ooc__MethodsClear
#endif

#define      SELF      TYPE
#define constSELF constTYPE

#define ooc_methodName(mthd) OOC_CAT3(ooc_classDesc(CLASS),_,mthd)

#if OOC_GNU_C /* GCC */

#define ooc_methodn_(ret, mthd, args...) \
    (ret OOC_AMS (*)(args))ooc_methodPureVirtual,

#elif OOC_VA_MACROS /* C99 */

#define ooc_methodn_(ret, mthd, ...) \
    (ret OOC_AMS (*)(__VA_ARGS__))ooc_methodPureVirtual,

#else /* C89 */

#define ooc_methodn_  (this should trig a compilation error)

#endif

#define ooc_method0_(ret, mthd, a0) \
   (ret OOC_AMS (*)(a0))ooc_methodPureVirtual,
#define ooc_method1_(ret, mthd, a0,a1) \
   (ret OOC_AMS (*)(a0,a1))ooc_methodPureVirtual,
#define ooc_method2_(ret, mthd, a0,a1,a2) \
   (ret OOC_AMS (*)(a0,a1,a2))ooc_methodPureVirtual,
#define ooc_method3_(ret, mthd, a0,a1,a2,a3) \
   (ret OOC_AMS (*)(a0,a1,a2,a3))ooc_methodPureVirtual,
#define ooc_method4_(ret, mthd, a0,a1,a2,a3,a4) \
   (ret OOC_AMS (*)(a0,a1,a2,a3,a4))ooc_methodPureVirtual,
#define ooc_method5_(ret, mthd, a0,a1,a2,a3,a4,a5) \
   (ret OOC_AMS (*)(a0,a1,a2,a3,a4,a5))ooc_methodPureVirtual,
#define ooc_method6_(ret, mthd, a0,a1,a2,a3,a4,a5,a6) \
   (ret OOC_AMS (*)(a0,a1,a2,a3,a4,a5,a6))ooc_methodPureVirtual,
#define ooc_method7_(ret, mthd, a0,a1,a2,a3,a4,a5,a6,a7) \
   (ret OOC_AMS (*)(a0,a1,a2,a3,a4,a5,a6,a7))ooc_methodPureVirtual,
#define ooc_method8_(ret, mthd, a0,a1,a2,a3,a4,a5,a6,a7,a8) \
   (ret OOC_AMS (*)(a0,a1,a2,a3,a4,a5,a6,a7,a8))ooc_methodPureVirtual,
#define ooc_method9_(ret, mthd, a0,a1,a2,a3,a4,a5,a6,a7,a8,a9) \
   (ret OOC_AMS (*)(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9))ooc_methodPureVirtual,

#define ooc_smethod0_  ooc_method0_
#define ooc_smethod1_  ooc_method0_
#define ooc_smethod2_  ooc_method1_
#define ooc_smethod3_  ooc_method2_
#define ooc_smethod4_  ooc_method3_
#define ooc_smethod5_  ooc_method4_
#define ooc_smethod6_  ooc_method5_
#define ooc_smethod7_  ooc_method6_
#define ooc_smethod8_  ooc_method7_
#define ooc_smethod9_  ooc_method8_
#define ooc_smethodn_  ooc_methodn_

/* multiple inclusion allowed */

/*
 ******************************
 * Method definition
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: mthd_def.h,v 1.3 2005/11/15 14:36:35 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#ifdef ooc_method0_
#include ooc__MethodsClear
#endif

#define      SELF restrict      TYPE self
#define constSELF restrict constTYPE self

#define ooc_methodName(mthd) OOC_CAT3(ooc_classDesc(CLASS),_,mthd)

#if OOC_GNU_C /* GCC */

#define ooc_methodn_(ret, mthd, args...) \
       static ret mthd OOC_AMS (args)

#elif OOC_VA_MACROS /* C99 */

#define ooc_methodn_(ret, mthd, ...) \
       static ret mthd OOC_AMS (__VA_ARGS__)

#else /* C89 */

#define ooc_methodn_ (this should trig a compilation error)

#endif

#define ooc_method0_(ret, mthd, a0)\
       static ret mthd OOC_AMS (a0)
#define ooc_method1_(ret, mthd, a0,a1)\
       static ret mthd OOC_AMS (a0,a1)
#define ooc_method2_(ret, mthd, a0,a1,a2)\
       static ret mthd OOC_AMS (a0,a1,a2)
#define ooc_method3_(ret, mthd, a0,a1,a2,a3)\
       static ret mthd OOC_AMS (a0,a1,a2,a3)
#define ooc_method4_(ret, mthd, a0,a1,a2,a3,a4)\
       static ret mthd OOC_AMS (a0,a1,a2,a3,a4)
#define ooc_method5_(ret, mthd, a0,a1,a2,a3,a4,a5)\
       static ret mthd OOC_AMS (a0,a1,a2,a3,a4,a5)
#define ooc_method6_(ret, mthd, a0,a1,a2,a3,a4,a5,a6)\
       static ret mthd OOC_AMS (a0,a1,a2,a3,a4,a5,a6)
#define ooc_method7_(ret, mthd, a0,a1,a2,a3,a4,a5,a6,a7)\
       static ret mthd OOC_AMS (a0,a1,a2,a3,a4,a5,a6,a7)
#define ooc_method8_(ret, mthd, a0,a1,a2,a3,a4,a5,a6,a7,a8)\
       static ret mthd OOC_AMS (a0,a1,a2,a3,a4,a5,a6,a7,a8)
#define ooc_method9_(ret, mthd, a0,a1,a2,a3,a4,a5,a6,a7,a8,a9)\
       static ret mthd OOC_AMS (a0,a1,a2,a3,a4,a5,a6,a7,a8,a9)

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

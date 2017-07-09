#ifndef OOC_OOC_OOC_H
#error "libooc: use ooc/ooc/ooc.h instead of ooc/ooc/mthds.h directly"
#endif 

/*
 ******************************
 * Method prototypes
 * -----
 * Object Oriented C progamming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: mthds.h,v 1.2 2005/11/15 14:36:35 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

/*
 * Generic macros (variadic)
 */

#if OOC_GNU_C /* GCC */

#define ooc_method(ret, args...) \
  OOC_CAT(ooc_method, OOC_VA_HAS2P(n,0,args))(ret, args)
#define ooc_constMethod(ret, args...) \
  OOC_CAT(ooc_constMethod, OOC_VA_HAS2P(n,0,args))(ret, args)
#define ooc_staticMethod(ret, args...) \
  OOC_CAT(ooc_staticMethod, OOC_VA_HAS2P(n,0,args))(ret, args)

#define ooc_methodn(ret, mthd, args...) \
  ooc_methodn_(ret, ooc_methodName(mthd), SELF, args)
#define ooc_constMethodn(ret, mthd, args...) \
  ooc_methodn_(ret, ooc_methodName(mthd), constSELF, args)
#define ooc_staticMethodn(ret, mthd, args...) \
  ooc_smethodn_(ret, ooc_methodName(mthd), args)

#elif OOC_VA_MACROS /* C99 */

#define ooc_method(ret, ...) \
  OOC_CAT(ooc_method, OOC_VA_HAS2P(n,0,__VA_ARGS__))(ret, __VA_ARGS__)
#define ooc_constMethod(ret, ...) \
  OOC_CAT(ooc_constMethod, OOC_VA_HAS2P(n,0,__VA_ARGS__))(ret, __VA_ARGS__)
#define ooc_staticMethod(ret, ...) \
  OOC_CAT(ooc_staticMethod, OOC_VA_HAS2P(n,0,__VA_ARGS__))(ret, __VA_ARGS__)

#define ooc_methodn(ret, mthd, ...) \
  ooc_methodn_(ret, ooc_methodName(mthd), SELF, __VA_ARGS__)
#define ooc_constMethodn(ret, mthd, ...) \
  ooc_methodn_(ret, ooc_methodName(mthd), constSELF, __VA_ARGS__)
#define ooc_staticMethodn(ret, mthd, ...) \
  ooc_smethodn_(ret, ooc_methodName(mthd), __VA_ARGS__)

#else /* C89 */

#define ooc_method        (this should trig a compilation error)
#define ooc_constMethod	  (this should trig a compilation error)
#define ooc_staticMethod  (this should trig a compilation error)

#define ooc_methodn       (this should trig a compilation error)
#define ooc_constMethodn  (this should trig a compilation error)
#define ooc_staticMethodn (this should trig a compilation error)

#endif

#define ooc_method0(ret,          mthd       )\
 ooc_method0_(ret, ooc_methodName(mthd), SELF)
#define ooc_method1(ret,          mthd ,       a1)\
 ooc_method1_(ret, ooc_methodName(mthd), SELF, a1)
#define ooc_method2(ret,          mthd ,       a1,a2)\
 ooc_method2_(ret, ooc_methodName(mthd), SELF, a1,a2)
#define ooc_method3(ret,          mthd ,       a1,a2,a3)\
 ooc_method3_(ret, ooc_methodName(mthd), SELF, a1,a2,a3)
#define ooc_method4(ret,          mthd ,       a1,a2,a3,a4)\
 ooc_method4_(ret, ooc_methodName(mthd), SELF, a1,a2,a3,a4)
#define ooc_method5(ret,          mthd ,       a1,a2,a3,a4,a5)\
 ooc_method5_(ret, ooc_methodName(mthd), SELF, a1,a2,a3,a4,a5)
#define ooc_method6(ret,          mthd ,       a1,a2,a3,a4,a5,a6)\
 ooc_method6_(ret, ooc_methodName(mthd), SELF, a1,a2,a3,a4,a5,a6)
#define ooc_method7(ret,          mthd ,       a1,a2,a3,a4,a5,a6,a7)\
 ooc_method7_(ret, ooc_methodName(mthd), SELF, a1,a2,a3,a4,a5,a6,a7)
#define ooc_method8(ret,          mthd ,       a1,a2,a3,a4,a5,a6,a7,a8)\
 ooc_method8_(ret, ooc_methodName(mthd), SELF, a1,a2,a3,a4,a5,a6,a7,a8)
#define ooc_method9(ret,          mthd ,       a1,a2,a3,a4,a5,a6,a7,a8,a9)\
 ooc_method9_(ret, ooc_methodName(mthd), SELF, a1,a2,a3,a4,a5,a6,a7,a8,a9)

#define ooc_constMethod0(ret,     mthd            )\
 ooc_method0_(ret, ooc_methodName(mthd), constSELF)
#define ooc_constMethod1(ret,     mthd ,            a1)\
 ooc_method1_(ret, ooc_methodName(mthd), constSELF, a1)
#define ooc_constMethod2(ret,     mthd ,            a1,a2)\
 ooc_method2_(ret, ooc_methodName(mthd), constSELF, a1,a2)
#define ooc_constMethod3(ret,     mthd ,            a1,a2,a3)\
 ooc_method3_(ret, ooc_methodName(mthd), constSELF, a1,a2,a3)
#define ooc_constMethod4(ret,     mthd ,            a1,a2,a3,a4)\
 ooc_method4_(ret, ooc_methodName(mthd), constSELF, a1,a2,a3,a4)
#define ooc_constMethod5(ret,     mthd ,            a1,a2,a3,a4,a5)\
 ooc_method5_(ret, ooc_methodName(mthd), constSELF, a1,a2,a3,a4,a5)
#define ooc_constMethod6(ret,     mthd ,            a1,a2,a3,a4,a5,a6)\
 ooc_method6_(ret, ooc_methodName(mthd), constSELF, a1,a2,a3,a4,a5,a6)
#define ooc_constMethod7(ret,     mthd ,            a1,a2,a3,a4,a5,a6,a7)\
 ooc_method7_(ret, ooc_methodName(mthd), constSELF, a1,a2,a3,a4,a5,a6,a7)
#define ooc_constMethod8(ret,     mthd ,            a1,a2,a3,a4,a5,a6,a7,a8)\
 ooc_method8_(ret, ooc_methodName(mthd), constSELF, a1,a2,a3,a4,a5,a6,a7,a8)
#define ooc_constMethod9(ret,     mthd ,            a1,a2,a3,a4,a5,a6,a7,a8,a9)\
 ooc_method9_(ret, ooc_methodName(mthd), constSELF, a1,a2,a3,a4,a5,a6,a7,a8,a9)

#define ooc_staticMethod0(ret,     mthd  )\
 ooc_smethod0_(ret, ooc_methodName(mthd), void)
#define ooc_staticMethod1(ret,     mthd , a1)\
 ooc_smethod1_(ret, ooc_methodName(mthd), a1)
#define ooc_staticMethod2(ret,     mthd , a1,a2)\
 ooc_smethod2_(ret, ooc_methodName(mthd), a1,a2)
#define ooc_staticMethod3(ret,     mthd , a1,a2,a3)\
 ooc_smethod3_(ret, ooc_methodName(mthd), a1,a2,a3)
#define ooc_staticMethod4(ret,     mthd , a1,a2,a3,a4)\
 ooc_smethod4_(ret, ooc_methodName(mthd), a1,a2,a3,a4)
#define ooc_staticMethod5(ret,     mthd , a1,a2,a3,a4,a5)\
 ooc_smethod5_(ret, ooc_methodName(mthd), a1,a2,a3,a4,a5)
#define ooc_staticMethod6(ret,     mthd , a1,a2,a3,a4,a5,a6)\
 ooc_smethod6_(ret, ooc_methodName(mthd), a1,a2,a3,a4,a5,a6)
#define ooc_staticMethod7(ret,     mthd , a1,a2,a3,a4,a5,a6,a7)\
 ooc_smethod7_(ret, ooc_methodName(mthd), a1,a2,a3,a4,a5,a6,a7)
#define ooc_staticMethod8(ret,     mthd , a1,a2,a3,a4,a5,a6,a7,a8)\
 ooc_smethod8_(ret, ooc_methodName(mthd), a1,a2,a3,a4,a5,a6,a7,a8)
#define ooc_staticMethod9(ret,     mthd , a1,a2,a3,a4,a5,a6,a7,a8,a9)\
 ooc_smethod9_(ret, ooc_methodName(mthd), a1,a2,a3,a4,a5,a6,a7,a8,a9)

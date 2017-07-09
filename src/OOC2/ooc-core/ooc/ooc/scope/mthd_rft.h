/* multiple inclusion allowed */

/*
 ******************************
 * Method reflection
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: mthd_rft.h,v 1.6 2006/11/27 17:18:29 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#ifdef ooc_method0_
#include ooc__MethodsClear
#endif

#define      SELF "W"
#define constSELF "R"

#define ooc_methodName(mthd) mthd

#define ooc_methodMakeMeta(T, mthd, Q, cnt, P)				\
  { "\000" OOC_STR(T) "\000" OOC_STR(P) "\000" Q OOC_STR(mthd) +	\
    sizeof(OOC_STR(T) "\000" OOC_STR(P) "\000" Q),			\
    0,  offsetof(struct OOC_CAT(class,CLASS), mthd), 0, cnt },

#if OOC_GNU_C /* GCC */

#define ooc_methodn_(ret, mthd, self, args...)		\
  ooc_methodMakeMeta(ret, mthd, self, -1, (args))
#define ooc_smethodn_(ret, mthd, args...)		\
  ooc_methodMakeMeta(ret, mthd,  "S", -1, (args))

#elif OOC_VA_MACROS /* C99 */

#define ooc_methodn_(ret, mthd, self, ...)			\
  ooc_methodMakeMeta(ret, mthd, self, -1, (__VA_ARGS__))
#define ooc_smethodn_(ret, mthd, ...)				\
  ooc_methodMakeMeta(ret, mthd,  "S", -1, (__VA_ARGS__))

#else /* C89 */

#define ooc_methodn_()  (this should trig a compilation error)
#define ooc_smethodn_() (this should trig a compilation error)

#endif

#define ooc_method0_(ret, mthd, self      )\
  ooc_methodMakeMeta(ret, mthd, self,  1, (void))
#define ooc_method1_(ret, mthd, self,      a1)\
  ooc_methodMakeMeta(ret, mthd, self,  2, (a1))
#define ooc_method2_(ret, mthd, self,      a1,a2)\
  ooc_methodMakeMeta(ret, mthd, self,  3, (a1,a2))
#define ooc_method3_(ret, mthd, self,      a1,a2,a3)\
  ooc_methodMakeMeta(ret, mthd, self,  4, (a1,a2,a3))
#define ooc_method4_(ret, mthd, self,      a1,a2,a3,a4)\
  ooc_methodMakeMeta(ret, mthd, self,  5, (a1,a2,a3,a4))
#define ooc_method5_(ret, mthd, self,      a1,a2,a3,a4,a5)\
  ooc_methodMakeMeta(ret, mthd, self,  6, (a1,a2,a3,a4,a5))
#define ooc_method6_(ret, mthd, self,      a1,a2,a3,a4,a5,a6)\
  ooc_methodMakeMeta(ret, mthd, self,  7, (a1,a2,a3,a4,a5,a6))
#define ooc_method7_(ret, mthd, self,      a1,a2,a3,a4,a5,a6,a7)\
  ooc_methodMakeMeta(ret, mthd, self,  8, (a1,a2,a3,a4,a5,a6,a7))
#define ooc_method8_(ret, mthd, self,      a1,a2,a3,a4,a5,a6,a7,a8)\
  ooc_methodMakeMeta(ret, mthd, self,  9, (a1,a2,a3,a4,a5,a6,a7,a8))
#define ooc_method9_(ret, mthd, self,      a1,a2,a3,a4,a5,a6,a7,a8,a9)\
  ooc_methodMakeMeta(ret, mthd, self, 10, (a1,a2,a3,a4,a5,a6,a7,a8,a9))

#define ooc_smethod0_(ret, mthd,         _)\
   ooc_methodMakeMeta(ret, mthd, "S", 0, (void))
#define ooc_smethod1_(ret, mthd,          a1)\
   ooc_methodMakeMeta(ret, mthd, "S", 1, (a1))
#define ooc_smethod2_(ret, mthd,          a1,a2)\
   ooc_methodMakeMeta(ret, mthd, "S", 2, (a1,a2))
#define ooc_smethod3_(ret, mthd,          a1,a2,a3)\
   ooc_methodMakeMeta(ret, mthd, "S", 3, (a1,a2,a3))
#define ooc_smethod4_(ret, mthd,          a1,a2,a3,a4)\
   ooc_methodMakeMeta(ret, mthd, "S", 4, (a1,a2,a3,a4))
#define ooc_smethod5_(ret, mthd,          a1,a2,a3,a4,a5)\
   ooc_methodMakeMeta(ret, mthd, "S", 5, (a1,a2,a3,a4,a5))
#define ooc_smethod6_(ret, mthd,          a1,a2,a3,a4,a5,a6)\
   ooc_methodMakeMeta(ret, mthd, "S", 6, (a1,a2,a3,a4,a5,a6))
#define ooc_smethod7_(ret, mthd,          a1,a2,a3,a4,a5,a6,a7)\
   ooc_methodMakeMeta(ret, mthd, "S", 7, (a1,a2,a3,a4,a5,a6,a7))
#define ooc_smethod8_(ret, mthd,          a1,a2,a3,a4,a5,a6,a7,a8)\
   ooc_methodMakeMeta(ret, mthd, "S", 8, (a1,a2,a3,a4,a5,a6,a7,a8))
#define ooc_smethod9_(ret, mthd,          a1,a2,a3,a4,a5,a6,a7,a8,a9)\
   ooc_methodMakeMeta(ret, mthd, "S", 9, (a1,a2,a3,a4,a5,a6,a7,a8,a9))

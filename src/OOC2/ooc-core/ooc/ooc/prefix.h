#ifndef OOC_OOC_OOC_H
#error "libooc: use ooc/ooc/ooc.h instead of ooc/ooc/prefix.h directly"
#endif 

/*
 ******************************
 * Prefix handler
 * -----
 * Object Oriented C progamming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: prefix.h,v 1.8 2005/12/15 16:58:59 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

/*
 * -------------------------
 *  Prefix handler
 * -------------------------
 */

#ifdef USING_OOC

/*
 * Namespace
 */

#define Interface		      ooc_Interface
#define Implementation	              ooc_Implementation
#define ImplementationExtension       ooc_ImplementationExtension
#define End                           ooc_End

#define OpenScope                     ooc_OpenScope
#define OpenInterface                 ooc_OpenInterface
#define OpenImplementation            ooc_OpenImplementation
#define OpenImplementationExtension   ooc_OpenImplementationExtension

#define CloseScope                    ooc_CloseScope
#define CloseInterface                ooc_CloseInterface
#define CloseImplementation           ooc_CloseImplementation
#define CloseImplementationExtension  ooc_CloseImplementationExtension

/*
 * Interface and implementation
 */

#if OOC_GNU_C /* GCC */

#define method(args...)                     ooc_method(args)
#define constMethod(args...)                ooc_constMethod(args)
#define staticMethod(args...)               ooc_staticMethod(args)

#define methodn(args...)                    ooc_methodn(args)
#define constMethodn(args...)               ooc_constMethodn(args)
#define staticMethodn(args...)              ooc_staticMethodn(args)

#elif OOC_VA_MACROS /* C99 */

#define method(...)                         ooc_method(__VA_ARGS__)
#define constMethod(...)                    ooc_constMethod(__VA_ARGS__)
#define staticMethod(...)                   ooc_staticMethod(__VA_ARGS__)

#define methodn(...)                        ooc_methodn(__VA_ARGS__)
#define constMethodn(...)                   ooc_constMethodn(__VA_ARGS__)
#define staticMethodn(...)                  ooc_staticMethodn(__VA_ARGS__)

#endif

#define method0(r,m)                        ooc_method0(r,m)
#define method1(r,m,a)                      ooc_method1(r,m,a)
#define method2(r,m,a,b)                    ooc_method2(r,m,a,b)
#define method3(r,m,a,b,c)                  ooc_method3(r,m,a,b,c)
#define method4(r,m,a,b,c,d)                ooc_method4(r,m,a,b,c,d)
#define method5(r,m,a,b,c,d,e)              ooc_method5(r,m,a,b,c,d,e)
#define method6(r,m,a,b,c,d,e,f)            ooc_method6(r,m,a,b,c,d,e,f)
#define method7(r,m,a,b,c,d,e,f,g)          ooc_method7(r,m,a,b,c,d,e,f,g)
#define method8(r,m,a,b,c,d,e,f,g,h)        ooc_method8(r,m,a,b,c,d,e,f,g,h)
#define method9(r,m,a,b,c,d,e,f,g,h,i)      ooc_method9(r,m,a,b,c,d,e,f,g,h,i)

#define constMethod0(r,m)                   ooc_constMethod0(r,m)
#define constMethod1(r,m,a)                 ooc_constMethod1(r,m,a)
#define constMethod2(r,m,a,b)               ooc_constMethod2(r,m,a,b)
#define constMethod3(r,m,a,b,c)             ooc_constMethod3(r,m,a,b,c)
#define constMethod4(r,m,a,b,c,d)           ooc_constMethod4(r,m,a,b,c,d)
#define constMethod5(r,m,a,b,c,d,e)         ooc_constMethod5(r,m,a,b,c,d,e)
#define constMethod6(r,m,a,b,c,d,e,f)       ooc_constMethod6(r,m,a,b,c,d,e,f)
#define constMethod7(r,m,a,b,c,d,e,f,g)     ooc_constMethod7(r,m,a,b,c,d,e,f,g)
#define constMethod8(r,m,a,b,c,d,e,f,g,h)   ooc_constMethod8(r,m,a,b,c,d,e,f,g,h)
#define constMethod9(r,m,a,b,c,d,e,f,g,h,i) ooc_constMethod9(r,m,a,b,c,d,e,f,g,h,i)

#define staticMethod0(r,m)                   ooc_staticMethod0(r,m)
#define staticMethod1(r,m,a)                 ooc_staticMethod1(r,m,a)
#define staticMethod2(r,m,a,b)               ooc_staticMethod2(r,m,a,b)
#define staticMethod3(r,m,a,b,c)             ooc_staticMethod3(r,m,a,b,c)
#define staticMethod4(r,m,a,b,c,d)           ooc_staticMethod4(r,m,a,b,c,d)
#define staticMethod5(r,m,a,b,c,d,e)         ooc_staticMethod5(r,m,a,b,c,d,e)
#define staticMethod6(r,m,a,b,c,d,e,f)       ooc_staticMethod6(r,m,a,b,c,d,e,f)
#define staticMethod7(r,m,a,b,c,d,e,f,g)     ooc_staticMethod7(r,m,a,b,c,d,e,f,g)
#define staticMethod8(r,m,a,b,c,d,e,f,g,h)   ooc_staticMethod8(r,m,a,b,c,d,e,f,g,h)
#define staticMethod9(r,m,a,b,c,d,e,f,g,h,i) ooc_staticMethod9(r,m,a,b,c,d,e,f,g,h,i)

#define inhibit(a)                 ooc_inhibit(a)
#define override(a)                ooc_override(a)
#define override2(a,b)             ooc_override2(a,b)
#define overrideMemServices(a)     ooc_overrideMemServices(a)
#define extendImplementation(a)    ooc_extendImplementation(a)
#define implementationExtension(a) ooc_implementationExtension(a)

#define   public(a,b)     ooc_public(a,b)
#define  visible(a,b)    ooc_visible(a,b)
#define  private(a,b)    ooc_private(a,b)
#define  publicN(a,b,c)  ooc_publicN(a,b,c)
#define visibleN(a,b,c) ooc_visibleN(a,b,c)
#define privateN(a,b,c) ooc_privateN(a,b,c)
#define  publicP(a,b,c)  ooc_publicP(a,b,c)
#define visibleP(a,b,c) ooc_visibleP(a,b,c)
#define privateP(a,b,c) ooc_privateP(a,b,c)

/*
 * Class
 */

#define Class(a)         ooc_Class(a)

/*
 * Exception
 */

#define try              ooc_try
#define catch(a,b)       ooc_catch(a,b)
#define endTry           ooc_endTry

#define throw(a)         ooc_throw(a)
#define throwLoc(a,b,c)  ooc_throwLoc(a,b,c)
#define rethrow(a)       ooc_rethrow(a)

#define protectPtr(a,b)  ooc_protectPtr(a,b)
#define unprotectPtr(a)  ooc_unprotectPtr(a)

/*
 * Calls
 */

#if OOC_GNU_C /* GCC */

#define call( args...)  ooc_call  (args)
#define pcall(args...)  ooc_pcall (args)
#define scall(args...)  ooc_scall (args)

#define calln( args...) ooc_calln (args)
#define pcalln(args...) ooc_pcalln(args)
#define scalln(args...) ooc_scalln(args)

#elif OOC_VA_MACROS /* C99 */

#define call( ...)  ooc_call  (__VA_ARGS__)
#define pcall(...)  ooc_pcall (__VA_ARGS__)
#define scall(...)  ooc_scall (__VA_ARGS__)

#define calln( ...) ooc_calln (__VA_ARGS__)
#define pcalln(...) ooc_pcalln(__VA_ARGS__)
#define scalln(...) ooc_scalln(__VA_ARGS__)

#endif

#define call0(s,m)                      ooc_call0(s,m)
#define call1(s,m,a)                    ooc_call1(s,m,a)
#define call2(s,m,a,b)                  ooc_call2(s,m,a,b)
#define call3(s,m,a,b,c)                ooc_call3(s,m,a,b,c)
#define call4(s,m,a,b,c,d)              ooc_call4(s,m,a,b,c,d)
#define call5(s,m,a,b,c,d,e)            ooc_call5(s,m,a,b,c,d,e)
#define call6(s,m,a,b,c,d,e,f)          ooc_call6(s,m,a,b,c,d,e,f)
#define call7(s,m,a,b,c,d,e,f,g)        ooc_call7(s,m,a,b,c,d,e,f,g)
#define call8(s,m,a,b,c,d,e,f,g,h)      ooc_call8(s,m,a,b,c,d,e,f,g,h)
#define call9(s,m,a,b,c,d,e,f,g,h,i)    ooc_call9(s,m,a,b,c,d,e,f,g,h,i)

#define pcall0(s,p,m)                   ooc_pcall0(s,p,m)
#define pcall1(s,p,m,a)                 ooc_pcall1(s,p,m,a)
#define pcall2(s,p,m,a,b)               ooc_pcall2(s,p,m,a,b)
#define pcall3(s,p,m,a,b,c)             ooc_pcall3(s,p,m,a,b,c)
#define pcall4(s,p,m,a,b,c,d)           ooc_pcall4(s,p,m,a,b,c,d)
#define pcall5(s,p,m,a,b,c,d,e)         ooc_pcall5(s,p,m,a,b,c,d,e)
#define pcall6(s,p,m,a,b,c,d,e,f)       ooc_pcall6(s,p,m,a,b,c,d,e,f)
#define pcall7(s,p,m,a,b,c,d,e,f,g)     ooc_pcall7(s,p,m,a,b,c,d,e,f,g)
#define pcall8(s,p,m,a,b,c,d,e,f,g,h)   ooc_pcall8(s,p,m,a,b,c,d,e,f,g,h)
#define pcall9(s,p,m,a,b,c,d,e,f,g,h,i) ooc_pcall9(s,p,m,a,b,c,d,e,f,g,h,i)

#define scall0(m)                       ooc_scall0(m)
#define scall1(m,a)                     ooc_scall1(m,a)
#define scall2(m,a,b)                   ooc_scall2(m,a,b)
#define scall3(m,a,b,c)                 ooc_scall3(m,a,b,c)
#define scall4(m,a,b,c,d)               ooc_scall4(m,a,b,c,d)
#define scall5(m,a,b,c,d,e)             ooc_scall5(m,a,b,c,d,e)
#define scall6(m,a,b,c,d,e,f)           ooc_scall6(m,a,b,c,d,e,f)
#define scall7(m,a,b,c,d,e,f,g)         ooc_scall7(m,a,b,c,d,e,f,g)
#define scall8(m,a,b,c,d,e,f,g,h)       ooc_scall8(m,a,b,c,d,e,f,g,h)
#define scall9(m,a,b,c,d,e,f,g,h,i)     ooc_scall9(m,a,b,c,d,e,f,g,h,i)

#endif /* USING_OOC */

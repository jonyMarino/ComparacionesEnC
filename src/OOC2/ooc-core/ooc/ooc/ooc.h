#ifndef OOC_OOC_OOC_H
#define OOC_OOC_OOC_H

/*
 ******************************
 * OOC Core
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: ooc.h,v 1.10 2005/12/14 18:35:05 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -------------------------
 *  ISO C Compliance
 * -------------------------
 */

#ifndef __STDC__
#error "libooc: OOC needs an ISO C compiler to work properly"
#endif

#ifdef __STDC_VERSION__
#define OOC_ISO_C   __STDC_VERSION__
#else
#define OOC_ISO_C   OOC_ISO_C90
#endif

#define OOC_ISO_C90 199000L /* ISO/IEC 9899:1990   */
#define OOC_ISO_C95 199409L /* ISO/IEC 9899:199409 */
#define OOC_ISO_C99 199901L /* ISO/IEC 9899:199901 */

/*
 * -------------------------
 *  OOC Config
 * -------------------------
 */

#include <ooc/config_ooc.h>
#include <ooc/ooc/setup.h>

/*
 * -------------------------
 *  Standard includes
 * -------------------------
 */

#include <stddef.h>
#include <limits.h>
#include <setjmp.h>

/*
 * -------------------------
 *  OOC Core
 * -------------------------
 */

#include <ooc/ooc/utils.h>
#include <ooc/ooc/types.h>
#include <ooc/ooc/error.h>
#include <ooc/ooc/alloc.h>
#include <ooc/ooc/mmsrv.h>
#include <ooc/ooc/excpt.h>
#include <ooc/ooc/cldef.h>
#include <ooc/ooc/class.h>
#include <ooc/ooc/mthds.h>
#include <ooc/ooc/calls.h>
#include <ooc/ooc/prefix.h>

#ifdef __cplusplus
}
#endif

/*
 * -------------------------
 *  OOC scope
 * -------------------------
 */

#define ooc_Interface                    ooc_OpenInterface
#define ooc_Implementation               ooc_OpenImplementation
#define ooc_ImplementationExtension      ooc_OpenImplementationExtension
#define ooc_End                          <ooc/ooc/scope/end.h>

#define ooc_OpenScope                    <ooc/ooc/scope/scop_o.h>
#define ooc_OpenInterface                <ooc/ooc/scope/intf_o.h>
#define ooc_OpenImplementation           <ooc/ooc/scope/impl_o.h>
#define ooc_OpenImplementationExtension  <ooc/ooc/scope/impl_oe.h>

#define ooc__ClassDeclare                <ooc/ooc/scope/clss_dcl.h>
#define ooc__ClassReflect                <ooc/ooc/scope/clss_rft.h>
#define ooc__ClassClear                  <ooc/ooc/scope/clss_clr.h>
#define ooc__ClassInfo                   <ooc/ooc/scope/clss_inf.h>

#define ooc__TypeDeclare                 <ooc/ooc/scope/type_dcl.h>
#define ooc__TypeAsObject                <ooc/ooc/scope/type_obj.h>
#define ooc__TypeAsCLASS                 <ooc/ooc/scope/type_cls.h>
#define ooc__TypeAsROOT                  <ooc/ooc/scope/type_rcl.h>
#define ooc__TypeClear                   <ooc/ooc/scope/type_clr.h>

#define ooc__PrivacyEnable               <ooc/ooc/scope/prvt_on.h>
#define ooc__PrivacyDisable              <ooc/ooc/scope/prvt_off.h>
#define ooc__PrivacyNullify              <ooc/ooc/scope/prvt_nul.h>
#define ooc__PrivacyReflect              <ooc/ooc/scope/prvt_rft.h>
#define ooc__PrivacyClear                <ooc/ooc/scope/prvt_clr.h>

#define ooc__MethodsDefine               <ooc/ooc/scope/mthd_def.h>
#define ooc__MethodsDeclare              <ooc/ooc/scope/mthd_dcl.h>
#define ooc__MethodsNullify              <ooc/ooc/scope/mthd_nul.h>
#define ooc__MethodsReflect              <ooc/ooc/scope/mthd_rft.h>
#define ooc__MethodsInitialize           <ooc/ooc/scope/mthd_ini.h>
#define ooc__MethodsClear                <ooc/ooc/scope/mthd_clr.h>

#define ooc__ProtodefsDeclare            <ooc/ooc/scope/prtd_dcl.h>
#define ooc__ProtodefsNullify            <ooc/ooc/scope/prtd_nul.h>
#define ooc__ProtodefsMeta               <ooc/ooc/scope/prtd_met.h>
#define ooc__ProtodefsReflect            <ooc/ooc/scope/prtd_rft.h>
#define ooc__ProtodefsInitialize         <ooc/ooc/scope/prtd_ini.h>
#define ooc__ProtodefsClear              <ooc/ooc/scope/prtd_clr.h>

#define ooc__MetaEnable                  <ooc/ooc/scope/meta_on.h>
#define ooc__MetaDisable                 <ooc/ooc/scope/meta_off.h>
#define ooc__MetaClear                   <ooc/ooc/scope/meta_clr.h>

#define ooc__InitializeDefine            <ooc/ooc/scope/init_def.h>

#endif /* OOC_OOC_OOC_H */

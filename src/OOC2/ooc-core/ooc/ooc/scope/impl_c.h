/* multiple inclusion allowed */

/*
 ******************************
 * Implementation closing
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: impl_c.h,v 1.12 2006/11/27 16:59:38 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#undef  ooc_CloseImplementation
#define ooc_OpenImplementation <ooc/ooc/scope/impl_o.h>

#undef ooc_inhibit
#undef ooc_override 
#undef ooc_override2
#undef ooc_overrideMemServices
#undef ooc_extendImplementation

#ifndef ooc_CloseImplementationExtension

/*
 * Class pre initialization
 */

#include ooc__InitializeDefine

/*
 * Class initialization
 */

#if defined(PROTOCOL)
#include ooc__MetaDisable
#else
#include ooc__MetaEnable
#endif

#include ooc__PrivacyNullify
#include ooc__MethodsInitialize
#include ooc__ProtodefsInitialize

/* dataCLASS */

static struct OOC_CAT(data,META_CLASS)
     OOC_CAT(ooc_classDesc(CLASS),_data__)[1] = {{
  OOC_CATD_(CLASSINIT_,META_CLASS)
}};

/* classCLASS */

struct OOC_CAT(class,CLASS) ooc_classDesc(CLASS)[1] = {{
  ooc_classDesc(META_CLASS),                      /* _isa         */
  0,                                              /* _cnt         */
#ifdef SUPER_CLASS                                /* _spr         */
  ooc_classDesc(SUPER_CLASS),
#else
  0,
#endif
  OOC_CAT(ooc_classDesc(CLASS),_data__),          /* _dat         */
#if OOC_THREAD_USE
  ooc_methodName(_once__),                        /* _init        */
#endif
  ooc_methodName(initialize),                     /* initialize   */
  ooc_methodDoNothing,                            /* deinitialize */
#ifdef METACLASS                                  /* init         */
  ooc_methodName(init),
#else
  (TYPE OOC_AMS (*)(TYPE))ooc_methodPureVirtual,
#endif
  (void(*)(TYPE))         ooc_methodPureVirtual,  /* deinit       */
  (Object   OOC_AMS (*)(TYPE, classObject  ))
                          ooc_methodPureVirtual,  /* cast         */
  (Protocol OOC_AMS (*)(TYPE, classProtocol))
                          ooc_methodPureVirtual,  /* pcast        */

#ifndef PROTOCOL
  OOC_CATD_(CLASSDEF_,CLASS)
#endif
}};

#include ooc__ProtodefsClear
#include ooc__MethodsClear
#include ooc__PrivacyClear
#include ooc__MetaClear

#endif /* ooc_CloseImplementationExtension */

#include ooc_CloseScope

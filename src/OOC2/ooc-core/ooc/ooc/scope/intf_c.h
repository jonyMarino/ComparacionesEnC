/* multiple inclusion allowed */

/*
 ******************************
 * Interface closing
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: intf_c.h,v 1.12 2006/11/27 16:59:38 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#undef   ooc_CloseInterface
#define  ooc_OpenInterface <ooc/ooc/scope/intf_o.h>
#include ooc_OpenScope

/*
 * Class typedefs
 */

#if !OOC_CAT(CLASSDECL_,CLASS)
OOC_CLASSDECL(CLASS);
#endif

/*
 * Class members privacy
 */

#ifdef ooc_CloseImplementation
#include ooc__PrivacyDisable
#else
#include ooc__PrivacyEnable
#endif

/*
 * Object type definition
 */

struct CLASS {

#define OOC__ISA const struct OOC_CAT(class,CLASS)*
  CLASSDEF_OOC_AnyObject
#undef  OOC__ISA

#if !defined(PROTOCOL) && !defined(METACLASS) /* -= CLASS =- */

#include ooc__MethodsNullify
#include ooc__ProtodefsNullify

  OOC_CATD_(CLASSDEF_,CLASS)

#elif defined(PROTOCOL)                    /* -= PROTOCOL =- */

#include ooc__TypeAsObject
#include ooc__MethodsDeclare

  OOC_CATD_(PROTODEF_,CLASS)

#include ooc__TypeAsCLASS

#elif defined(METACLASS)                  /* -= METACLASS =- */

#define OOC__SPR const struct classObject*
#define OOC__DAT       struct OOC_CAT(data,CLASS)*
  CLASSDEF_OOC_AnyClass
#undef  OOC__DAT
#undef  OOC__SPR

#include ooc__MethodsDeclare
#include ooc__ProtodefsDeclare

  OOC_CATD_(CLASSDEF_,ROOT_CLASS)

#else /* !CLASS && !PROTOCOL && !METACLASS */
#error "libooc: invalid class instance type definition"
#endif

    /* TODO for inheritance
#if OOC_ISO_C < OOC_ISO_C99
  const char _end_[sizeof(void*)];
#else
  const char _end_[];
#endif
    */
};

/*
 * Class type definition
 */

struct OOC_CAT(class,CLASS) {

#define OOC__ISA const struct OOC_CAT(class, META_CLASS)*
#define OOC__SPR const struct OOC_CAT(class,SUPER_CLASS)*
#define OOC__DAT const struct OOC_CAT(data , META_CLASS)*
  CLASSDEF_OOC_AnyObject
  CLASSDEF_OOC_AnyClass
#undef  OOC__DAT
#undef  OOC__SPR
#undef  OOC__ISA

#if !defined(PROTOCOL)

#include ooc__PrivacyNullify
#include ooc__MethodsDeclare
#include ooc__ProtodefsDeclare

  OOC_CATD_(CLASSDEF_,CLASS)

#endif

};

/*
 * Class data type definition, metaclass only
 */

#if defined(METACLASS)

struct OOC_CAT(data,CLASS) {

#ifdef ooc_CloseImplementation
#include ooc__PrivacyDisable
#else
#include ooc__PrivacyEnable
#endif

#include ooc__MethodsNullify
#include ooc__ProtodefsNullify

  OOC_CATD_(CLASSDEF_,CLASS)

};

#endif /* METACLASS */

extern struct OOC_CAT(class,CLASS) ooc_classDesc(CLASS)[1];

#include ooc__ProtodefsClear
#include ooc__MethodsClear
#include ooc__PrivacyClear

#include ooc__ClassInfo

#ifdef ooc_CloseImplementation
#include ooc__MethodsDefine
#else
#include ooc_CloseScope
#endif

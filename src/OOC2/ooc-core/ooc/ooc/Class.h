#ifndef OOC_OOC_CLASS_H
#define OOC_OOC_CLASS_H

#ifndef OOC_OBJECT_H
#error "libooc: use ooc/Object.h instead of ooc/ooc/Class.h directly"
#endif

/*
 *******************************
 * Class interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Class.h,v 1.12 2006/11/27 16:59:38 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

/*
 * -------------------------
 *  Class interface
 *  Root of all OOC Classes
 * -------------------------
 */

#include ooc_Interface

#define ABSTRACT_METACLASS Class
#define SUPER_CLASS Object

#define CLASSDEF_Class						\
  /* class reflection */					\
 ooc_staticMethod1(constClass , findClass   , const char *name)	\
  ooc_constMethod1(constClass , findSubclass, const char *name)	\
								\
  /* field reflection */					\
  ooc_constMethod0(size_t     , fieldCnt    )			\
  ooc_constMethod1(constField , newField    , const char *name)	\
  ooc_constMethod1(constField , newFieldAt  , size_t idx)	\
								\
  /* method reflection */					\
  ooc_constMethod0(size_t     , methodCnt   )			\
  ooc_constMethod1(constMethod, newMethod   , const char *name)	\
  ooc_constMethod1(constMethod, newMethodAt , size_t idx)	\
								\
  /* dynamic loading */						\
 ooc_staticMethod2(constClass , loadClass   , const char *lib	\
		                            , const char *name)	\
								\
  /* class data */						\
  ooc_visible(size_t             , obj_size)			\
  ooc_visible(size_t             , cls_size)			\
  ooc_visible(unsigned           , info    )			\
  ooc_visible(const char*        , name    )			\
  ooc_visible(struct ooc_memsrv* , memsrv  )			\
  ooc_visible(struct ooc_reflect*, meta    )			\
  ooc_visible(Protocol*          , proto   )			\
  ooc_visible(Class              , next    )			\
  ooc_visible(Class              , sub     )

#define CLASSINIT_Class						\
  sizeof(struct CLASS),                         /* obj_size  */	\
  sizeof(struct OOC_CAT(class,CLASS)),          /* cls_size  */	\
  OOC_CAT(ooc_classDesc(CLASS),_info__),        /* info      */	\
  OOC_STR(CLASS),                               /* name      */	\
  0,                                            /* memsrv    */	\
  OOC_CLASS_META,                               /* meta      */	\
  OOC_PROTO_META,                               /* proto     */	\
  0, 0,                                         /* next, sub */

#include ooc_End

#endif /* OOC_OOC_CLASS_H */

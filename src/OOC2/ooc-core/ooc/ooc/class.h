#ifndef OOC_OOC_OOC_H
#error "libooc: use ooc/ooc/ooc.h instead of ooc/ooc/class.h directly"
#endif 

/*
 ******************************
 * Class accessors
 * -----
 * Object Oriented C progamming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: class.h,v 1.8 2006/11/27 16:59:38 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

/*
 * Class status
 */

#define ooc_classIsAbstract(cls) \
  (OOC_CLASSINFO_GET(cls, OOC_CLASSINFO_ABSTRACT)  != 0)

#define ooc_classIsFinal(cls) \
  (OOC_CLASSINFO_GET(cls, OOC_CLASSINFO_FINAL)     != 0)

#define ooc_classIsMetaClass(cls) \
  (OOC_CLASSINFO_GET(cls, OOC_CLASSINFO_METACLASS) != 0)

#define ooc_classIsProtocol(cls) \
  (OOC_CLASSINFO_GET(cls, OOC_CLASSINFO_PROTOCOL)  != 0)

#define ooc_classIsStatic(cls) \
  (OOC_CLASSINFO_GET(cls, OOC_CLASSINFO_STATIC_CLASS) != 0)

/*
 * Class getter
 */

#define ooc_classSuper(cls)        ((cls)->_spr)
#define ooc_classInstanceSize(cls) ((cls)->_dat->obj_size)
#define ooc_classSize(cls)         ((cls)->_dat->cls_size)
#define ooc_className(cls)         ((cls)->_dat->name)
#define ooc_classInfo(cls)         ((cls)->_dat->info)
#define ooc_classProtocol(cls)     ((cls)->_dat->proto)
#define ooc_classReflect(cls)      ((cls)->_dat->meta)
#define ooc_classMemSrv(cls)       ((cls)->_dat->memsrv)
#define ooc_classNextClass(cls)    ((cls)->_dat->next)
#define ooc_classSubClass(cls)     ((cls)->_dat->sub)

/*
 * Class descriptor
 */

#define ooc_Class(cname) \
       (ooc_classInitialize(cname), ooc_classDesc(cname))

#define ooc_classDesc(cname) \
        OOC_CAT3(ooc_, cname, _)

#define ooc_classDescSymStr(str) \
       "ooc_" str "_"

#if OOC_THREAD_USE
#define ooc_classInitialize(cname) \
        ooc_classDescInitialize(ooc_classDesc(cname))
#define ooc_classDescInitialize(cls) \
        (cls)->_init()
#else
#define ooc_classInitialize(cname) \
        ooc_classDescInitialize(ooc_classDesc(cname))
#define ooc_classDescInitialize(cls)  \
      ((cls)->_cnt ? (void)0 : \
       ooc_classInitialize_(((void)&(cls)->_spr, (void*)(cls))))
#endif /* OOC_THREAD_USE */

void    ooc_classDeinitialize(void);

/*
 * Class information
 */

enum {
  OOC_CLASSINFO_NONE              = 0x0000,

  /* class init */
  OOC_CLASSINFO_INIT              = 0x0001,

  /* class specifier */
  OOC_CLASSINFO_AFMP              = 0x00F0,
  OOC_CLASSINFO_ABSTRACT          = 0x0010,
  OOC_CLASSINFO_FINAL             = 0x0020,
  OOC_CLASSINFO_METACLASS         = 0x0040,
  OOC_CLASSINFO_PROTOCOL          = 0x0080,

  /* class qualifiers */
  OOC_CLASSINFO_STATIC            = 0x0F00,
  OOC_CLASSINFO_STATIC_CLASS      = 0x0100,
  OOC_CLASSINFO_STATIC_PROTO      = 0x0200,
  OOC_CLASSINFO_STATIC_FIELD_RFT  = 0x0400,
  OOC_CLASSINFO_STATIC_METHOD_RFT = 0x0800
};

#define OOC_CLASSINFO_GET(cls, st) \
  (ooc_classInfo(cls) & (st))

#define OOC_CLASSINFO_SET(cls, st) \
  (ooc_classInfo(cls) |= (st))

#define OOC_CLASSINFO_CLR(cls, st) \
  (ooc_classInfo(cls) &= ~(unsigned)(st))

/*
 * Debug services
 */

void ooc_classInheritanceTree(constClass cls); /* to stdout */

/*
 * Special methods
 */

void ooc_methodPureVirtual(Object);
void ooc_methodInhibited  (Object);
void ooc_methodDoNothing  (void);

/*
 * Hidden services
 */

void ooc_classInitialize_(Class cls);

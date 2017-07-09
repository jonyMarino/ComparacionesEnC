/*
 *******************************
 * Class implementation
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Class.c,v 1.28 2006/11/27 16:59:38 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#define USING_OOC

#include <ooc/ooc/ooc.h>
#include <ooc/assert.h>

#include <string.h>
#include <stdlib.h>

OOC_STATIC_ASSERT(sizeof(void*) == sizeof(ooc_function));

/*
 * -------------------------
 *  Class implementation
 * -------------------------
 */

#include Implementation

#include <ooc/Object.h> /* friend classes */
#include <ooc/ooc/lib/pool.h>
#include <ooc/ooc/lib/mem_srv.h>
#include <ooc/utils/memfct.h>
#include <ooc/reflect/staticmeta.h>
#include <ooc/ex/ExBadAlloc.h>

/* reactivate Class scope */
#include CloseScope
#define ABSTRACT_METACLASS Class
#define SUPER_CLASS Object
#include OpenScope

/*
 * Static functions
 */

static inline int
cmp_fld_name(const void *fld1_ , const void *fld2_)
{
  const struct ooc_meta_fld *fld1 = fld1_;
  const struct ooc_meta_fld *fld2 = fld2_;
  
  return strcmp(fld1->name, fld2->name);
}

static inline int
cmp_mth_name(const void *mth1_, const void *mth2_)
{
  const struct ooc_meta_mth *mth1 = mth1_;
  const struct ooc_meta_mth *mth2 = mth2_;

  return strcmp(mth1->name, mth2->name);
}

/*
 * Meta setup
 */

static inline void
sort_fields(Class cls)
{
  struct ooc_reflect *meta = ooc_classReflect(cls);

  if (meta->fld_cnt > 1) {
    size_t i;
    
    for (i = 0; i < meta->fld_cnt; ++i)
      meta->fld[i].type.id = i;
    
    qsort(meta->fld, meta->fld_cnt, sizeof(struct ooc_meta_fld), cmp_fld_name);
    
    for (i = 0; i < meta->fld_cnt; ++i) {
      meta->fld_lut[meta->fld[i].type.id] = i;
      meta->fld[i].type.id = 0;
    }
  }
}

static inline void
sort_methods(Class cls)
{
  struct ooc_reflect *meta = ooc_classReflect(cls);
  
  if (meta->mth_cnt > 1)
    qsort(meta->mth, meta->mth_cnt, sizeof(struct ooc_meta_mth), cmp_mth_name);
}

static inline void
setup_reflect(Class cls)
{
  if (!ooc_classReflect(cls)) {
    Class super = (Class)ooc_classSuper(cls);
    
    if (!super) {
      static struct ooc_reflect sentinel[1] = {{0,0,0,0,0}};

      ooc_classReflect(cls) = sentinel;
      OOC_CLASSINFO_SET(cls, 
			OOC_CLASSINFO_STATIC_FIELD_RFT |
			OOC_CLASSINFO_STATIC_METHOD_RFT);
    } else {
      ooc_classReflect(cls) = ooc_classReflect(super);
      OOC_CLASSINFO_SET(cls,
			OOC_CLASSINFO_GET(super,
					  OOC_CLASSINFO_STATIC_FIELD_RFT |
					  OOC_CLASSINFO_STATIC_METHOD_RFT));
    }
    return;
  }
  
  if (OOC_CLASSINFO_GET(cls, OOC_CLASSINFO_STATIC_FIELD_RFT))
    sort_fields (cls);
  
  if (OOC_CLASSINFO_GET(cls, OOC_CLASSINFO_STATIC_METHOD_RFT))
    sort_methods(cls);
}

/*
 * Protocol setup
 */

static inline void
setup_protocol(Class cls)
{
  Protocol *p = ooc_classProtocol(cls);

  if (!p) {
    static Protocol sentinel[1] = { 0 };
    
    ooc_classProtocol(cls) = sentinel;
    OOC_CLASSINFO_SET(cls, OOC_CLASSINFO_STATIC_PROTO);
    
    return;
  }
  
  for (; *p; p++) {
    ooc_classDescInitialize((*p)->_isa);
      
    if (ooc_classIsAbstract((*p)->_isa))
      ooc_error("implementing abstract protocol %s (check CLASSDEF_%s)",
		ooc_className((*p)->_isa), ooc_className(cls));
    
    call0(*p, init);
  }
}

/*
 * Methods setup
 */

static inline void
setup_methods(Class cls, Class super)
{
  size_t size = ooc_classSize(super) - offsetof(struct Class, init);
  size_t cnt  = size / sizeof(ooc_function);

  ooc_memfct_copy((void*)&  cls->init, (void*)&super->init, cnt);
}

/*
 * Inheritance links
 */

static inline void
setup_inheritance(Class cls, Class super)
{
  ooc_classNextClass(cls) = ooc_classSubClass(super);
  ooc_classSubClass(super) = cls;
}

/*
 * Memory Services setup
 */

static inline void
setup_memsrv(Class cls)
{
  if (ooc_classIsAbstract(cls))
    ooc_classMemSrv(cls) = ooc_memAbsSrv;
#if OOC_GC_USE
  else
    ooc_classMemSrv(cls) = ooc_memGCSrv;
#else
  else
    ooc_classMemSrv(cls) = ooc_page_fitSize(ooc_classInstanceSize(cls))
      ? ooc_memStdSrv
      : ooc_memBigSrv;
#endif
}

/*
 * Initialize setup
 */

static inline void
setup_init(Class cls)
{
  if (!cls->initialize)
    cls->initialize = ooc_methodDoNothing;
  if (!cls->deinitialize)
    cls->deinitialize = ooc_methodDoNothing;

#if OOC_THREAD_USE
  if (!cls->_init)
    cls->_init = ooc_methodDoNothing;
#endif
}

/*
 * Check inheritance
 */

static void
check_metaclass_inheritance(Class cls)
{
  classObject root = cls->_isa->_dat->root;

  ooc_assert(root);

  if (!isClassOf(root, Object) && !isSubclassOfClass(cls, root))
    ooc_abort("invalid metaclass inheritance, %s is not subclass of %s "
	      "(check META_CLASS of %s)", ooc_className(cls),
	      ooc_className(root), ooc_className(cls));
}

static void
check_inheritance(Class cls, Class super)
{
  if (ooc_classIsFinal(super))
    ooc_abort("invalid inheritance, %s inherits of the final class %s "
	      "(check SUPER_CLASS)", ooc_className(cls), ooc_className(super));

  if (ooc_classSize        (super) > ooc_classSize        (cls) ||
      ooc_classInstanceSize(super) > ooc_classInstanceSize(cls))
    ooc_abort("invalid inheritance, size(%s) > size(%s) (check SUPER_CLASS)",
	      ooc_className(super), ooc_className(cls));

  if (!isSubclassOfClass(cls->_isa, super->_isa))
    ooc_abort("invalid metaclass inheritance, %s is not subclass of %s "
	      "(check META_CLASS of %s)", ooc_className(cls->_isa),
	      ooc_className(super->_isa), ooc_className(cls));

  if ((ooc_classSize(cls) - ooc_classSize(super)) % sizeof(ooc_function))
    ooc_abort("invalid class methods table, size(methods) %% size(method) > 0 "
	      "(check CLASSDEF_%s)", ooc_className(cls));

  check_metaclass_inheritance(cls);
}

/*
 * Class init
 */

static void
init_class(Class cls)
{
  Class super = (Class)ooc_classSuper(cls);

  OOC_DBG(("init_class(%s)", ooc_className(cls)));

  if (super) {

    check_inheritance(cls, super);
    setup_methods    (cls, super);
    setup_inheritance(cls, super);

  } else if (!isClassOf(cls, Object))
    ooc_abort("invalid inheritance, %s has no super class "
	      "(check SUPER_CLASS)", ooc_className(cls));
  
  setup_protocol(cls);
  setup_reflect (cls);
  setup_memsrv  (cls);
  setup_init    (cls);

  OOC_DBG(("%s.initialize()", ooc_className(cls)));
  cls->initialize();
}

/*
 * Class deinit
 */

static void
deinit_class(Class cls)
{
  OOC_DBG(("deinit_class(%s)", ooc_className(cls)));

  OOC_DBG(("%s.deinitialize()", ooc_className(cls)));
  cls->deinitialize();

  /* NOTE-TODO: better deinit
 
  if (OOC_CLASSINFO_GET(cls, OOC_CLASSINFO_STATIC_METHOD_RFT) &&
      ooc_classReflect(cls)->mth_cnt                          &&
      ooc_classReflect(cls)->mth != ooc_classReflect(super)->mth)
    ooc_free(ooc_classReflect(cls)->mth->type);
  */
}

/*
 * Class methods
 */

method0(TYPE, init)
{
  OOC_DBG((OOC_STR(CLASS)".init(%s)", ooc_className(self)));

  if (OOC_CLASSINFO_GET(self, OOC_CLASSINFO_INIT))
    ooc_abort("class %s initialized twice", ooc_className(self));
  
  OOC_CLASSINFO_SET(self, OOC_CLASSINFO_INIT);

  init_class(self);

  return self;
}

method0(void, deinit)
{
  OOC_DBG((OOC_STR(CLASS)".deinit(%s)", ooc_className(self)));
  
  if (!OOC_CLASSINFO_GET(self, OOC_CLASSINFO_INIT))
    ooc_abort("class %s deinitialized twice", ooc_className(self));
  
  OOC_CLASSINFO_CLR(self, OOC_CLASSINFO_INIT);

  deinit_class(self);
}

staticMethod0(void, initialize)
{
  override( init   );
  override( deinit );

  extendImplementation(rft);
  extendImplementation(dl );
}

#include End

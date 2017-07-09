#ifndef OOC_OOC_OOC_H
#error "libooc: use ooc/ooc/ooc.h instead of ooc/ooc/types.h directly"
#endif 

/*
 ******************************
 * OOC types
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: types.h,v 1.18 2006/11/27 16:59:38 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

/*
 * Class types definitions
 */

#define OOC_CLASSDECL(T)					\
typedef       struct               T *               T ;	\
typedef const struct               T * OOC_CAT(const,T);	\
typedef const struct OOC_CAT(class,T)* OOC_CAT(class,T)

/*
 * Forward class declaration
 */

    OOC_CLASSDECL(Object);
#define CLASSDECL_Object    OOC_DONE

    OOC_CLASSDECL(Class);
#define CLASSDECL_Class     OOC_DONE

    OOC_CLASSDECL(MetaClass);
#define CLASSDECL_MetaClass OOC_DONE

    OOC_CLASSDECL(Protocol);
#define CLASSDECL_Protocol  OOC_DONE

    OOC_CLASSDECL(Field);
#define CLASSDECL_Field     OOC_DONE

    OOC_CLASSDECL(Method);
#define CLASSDECL_Method    OOC_DONE

    OOC_CLASSDECL(Closure);
#define CLASSDECL_Closure   OOC_DONE

/*
 * Function holder (function pointer)
 */

typedef void (*ooc_function)(void);

/*
 * Closure holder (function pointer)
 */

typedef Object (*ooc_closure)(constClosure self, Object arg[]);

/*
 * Allocator services
 */

struct ooc_memsrv {
  Object (*alloc  )(classObject cls);
  void   (*dealloc)(     Object obj);
  void   (*detach )(     Object obj);
};

/*
 * Exception
 */

struct ooc_exception {
  Object      obj;
  const char *file;
  int         line;
  bool        uncaught;
};

/*
 * Reflection
 */

struct ooc_reflect {
  struct ooc_meta_mth* mth;   /* ADT */
  struct ooc_meta_fld* fld;   /* ADT */
  unsigned short*      fld_lut;
  unsigned short       mth_cnt;
  unsigned short       fld_cnt;
};

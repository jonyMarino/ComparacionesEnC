#ifndef OOC_OOC_OPERATORS_H
#define OOC_OOC_OPERATORS_H

#ifndef OOC_OBJECT_H
#error "libooc: use ooc/Object.h instead of ooc/ooc/operators.h directly"
#endif 

/*
 *******************************
 * Operators interface
 * -----
 * Object Oriented C progamming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: operators.h,v 1.22 2006/11/27 16:59:38 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

/*
 * -------------------------
 *  Operators interface
 * -------------------------
 */

/*
 * New & Al
 *
 * NOTE-USER: new, clone and exceptions
   - new and newAs throw
     o ExBadAlloc upon allocation failure                    (alloc)
     o ExBadArgument if the class is abstact                 (alloc)
   - clone throws
     o ExBadAlloc upon allocation failure                    (alloc)
     o ExBadCast if the Copiable protocol is not implemented (pcall)
 */

#if OOC_GNU_C /* GCC */

#define ooc_new(args...)					\
  OOC_VA_HAS2P(OOC_VA_HAS3P(ooc_newn, ooc_new0, args)(args),	\
	       ooc_new0(args, init), args)

#define ooc_newAs(args...)					\
  OOC_VA_HAS2P(OOC_VA_HAS3P(ooc_newAsn, ooc_newAs0, args)(args),\
	       ooc_newAs0(args, init), args)

#define ooc_newn(cname, args...)				\
  ((cname)(ooc_classInitialize(cname),				\
	   ooc_newAsn(ooc_classDesc(cname), ctor, args)))

#define ooc_newAsn(cls, ctor, args...)		\
  (((cls)->ctor)(ooc_newAs_alloc_(cls), args))

#elif OOC_VA_MACROS /* C99 */

#define ooc_new(...)							  \
  OOC_VA_HAS2P(OOC_VA_HAS3P(ooc_newn, ooc_new0, __VA_ARGS__)(__VA_ARGS__),\
	       ooc_new0(__VA_ARGS__, init), __VA_ARGS__)

#define ooc_newAs(...)							      \
  OOC_VA_HAS2P(OOC_VA_HAS3P(ooc_newAsn, ooc_newAs0, __VA_ARGS__)(__VA_ARGS__),\
	       ooc_newAs0(__VA_ARGS__, init), __VA_ARGS__)

#define ooc_newn(cname, ...)					\
  ((cname)(ooc_classInitialize(cname),				\
	   ooc_newAsn(ooc_classDesc(cname), ctor, __VA_ARGS__)))

#define ooc_newAsn(cls, ctor, ...)			\
  (((cls)->ctor)(ooc_newAs_alloc_(cls), __VA_ARGS__))

#else /* C89 */

#define ooc_new(cname) ooc_new0(cname, init)
#define ooc_newn       (this should trig a compilation error)

#define ooc_newAs(cls) ooc_newAs0(cls, init)
#define ooc_newAsn     (this should trig a compilation error)

#endif

#define ooc_new0(cname, ctor                    )\
  ((cname)(ooc_classInitialize(cname), \
	   ooc_newAs0(ooc_classDesc(cname), ctor)))
#define ooc_new1(cname, ctor                    , a1)\
  ((cname)(ooc_classInitialize(cname), \
	   ooc_newAs1(ooc_classDesc(cname), ctor, a1)))
#define ooc_new2(cname, ctor                    , a1,a2)\
  ((cname)(ooc_classInitialize(cname), \
	   ooc_newAs2(ooc_classDesc(cname), ctor, a1,a2)))
#define ooc_new3(cname, ctor                    , a1,a2,a3)\
  ((cname)(ooc_classInitialize(cname), \
	   ooc_newAs3(ooc_classDesc(cname), ctor, a1,a2,a3)))
#define ooc_new4(cname, ctor                    , a1,a2,a3,a4)\
  ((cname)(ooc_classInitialize(cname), \
	   ooc_newAs4(ooc_classDesc(cname), ctor, a1,a2,a3,a4)))
#define ooc_new5(cname, ctor                    , a1,a2,a3,a4,a5)\
  ((cname)(ooc_classInitialize(cname), \
	   ooc_newAs5(ooc_classDesc(cname), ctor, a1,a2,a3,a4,a5)))
#define ooc_new6(cname, ctor                    , a1,a2,a3,a4,a5,a6)\
  ((cname)(ooc_classInitialize(cname), \
	   ooc_newAs6(ooc_classDesc(cname), ctor, a1,a2,a3,a4,a5,a6)))
#define ooc_new7(cname, ctor                    , a1,a2,a3,a4,a5,a6,a7)\
  ((cname)(ooc_classInitialize(cname), \
	   ooc_newAs7(ooc_classDesc(cname), ctor, a1,a2,a3,a4,a5,a6,a7)))
#define ooc_new8(cname, ctor                    , a1,a2,a3,a4,a5,a6,a7,a8)\
  ((cname)(ooc_classInitialize(cname), \
           ooc_newAs8(ooc_classDesc(cname), ctor, a1,a2,a3,a4,a5,a6,a7,a8)))
#define ooc_new9(cname, ctor                    , a1,a2,a3,a4,a5,a6,a7,a8,a9)\
  ((cname)(ooc_classInitialize(cname), \
           ooc_newAs9(ooc_classDesc(cname), ctor, a1,a2,a3,a4,a5,a6,a7,a8,a9)))

#define ooc_newAs0(cls, ctor           )\
  (((cls)->ctor)(ooc_newAs_alloc_(cls) ))
#define ooc_newAs1(cls, ctor          , a1)\
  (((cls)->ctor)(ooc_newAs_alloc_(cls), a1))
#define ooc_newAs2(cls, ctor   	      , a1,a2)\
  (((cls)->ctor)(ooc_newAs_alloc_(cls), a1,a2))
#define ooc_newAs3(cls, ctor   	      , a1,a2,a3)\
  (((cls)->ctor)(ooc_newAs_alloc_(cls), a1,a2,a3))
#define ooc_newAs4(cls, ctor   	      , a1,a2,a3,a4)\
  (((cls)->ctor)(ooc_newAs_alloc_(cls), a1,a2,a3,a4))
#define ooc_newAs5(cls, ctor   	      , a1,a2,a3,a4,a5)\
  (((cls)->ctor)(ooc_newAs_alloc_(cls), a1,a2,a3,a4,a5))
#define ooc_newAs6(cls, ctor   	      , a1,a2,a3,a4,a5,a6)\
  (((cls)->ctor)(ooc_newAs_alloc_(cls), a1,a2,a3,a4,a5,a6))
#define ooc_newAs7(cls, ctor   	      , a1,a2,a3,a4,a5,a6,a7)\
  (((cls)->ctor)(ooc_newAs_alloc_(cls), a1,a2,a3,a4,a5,a6,a7))
#define ooc_newAs8(cls, ctor   	      , a1,a2,a3,a4,a5,a6,a7,a8)\
  (((cls)->ctor)(ooc_newAs_alloc_(cls), a1,a2,a3,a4,a5,a6,a7,a8))
#define ooc_newAs9(cls, ctor   	      , a1,a2,a3,a4,a5,a6,a7,a8,a9)\
  (((cls)->ctor)(ooc_newAs_alloc_(cls), a1,a2,a3,a4,a5,a6,a7,a8,a9))

#define ooc_newAs_alloc_(cls) \
       ((void*)(ooc_classMemSrv(cls)->alloc)((void*)&(cls)->_isa))

#define ooc_clone(obj) /* null-safe */ \
        ooc_cloneLoc(obj, __FILE__, __LINE__)

#define ooc_cloneLoc(obj, file, line) /* null-safe */ \
        ooc_cloneLoc((void*)&(obj)->_isa, file, line)

#define ooc_retain(obj) /* null-safe */ \
        ooc_retain((void*)&(obj)->_isa)

#define ooc_delete(obj) /* null-safe */ \
       (ooc_delete((void*)&(obj)->_isa), (obj) = 0)

#define ooc_release(obj) /* null-safe */ \
       (ooc_release((void*)&(obj)->_isa), (obj) = 0)

#define ooc_autorelease(obj) /* null-safe */ \
       (ooc_autorelease((void*)&(obj)->_isa), (obj) = 0)

/* NOTE-USER: drop must be used immediately after new */
#define ooc_drop(obj)  /* not null-safe! */ \
        ooc_drop((void*)&(obj)->_isa)

/* NOTE-USER: own must be used immediately after new */
#define ooc_own(obj) /* not null-safe! */ \
        ooc_own((void*)&(obj)->_isa)

#define ooc_refcnt(obj) /* null-safe */ \
        ooc_refcnt((void*)&(obj)->_isa)

/*
 * Cast
 */
#define ooc_castTo(obj, cname) \
((cname)ooc_castAs(obj, ooc_classDesc(cname)))

#define ooc_castAs(obj, cls) \
        ooc_castAs((void*)&(obj)->_isa, \
		   (void*)&(cls)->_isa)

#define ooc_ecastTo(obj, cname) \
((cname)ooc_ecastAs(obj, ooc_classDesc(cname)))

#define ooc_ecastAs(obj, cls) \
        ooc_ecastAsLoc(obj, cls, __FILE__, __LINE__)

#define ooc_ecastToLoc(obj, cname, file, line) \
((cname)ooc_ecastAsLoc(obj, ooc_classDesc(cname), file, line))

#define ooc_ecastAsLoc(obj, cls, file, line)	  \
        ooc_ecastAsLoc((void*)&(obj)->_isa,       \
		       (void*)&(cls)->_isa, file, line)

#define ooc_castToProto(obj, pname) \
((pname)ooc_castAsProto(obj, ooc_classDesc(pname)))

#define ooc_castAsProto(obj, pcls)		\
        ooc_castAsProto((void*)&( obj)->_isa,	\
			(void*)&(pcls)->_isa)

#define ooc_ecastToProto(obj, pname) \
((pname)ooc_ecastAsProto(obj, ooc_classDesc(pname)))

#define ooc_ecastAsProto(obj, pcls) \
        ooc_ecastAsProtoLoc(obj, pcls, __FILE__, __LINE__)

#define ooc_ecastToProtoLoc(obj, pname, file, line) \
((pname)ooc_ecastAsProtoLoc(obj, ooc_classDesc(pname), file, line))

#define ooc_ecastAsProtoLoc(obj, pcls, file, line)	\
        ooc_ecastAsProtoLoc((void*)&( obj)->_isa,	\
			    (void*)&(pcls)->_isa, file, line)

/*
 * Object (address) comparison
 */
#define ooc_isSame(obj1, obj2) \
        ((void*)&(obj1)->_isa == (void*)&(obj2)->_isa)

/*
 * Object identifier
 */
#define ooc_isA(obj, cname) \
        ooc_isInstanceOf(obj, ooc_classDesc(cname))

#define ooc_isInstanceOf(obj, cls) \
        ooc_isSame((obj)->_isa, (cls))

#define ooc_isKindOf(obj, cname) \
        ooc_isKindOfInstanceOf(obj, ooc_classDesc(cname))

#define ooc_isKindOfInstanceOf(obj, cls) \
        ooc_isSubclassOfClass((obj)->_isa, (cls))

/*
 * Class identifier
 */
#define ooc_isClassOf(cls, cname) \
        ooc_isSame(cls, ooc_classDesc(cname))

#define ooc_isSubclassOf(cls, cname) \
        ooc_isSubclassOfClass(cls, ooc_classDesc(cname))

#define ooc_isSubclassOfClass(cls, spr)	\
        ooc_isSubclassOfClass((void*)&(cls)->_isa, \
			      (void*)&(spr)->_isa)

/*
 * Critical region
 */
#if OOC_THREAD_USE

#define ooc_criticalRegion			\
  do {						\
     ooc_contextSwitchToGlobal();		\
     ooc_try {

#define ooc_endCriticalRegion			\
     } ooc_catch(Object, ex) {			\
	ooc_contextSwitchToLocal(&ex);		\
	ooc_rethrow(ex);			\
     } ooc_endTry;				\
     ooc_contextSwitchToLocal(0);		\
  } while(0)

#else

#define ooc_criticalRegion    do {
#define ooc_endCriticalRegion } while(0)

#endif

/*
 * -------------------------
 *  Prefix handler
 * -------------------------
 */

#ifdef USING_OOC

#if OOC_GNU_C /* GCC */

#define new(args...)                  ooc_new(args)
#define newn(args...)                 ooc_newn(args)
#define newAs(args...)                ooc_newAs(args)
#define newAsn(args...)               ooc_newAsn(args)

#elif OOC_VA_MACROS /* C99 */

#define new(...)                      ooc_new(__VA_ARGS__)
#define newn(...)                     ooc_newn(__VA_ARGS__)
#define newAs(...)                    ooc_newAs(__VA_ARGS__)
#define newAsn(...)                   ooc_newAsn(__VA_ARGS__)

#else /* C89 */

#define new(a)                        ooc_new(a)
#define newAs(a)                      ooc_newAs(a)

#endif

#define new0(C,I)                     ooc_new0(C,I)
#define new1(C,I,a)                   ooc_new1(C,I,a)
#define new2(C,I,a,b)                 ooc_new2(C,I,a,b)
#define new3(C,I,a,b,c)               ooc_new3(C,I,a,b,c)
#define new4(C,I,a,b,c,d)             ooc_new4(C,I,a,b,c,d)
#define new5(C,I,a,b,c,d,e)           ooc_new5(C,I,a,b,c,d,e)
#define new6(C,I,a,b,c,d,e,f)         ooc_new6(C,I,a,b,c,d,e,f)
#define new7(C,I,a,b,c,d,e,f,g)       ooc_new7(C,I,a,b,c,d,e,f,g)
#define new8(C,I,a,b,c,d,e,f,g,h)     ooc_new8(C,I,a,b,c,d,e,f,g,h)
#define new9(C,I,a,b,c,d,e,f,g,h,i)   ooc_new9(C,I,a,b,c,d,e,f,g,h,i)

#define newAs0(C,I)                   ooc_newAs0(C,I)
#define newAs1(C,I,a)                 ooc_newAs1(C,I,a)
#define newAs2(C,I,a,b)               ooc_newAs2(C,I,a,b)
#define newAs3(C,I,a,b,c)             ooc_newAs3(C,I,a,b,c)
#define newAs4(C,I,a,b,c,d)           ooc_newAs4(C,I,a,b,c,d)
#define newAs5(C,I,a,b,c,d,e)         ooc_newAs5(C,I,a,b,c,d,e)
#define newAs6(C,I,a,b,c,d,e,f)       ooc_newAs6(C,I,a,b,c,d,e,f)
#define newAs7(C,I,a,b,c,d,e,f,g)     ooc_newAs7(C,I,a,b,c,d,e,f,g)
#define newAs8(C,I,a,b,c,d,e,f,g,h)   ooc_newAs8(C,I,a,b,c,d,e,f,g,h)
#define newAs9(C,I,a,b,c,d,e,f,g,h,i) ooc_newAs9(C,I,a,b,c,d,e,f,g,h,i)

#define clone(a)                      ooc_clone(a)
#define cloneLoc(a,b,c)               ooc_cloneLoc(a,b,c)
#define retain(a)                     ooc_retain(a)
#define release(a)                    ooc_release(a)
#define autorelease(a)                ooc_autorelease(a)
#define drop(a)                       ooc_drop(a)
#define own(a)                        ooc_own(a)
#define delete(a)                     ooc_delete(a)
#define refcnt(a)                     ooc_refcnt(a)

#define castTo(a,b)                   ooc_castTo(a,b)
#define castAs(a,b)                   ooc_castAs(a,b)
#define ecastTo(a,b)                  ooc_ecastTo(a,b)
#define ecastAs(a,b)                  ooc_ecastAs(a,b)
#define ecastToLoc(a,b,c,d)           ooc_ecastToLoc(a,b,c,d)
#define ecastAsLoc(a,b,c,d)           ooc_ecastAsLoc(a,b,c,d)

#define castToProto(a,b)              ooc_castToProto(a,b)
#define castAsProto(a,b)              ooc_castAsProto(a,b)
#define ecastToProto(a,b)             ooc_ecastToProto(a,b)
#define ecastAsProto(a,b)             ooc_ecastAsProto(a,b)
#define ecastToProtoLoc(a,b,c,d)      ooc_ecastToProtoLoc(a,b,c,d)
#define ecastAsProtoLoc(a,b,c,d)      ooc_ecastAsProtoLoc(a,b,c,d)

#define isSame(a,b)                   ooc_isSame(a,b)

#define isA(a,b)                      ooc_isA(a,b)
#define isInstanceOf(a,b)             ooc_isInstanceOf(a,b)
#define isKindOf(a,b)                 ooc_isKindOf(a,b)
#define isKindOfInstanceOf(a,b)       ooc_isKindOfInstanceOf(a,b)

#define isClassOf(a,b)                ooc_isClassOf(a,b)
#define isSubclassOf(a,b)             ooc_isSubclassOf(a,b)
#define isSubclassOfClass(a,b)        ooc_isSubclassOfClass(a,b)

#define criticalRegion                ooc_criticalRegion
#define endCriticalRegion             ooc_endCriticalRegion

#endif

/*
 * -------------------------
 *  End of interface
 * ------------------------------------------------------------------------
 */

/*
 * Hidden services
 */

void *(ooc_cloneLoc) (Object obj, const char *file, int line);
void   ooc_badcast_  (const char *file, int line) __attribute__ ((noreturn));

/*
 * Hidden inlined services
 */

static inline unsigned
(ooc_refcnt)(Object obj)
{
  if (obj)
    return obj->_cnt & OOC_ATTACH_MASK
      ? obj->_cnt &  OOC_REFCNT_MASK
      : obj->_cnt & ~OOC_ATTACH_MASK;

  return 0;
}

static inline void
(ooc_destroy_)(Object obj)
{
  classObject cls = obj->_isa;

  cls->deinit(obj);
  (ooc_classMemSrv(cls)->dealloc)(obj);
}

static inline void*
(ooc_retain)(Object obj)
{
  if (obj && ++OOC_CONST_CAST(unsigned, obj->_cnt) == 1)
    (ooc_classMemSrv(obj->_isa)->detach)(obj); /* drop + retain */

  return obj;
}

static inline void
(ooc_release)(Object obj)
{
  if (obj && --OOC_CONST_CAST(unsigned, obj->_cnt) == 0)
    ooc_destroy_(obj);
}

static inline void*
(ooc_drop)(Object obj)
{
  OOC_CONST_CAST(unsigned, obj->_cnt) &= OOC_REFCNT_MASK;

  return obj;
}

static inline void
(ooc_autorelease)(Object obj)
{
  if (obj && !obj->_cnt) {
    (ooc_classMemSrv(obj->_isa)->detach)(obj); /* drop + autorelease */
    ooc_destroy_(obj);
  }
}

static inline void
(ooc_delete)(Object obj)
{
  if (obj) {
    if (!(obj->_cnt & OOC_REFCNT_MASK)) /* new + delete */
      ooc_destroy_(obj);
    else                                /* new + retain + delete */
      ooc_classMemSrv(obj->_isa)->detach( (ooc_drop)(obj) );
  }
}

static inline void*
(ooc_own)(Object obj)
{
  return (ooc_retain)( (ooc_drop)(obj) );
}

static inline bool
(ooc_isSubclassOfClass)(classObject cls, classObject spr)
{
  while(cls != spr && cls != ooc_classDesc(Object))
    cls = ooc_classSuper(cls);

  return cls == spr;
}

static inline bool
(ooc_isSubprotoclassOfClass)(classProtocol cls, classProtocol spr)
{
  while(cls != spr && cls != ooc_classDesc(Protocol))
    cls = (classProtocol)ooc_classSuper(cls);

  return cls == spr;
}

static inline void*
(ooc_castAs)(Object obj, classObject cls)
{
  return ooc_isKindOfInstanceOf(obj, cls) ? obj : ooc_call1(obj, cast, cls);
}

static inline void*
(ooc_ecastAsLoc)(Object obj, classObject cls, const char *file, int line)
{
  return (obj = ooc_castAs(obj, cls)) ? obj
    : (ooc_badcast_(file, line), NULL);
}

static inline void*
(ooc_castAsProto)(Object obj, classProtocol pcls)
{
  Protocol *pptr = ooc_classProtocol(obj->_isa);
  
  if (*pptr && ooc_isSubprotoclassOfClass((*pptr)->_isa, pcls))
    return *pptr;
  
  while(*++pptr)
    if (ooc_isSubprotoclassOfClass((*pptr)->_isa, pcls))
#if OOC_THREAD_USE
      return *pptr;
#else /* iterative bubble-sort, may not converge */
    { Protocol p = *pptr;
      *pptr = *(pptr-1);
      return *(pptr-1) = p;
    }
#endif
  
  return ooc_call1(obj, pcast, pcls);
}

static inline void*
(ooc_ecastAsProtoLoc)(Object obj, classProtocol pcls,const char *file,int line)
{
  return (obj = ooc_castAsProto(obj, pcls)) ? obj
    : (ooc_badcast_(file, line), NULL);
}

#endif /* OOC_OOC_OPERATORS_H */

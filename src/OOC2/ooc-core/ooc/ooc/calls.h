#ifndef OOC_OOC_OOC_H
#error "libooc: use ooc/ooc/ooc.h instead of ooc/ooc/calls.h directly"
#endif 

/*
 ******************************
 * Method calls
 * -----
 * Object Oriented C progamming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: calls.h,v 1.4 2005/12/09 17:43:09 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

/* NOTE-USER: call and variant
 * call0 is for method call with NO arguments AFTER self
 * call1 is for method call with one arguments after self
 * call2 ...
 * calln is for method call with one to many arguments (C99 or GCC only)
 *
 * scall? is for super call
 * pcall? is for protocol call
 */

#if OOC_GNU_C /* GCC */

#define ooc_call(self, mthd, args...)	\
  ({ __typeof__(self) _tmp = (self);	\
    (_tmp->_isa->mthd) (_tmp, ## args); })

#define ooc_call0 ooc_call
#define ooc_call1 ooc_call
#define ooc_call2 ooc_call
#define ooc_call3 ooc_call
#define ooc_call4 ooc_call
#define ooc_call5 ooc_call
#define ooc_call6 ooc_call
#define ooc_call7 ooc_call
#define ooc_call8 ooc_call
#define ooc_call9 ooc_call
#define ooc_calln ooc_call

#define ooc_pcall(self, proto, mthd, args...)	\
  ({ __typeof__(self) _tmp = (self);		\
    (ooc_ecastToProto(_tmp, proto)->mthd) (_tmp, ## args); })

#define ooc_pcall0 ooc_pcall
#define ooc_pcall1 ooc_pcall
#define ooc_pcall2 ooc_pcall
#define ooc_pcall3 ooc_pcall
#define ooc_pcall4 ooc_pcall
#define ooc_pcall5 ooc_pcall
#define ooc_pcall6 ooc_pcall
#define ooc_pcall7 ooc_pcall
#define ooc_pcall8 ooc_pcall
#define ooc_pcall9 ooc_pcall
#define ooc_pcalln ooc_pcall

#define ooc_scall(mthd, args...) \
   (ooc_classDesc(SUPER_CLASS)->mthd) ((SUPER_CLASS)self, ## args)

#define ooc_scall0 ooc_scall
#define ooc_scall1 ooc_scall
#define ooc_scall2 ooc_scall
#define ooc_scall3 ooc_scall
#define ooc_scall4 ooc_scall
#define ooc_scall5 ooc_scall
#define ooc_scall6 ooc_scall
#define ooc_scall7 ooc_scall
#define ooc_scall8 ooc_scall
#define ooc_scall9 ooc_scall
#define ooc_scalln ooc_scall

#else /* NOT GCC */

#if OOC_VA_MACROS /* C99 */

#define ooc_call(self, ...) \
  OOC_CAT(ooc_call ,OOC_VA_HAS2P(n,0,__VA_ARGS__))(self, __VA_ARGS__)
#define ooc_pcall(self, proto, ...) \
  OOC_CAT(ooc_pcall,OOC_VA_HAS2P(n,0,__VA_ARGS__))(self, proto, __VA_ARGS__)
#define ooc_scall(...) \
  OOC_CAT(ooc_scall,OOC_VA_HAS2P(n,0,__VA_ARGS__))(__VA_ARGS__)

#define ooc_calln(self, mthd, ...) \
  ((self)->_isa->mthd) (*&(self), __VA_ARGS__)
#define ooc_pcalln(self, proto, mthd, ...) \
  (ooc_ecastToProto((self),proto)->mthd) (*&(self), __VA_ARGS__)
#define ooc_scalln(mthd, ...) \
   (ooc_classDesc(SUPER_CLASS)->mthd) ((SUPER_CLASS)self, __VA_ARGS__)

#else /* C89 */

#define ooc_call   (this should trig a compilation error)
#define ooc_pcall  (this should trig a compilation error)
#define ooc_scall  (this should trig a compilation error)

#define ooc_calln  (this should trig a compilation error)
#define ooc_pcalln (this should trig a compilation error)
#define ooc_scalln (this should trig a compilation error)

#endif

#define ooc_call0(self, mthd   ) \
  ((self)->_isa->mthd)(*&(self) )
#define ooc_call1(self, mthd,   a1) \
  ((self)->_isa->mthd)(*&(self), a1)
#define ooc_call2(self, mthd,   a1,a2) \
  ((self)->_isa->mthd)(*&(self), a1,a2)
#define ooc_call3(self, mthd,   a1,a2,a3) \
  ((self)->_isa->mthd)(*&(self), a1,a2,a3)
#define ooc_call4(self, mthd,   a1,a2,a3,a4) \
  ((self)->_isa->mthd)(*&(self), a1,a2,a3,a4)
#define ooc_call5(self, mthd,   a1,a2,a3,a4,a5) \
  ((self)->_isa->mthd)(*&(self), a1,a2,a3,a4,a5)
#define ooc_call6(self, mthd,   a1,a2,a3,a4,a5,a6) \
  ((self)->_isa->mthd)(*&(self), a1,a2,a3,a4,a5,a6)
#define ooc_call7(self, mthd,   a1,a2,a3,a4,a5,a6,a7) \
  ((self)->_isa->mthd)(*&(self), a1,a2,a3,a4,a5,a6,a7)
#define ooc_call8(self, mthd,   a1,a2,a3,a4,a5,a6,a7,a8) \
  ((self)->_isa->mthd)(*&(self), a1,a2,a3,a4,a5,a6,a7,a8)
#define ooc_call9(self, mthd,   a1,a2,a3,a4,a5,a6,a7,a8,a9) \
  ((self)->_isa->mthd)(*&(self), a1,a2,a3,a4,a5,a6,a7,a8,a9)

#define ooc_pcall0(self, proto, mthd               ) \
  (ooc_ecastToProto((self), proto)->mthd)(*&(self))
#define ooc_pcall1(self, proto, mthd,               a1) \
  (ooc_ecastToProto((self), proto)->mthd)(*&(self), a1)
#define ooc_pcall2(self, proto, mthd,               a1,a2) \
  (ooc_ecastToProto((self), proto)->mthd)(*&(self), a1,a2)
#define ooc_pcall3(self, proto, mthd,               a1,a2,a3) \
  (ooc_ecastToProto((self), proto)->mthd)(*&(self), a1,a2,a3)
#define ooc_pcall4(self, proto, mthd,               a1,a2,a3,a4) \
  (ooc_ecastToProto((self), proto)->mthd)(*&(self), a1,a2,a3,a4)
#define ooc_pcall5(self, proto, mthd,               a1,a2,a3,a4,a5) \
  (ooc_ecastToProto((self), proto)->mthd)(*&(self), a1,a2,a3,a4,a5)
#define ooc_pcall6(self, proto, mthd,               a1,a2,a3,a4,a5,a6) \
  (ooc_ecastToProto((self), proto)->mthd)(*&(self), a1,a2,a3,a4,a5,a6)
#define ooc_pcall7(self, proto, mthd,               a1,a2,a3,a4,a5,a6,a7) \
  (ooc_ecastToProto((self), proto)->mthd)(*&(self), a1,a2,a3,a4,a5,a6,a7)
#define ooc_pcall8(self, proto, mthd,               a1,a2,a3,a4,a5,a6,a7,a8) \
  (ooc_ecastToProto((self), proto)->mthd)(*&(self), a1,a2,a3,a4,a5,a6,a7,a8)
#define ooc_pcall9(self, proto, mthd,               a1,a2,a3,a4,a5,a6,a7,a8,a9) \
  (ooc_ecastToProto((self), proto)->mthd)(*&(self), a1,a2,a3,a4,a5,a6,a7,a8,a9)

#define ooc_scall0(mthd                               ) \
  (ooc_classDesc(SUPER_CLASS)->mthd)((SUPER_CLASS)self)
#define ooc_scall1(mthd,                                a1) \
  (ooc_classDesc(SUPER_CLASS)->mthd)((SUPER_CLASS)self, a1)
#define ooc_scall2(mthd,                                a1,a2) \
  (ooc_classDesc(SUPER_CLASS)->mthd)((SUPER_CLASS)self, a1,a2)
#define ooc_scall3(mthd,                                a1,a2,a3) \
  (ooc_classDesc(SUPER_CLASS)->mthd)((SUPER_CLASS)self, a1,a2,a3)
#define ooc_scall4(mthd,                                a1,a2,a3,a4) \
  (ooc_classDesc(SUPER_CLASS)->mthd)((SUPER_CLASS)self, a1,a2,a3,a4)
#define ooc_scall5(mthd,                                a1,a2,a3,a4,a5) \
  (ooc_classDesc(SUPER_CLASS)->mthd)((SUPER_CLASS)self, a1,a2,a3,a4,a5)
#define ooc_scall6(mthd,                                a1,a2,a3,a4,a5,a6) \
  (ooc_classDesc(SUPER_CLASS)->mthd)((SUPER_CLASS)self, a1,a2,a3,a4,a5,a6)
#define ooc_scall7(mthd,                                a1,a2,a3,a4,a5,a6,a7) \
  (ooc_classDesc(SUPER_CLASS)->mthd)((SUPER_CLASS)self, a1,a2,a3,a4,a5,a6,a7)
#define ooc_scall8(mthd,                                a1,a2,a3,a4,a5,a6,a7,a8) \
  (ooc_classDesc(SUPER_CLASS)->mthd)((SUPER_CLASS)self, a1,a2,a3,a4,a5,a6,a7,a8)
#define ooc_scall9(mthd,                                a1,a2,a3,a4,a5,a6,a7,a8,a9) \
  (ooc_classDesc(SUPER_CLASS)->mthd)((SUPER_CLASS)self, a1,a2,a3,a4,a5,a6,a7,a8,a9)

#endif /* NOT GCC */

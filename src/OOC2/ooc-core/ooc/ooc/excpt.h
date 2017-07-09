#ifndef OOC_OOC_OOC_H
#error "libooc: use ooc/ooc/ooc.h instead of ooc/ooc/excpt.h directly"
#endif 

/*
 ******************************
 * Exception interface
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: excpt.h,v 1.6 2006/11/27 16:59:38 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

/*
 * Exceptions handling
 */

#define ooc_try							\
  do {								\
    volatile int ooc_exStatus_;					\
    struct ooc_exContext_ ooc_exLocalContext_;			\
    struct ooc_exception *ooc_ex_ =				\
                   ooc_exContextSave(&ooc_exLocalContext_);	\
    ooc_exStatus_ = ooc_exSetContext_(ooc_exLocalContext_);	\
    if (ooc_exStatus_ == ooc_exStatusTry_) {

#define ooc_catch(cname, excpt)				\
    } else if (ooc_isKindOf(ooc_ex_->obj, cname) &&	\
               (ooc_exStatus_ = ooc_exStatusCatch_)) {	\
      cname excpt = (cname)ooc_ex_->obj;

#define ooc_endTry					\
    }							\
    if (ooc_exStatus_ == ooc_exStatusTry_)		\
      ooc_exContextRestore(ooc_ex_);			\
    else if (ooc_exStatus_ == ooc_exStatusThrow_)	\
      ooc_rethrow(ooc_ex_->obj);			\
  } while(0)

#define ooc_rethrow(excpt) \
        ooc_throwLoc(excpt, ooc_ex_->file, ooc_ex_->line)

#define ooc_exFile()  (ooc_ex_->file)
#define ooc_exLine()  (ooc_ex_->line)

/*
 * Throwing exception
 */

#define ooc_throw(obj) \
        ooc_throwLoc(obj, __FILE__, __LINE__)

#define ooc_throwLoc(obj, file, line) \
        ooc_throwLoc_((void*)&(obj)->_isa, file, line)

/*
 * Pointer protection
 */

#define ooc_protectPtr(ptr, free)		 \
 struct ooc_exProtect_ OOC_CAT3(ooc_ep_,ptr,_) = \
      ooc_protectPtr_(&OOC_CAT3(ooc_ep_,ptr,_), (void*)&(ptr), free)

#define ooc_unprotectPtr(ptr) \
        ooc_unprotectPtr_((void*)&(ptr), __FILE__, __LINE__)

/*
 * Terminate handler
 */

typedef void (ooc_exTermHandler_t)(struct ooc_exception *ex);

ooc_exTermHandler_t* ooc_exSetTerminateHandler(ooc_exTermHandler_t *handler);

/*
 * -------------------------
 *  End of public interface
 * ------------------------------------------------------------------------
 */

#ifdef sigsetjmp
#define ooc_exSetContext_(context) sigsetjmp(context.buf_, 1)
#else
#define ooc_exSetContext_(context) setjmp(context.buf_)
#endif

enum { ooc_exStatusTry_, ooc_exStatusThrow_, ooc_exStatusCatch_ };

struct ooc_exContext_ {
  struct ooc_exProtect_ *ptrStack_;
  struct ooc_exContext_ *prev_;
  jmp_buf                buf_;
};

struct ooc_exProtect_ {
  struct ooc_exProtect_ *prev_;
  void *ptr_;
  void(*free_)(void*);
};

void ooc_throwLoc_       (Object ex, const char *file, int line)
                         __attribute__ ((noreturn));
struct ooc_exception*
     ooc_exContextSave   (struct ooc_exContext_ *ex_context);
void ooc_exContextRestore(struct ooc_exception  *ex);
struct ooc_exProtect_ 
     ooc_protectPtr_     (struct ooc_exProtect_ *ep_ptr,
			  void *ptr, void (*free)(void*));
void ooc_unprotectPtr_   (void *ptr, const char *file, int  line);

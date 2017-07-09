/*
 ******************************
 * Exception implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: excpt.c,v 1.7 2005/12/16 11:02:48 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/ex/ExBadException.h>
#include <ooc/ex/ExNotFound.h>
#include <ooc/ooc/lib/context.h>
#include <ooc/ooc/lib/allocator.h>
#include <stdlib.h>

/*
 * ---------------------
 *  Local implementation
 * ---------------------
 */

#ifdef sigsetjmp
#define restContext(context) siglongjmp(context->buf_, ooc_exStatusThrow_)
#else
#define restContext(context) longjmp   (context->buf_, ooc_exStatusThrow_)
#endif

static void
verbose_terminate_handler(struct ooc_exception *ex)
{
  if (ex->uncaught)
    ooc_abort("exception %s thrown (%s:%d) during stack unwinding "
	      "leading to an undefined behavior", 
	      ooc_className(ex->obj->_isa), ex->file, ex->line);
  else
    ooc_abort("exception %s thrown (%s:%d) but not caught",
	      ooc_className(ex->obj->_isa), ex->file, ex->line);
}

static ooc_exTermHandler_t *terminate = verbose_terminate_handler;

static void
do_terminate(struct ooc_context *context)
{
  OOC_DBG(("EXCPT: terminate execution"));
  
  if (terminate)
    terminate(&context->ex);

  abort(); /* safe even if user's terminate does not abort itself */
}

static void
do_stack_unwinding(struct ooc_context *context)
{
  struct ooc_exProtect_ *p = context->ex_context->ptrStack_;

  OOC_DBG(("EXCPT: stack unwinding (clear protected objects)"));

  context->ex.uncaught = true;

  while (p) {
    void **ep = (void**)p->ptr_;
    
    p->free_(*ep), *ep = 0;
    p = p->prev_;
  }

  context->ex.uncaught = false;
}

static void
do_release_shield(struct ooc_context *context)
{
  OOC_DBG(("EXCPT: release shield (clear context dependant objects)"));

  context->ex.uncaught = true;

  ooc_allocator_release(context->allocator);
  
  context->ex.uncaught = false;
}

static void
do_move_exception(struct ooc_context *context)
{
  Object ex = context->ex.obj;
  
  OOC_DBG(("EXCPT: exception moved to previous context (--ctxt)"));

  if (ex->_cnt & OOC_ATTACH_MASK)
    OOC_CONST_CAST(unsigned, ex->_cnt) -= OOC_CONTEXT_UNIT;
}

/*
 * ----------------------
 *  Global implementation
 * ----------------------
 */

/* Throw */
void
ooc_throwLoc_(Object ex, const char *file, int line)
{
  struct ooc_context       *context = ooc_contextGet();
  struct ooc_exContext_ *ex_context = context->ex_context;

  OOC_DBG(("EXCPT: exception thrown at %s:%d", file, line));

  if (context->ex.uncaught)
    do_terminate(context);

  if (!ex)
    ex = (Object)new(ExBadException);
  
  context->ex.obj  = ex;
  context->ex.file = file;
  context->ex.line = line;
  
  do_move_exception (context);
  do_stack_unwinding(context);
  do_release_shield (context);
  
  if (!ex_context->prev_)
    do_terminate(context);
  
  OOC_DBG(("EXCPT: restore exception context (longjmp)"));
  ooc_exContextRestore(&context->ex);
  restContext(ex_context);
}

/* Save/Restore */
struct ooc_exception*
ooc_exContextSave(struct ooc_exContext_ *ex_context)
{
  struct ooc_context *context = (ooc_contextInitialize(), ooc_contextGet());

  ex_context->ptrStack_ = 0;
  ex_context->prev_     = context->ex_context;

  context->ex_context     = ex_context;
  context->allocator->id += OOC_CONTEXT_UNIT;

  return &context->ex;
}

void
ooc_exContextRestore(struct ooc_exception *ex)
{
  struct ooc_context *context = (struct ooc_context*)ex;

  context->allocator->id -= OOC_CONTEXT_UNIT;

  context->ex_context = context->ex_context->prev_;
}

/* Terminate */
ooc_exTermHandler_t*
ooc_exSetTerminateHandler(ooc_exTermHandler_t *handler)
{
  ooc_exTermHandler_t *old = terminate;

  terminate = handler;

  return old;
}

/* Protect/Unprotect */
struct ooc_exProtect_
ooc_protectPtr_(struct ooc_exProtect_ *ep_ptr, void *ptr, void (*free)(void*))
{
  struct ooc_exContext_ *ex_context =
    (ooc_contextInitialize(), ooc_contextGet()->ex_context);

  ep_ptr->prev_ = ex_context->ptrStack_;
  ep_ptr->ptr_  = ptr;
  ep_ptr->free_ = free;
  ex_context->ptrStack_ = ep_ptr;

  return *ep_ptr;
}

void
ooc_unprotectPtr_(void *ptr, const char *file, int line)
{
  struct ooc_exContext_ *ex_context = ooc_contextGet()->ex_context;
  struct ooc_exProtect_ *p = ex_context->ptrStack_;

  if (p->ptr_ == ptr) {
    ex_context->ptrStack_ = p->prev_;
    return;
  }
  
  while (p->prev_ && p->prev_->ptr_ != ptr)
    p = p->prev_;
  
  if (!p->prev_)
    throwLoc(new(ExNotFound), file, line);
  
  p->prev_ = p->prev_->prev_;
}

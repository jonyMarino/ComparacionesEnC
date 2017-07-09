/*
 ******************************
 * PThread implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: pthread.c,v 1.1 2005/12/14 18:35:06 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>

#if OOC_POSIX_THREAD_USE

#include <ooc/ooc/lib/context.h>
#include <ooc/ooc/lib/allocator.h>
#include <ooc/ex/ExBadAlloc.h>

#include <ooc/utils/pthread.h>

/*
 * ---------------
 * Cleanup routine
 * ---------------
 */

static
void thread_cleanup(void *arg)
{
  struct ooc_context *context = arg;
  
  context->ex.obj = 0;
  ooc_allocator_releaseAll(context->allocator);

  OOC_DBG(("PTHREAD: cleanup"));
}

/*
 * ---------------------
 * Start routine wrapper
 * ---------------------
 */

static
void *start_wrapper(void *arg)
{
  struct ooc_context *context = arg;
  void * volatile   ret_value = 0;

  ooc_contextRegister(context);
  
  pthread_cleanup_push(thread_cleanup, context);

  try {
    ret_value = context->thread_routine(context->thread_arg);
    context->ex.obj = 0;
  } catch(Object, ex) {
    retain(ex);
  } endTry;

  ooc_allocator_releaseAll(context->allocator);

  pthread_cleanup_pop(0);
  
  return ret_value;
}

/*
 * -------------------------
 * Pthread wrapper functions
 * -------------------------
 */

int
ooc_pthread_create(pthread_t *thread, pthread_attr_t *attr, 
		   void *(*thread_routine)(void*), void *arg)
{
  struct ooc_context *child = ooc_contextNew();
  int ret;

  child->thread_routine = thread_routine;
  child->thread_arg     = arg;

  ret = pthread_create(thread, attr, start_wrapper, child);

  if (!ret) { /* thread running */
    struct ooc_context *context = ooc_contextGet();
    
    ooc_contextAddChild(context, child);
    child->thread = *thread;
  } else
    ooc_contextDel(child);
  
  return ret;
}

int
ooc_pthread_join(pthread_t thread, void **ret_value)
{
  int ret = pthread_join(thread, ret_value);

  if (!ret) { /* thread joined */
    struct ooc_context *context = ooc_contextGet();
    struct ooc_context   *child = ooc_contextGetChild(context, &thread);

    ooc_contextMerge      (context, child);
    ooc_contextRemoveChild(context, child);
    
    if (!child->ex.obj)
      ooc_contextDel(child);
    else {
      context->ex.obj  = clone(child->ex.obj);
      context->ex.file = child->ex.file;
      context->ex.line = child->ex.line;
      
      release(child->ex.obj);
      ooc_contextDel(child);
      
      ooc_throwLoc(context->ex.obj, context->ex.file, context->ex.line);
    }
  }

  return ret;
}

#endif /* OOC_POSIX_THREAD_USE */

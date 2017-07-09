/*
 ******************************
 * Context implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: context.c,v 1.16 2005/12/09 17:43:09 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/ooc/lib/context.h>
#include <ooc/ooc/lib/allocator.h>
#include <ooc/ooc/lib/pager.h>
#include <ooc/ex/ExNotFound.h>
#include <stdlib.h>

/*
 * -------------------
 * Main thread context
 * -------------------
 */

struct ooc_context ooc_contextMain[1];

/*
 * ---------------------
 *  Local implementation
 * ---------------------
 */

static struct ooc_context*
context_init(struct ooc_context *context)
{
  struct ooc_exception ex_null = { 0, 0, 0, false };

  context->ex_context_default.ptrStack_ = 0;
  context->ex_context_default.prev_     = 0;

  context->ex_context = &context->ex_context_default;
  context->ex         = ex_null;

  context->allocator     = ooc_allocator_new();
  context->allocator->id = OOC_ATTACH_MASK + OOC_CONTEXT_UNIT;

#if OOC_THREAD_USE
  context->local_allocator = context->allocator;
  context->child           = 0;
  context->next            = 0;
#endif

  return context;
}

static void
context_deinit(struct ooc_context *context)
{
  ooc_allocator_del(context->allocator);
}

/*
 * ----------------------
 *  Global implementation
 * ----------------------
 */

struct ooc_context*
ooc_contextNew(void)
{
  struct ooc_context *context = ooc_emalloc(sizeof(struct ooc_context));

  context_init(context);

#if OOC_THREAD_USE
  OOC_DBG(("THREAD: context created"));
#endif  
  
  return context;
}

void
ooc_contextDel(struct ooc_context *context)
{
  context_deinit(context);

  ooc_free(context);

#if OOC_THREAD_USE
  OOC_DBG(("THREAD: context destroyed"));
#endif
}

#if !OOC_THREAD_USE

/*
 * -------------------------
 * Single-thread environment
 * -------------------------
 */

/* Main context services */
void
ooc_contextInitialize(void)
{
  if (ooc_contextMain->ex_context)
    return;

  ooc_pager_new();

  context_init(ooc_contextMain);

  OOC_DBG(("MEM: main context created"));
}

void
ooc_contextDeinitialize(void)
{
  context_deinit(ooc_contextMain);

  OOC_DBG(("MEM: main context destroyed"));

  ooc_pager_del();
}

#else /* OOC_THREAD_USE */

/*
 * ------------------------
 * Multi-thread environment
 * ------------------------
 */

ooc_threadKey  (context_key);
ooc_threadOnce (global_allocator_once);
ooc_threadMutex(global_allocator_mutex);

static struct allocator *global_allocator = 0;

/* Main context services */
void
ooc_contextInit(void)
{
  if (ooc_contextMain->ex_context)
    return;

  ooc_pager_new();

  context_init(ooc_contextMain);

  OOC_DBG(("MEM: main context created"));

  if (ooc_threadKeyCreate(&context_key, 0))
    ooc_abort("thread unable to create context key");
    
  OOC_DBG(("THREAD: context key created"));

  ooc_contextRegister(ooc_contextMain);
}

void
ooc_contextDeinit(void)
{
  if (global_allocator)
    ooc_allocator_del(global_allocator);

  if (ooc_threadKeyDestroy(context_key))
    ooc_abort("thread unable to destroy context key");

  OOC_DBG(("THREAD: context key destroyed"));

  context_deinit(ooc_contextMain);

  OOC_DBG(("MEM: main context destroyed"));

  ooc_pager_del();
}

struct ooc_context*
ooc_contextGet(void)
{
  struct ooc_context *context = 
    (struct ooc_context*)ooc_threadKeyGetSpecific(context_key);

  if (!context) {
    OOC_DBG(("THREAD: unable to get context thread"));
    ooc_threadExit(0);
  }

  return context;
}

/* Global allocator/switch contexts management */
static
void global_allocator_init(void)
{
  global_allocator = ooc_allocator_new();
}

static struct allocator*
global_allocator_get(void)
{
  ooc_threadOnceCall(&global_allocator_once, global_allocator_init);

  return global_allocator;
}

struct allocator*
ooc_contextGetGlobalAllocator(void)
{
  return global_allocator;
}

void
ooc_contextSwitchToGlobal(void)
{
  struct ooc_context *context = ooc_contextGet();

  if (context->allocator == context->local_allocator) {
    /* thread hasn't yet a criticalRegion */
    ooc_threadMutexLock(&global_allocator_mutex);

    context->allocator = global_allocator_get();
    context->allocator->id = OOC_CONTEXT_UNIT;
  }
}

void
ooc_contextSwitchToLocal(Object *ex_)
{
  struct ooc_context *context = ooc_contextGet();

  if (context->allocator->id == OOC_CONTEXT_UNIT) {
    /* thread's top criticalRegion */
    context->allocator = context->local_allocator;
    if (ex_) {
      try {
	Object ex = clone(*ex_);
	delete(*ex_), *ex_ = ex;
      } catch(Object, ex) {
	delete(*ex_), *ex_ = ex;
      } endTry;
    }
    ooc_threadMutexUnlock(&global_allocator_mutex);
  }
}

/*
 * -------------------
 * Children management
 * -------------------
 */

struct ooc_context*
ooc_contextGetChild(struct ooc_context *context, ooc_thread(*thread))
{
  struct ooc_context *curr = context->child;

  while (curr && !ooc_threadEqual(curr->thread, *thread)) 
    curr = curr->next;

  if (!curr)
    throw(new(ExNotFound));

  return curr;
}

void
ooc_contextAddChild(struct ooc_context *context, struct ooc_context *child)
{
  child->next = context->child;
  context->child = child;
}

void
ooc_contextRemoveChild(struct ooc_context *context, struct ooc_context *child)
{
  struct ooc_context *curr = context->child;
  
  if (!curr)
    throw(new(ExNotFound));
  
  if (curr == child)
    context->child = curr->next;
  else {
    struct ooc_context *prev = curr;
    
    while (prev->next && prev->next != child)
      prev = prev->next;
    
    if (!prev->next)
      throw(new(ExNotFound));
    
    curr       = prev->next;
    prev->next = curr->next;
  }
}

void
ooc_contextRegister(struct ooc_context *context)
{
  struct ooc_context *stored_context = 
    (struct ooc_context*)ooc_threadKeyGetSpecific(context_key);

  if (stored_context)
    ooc_abort("context instance for the current thread already exists");

  if (ooc_threadKeySetSpecific(context_key, context))
    ooc_abort("thread unable to set context key");

  OOC_DBG(("THREAD: register context"));
}

void
ooc_contextMerge(struct ooc_context *context, struct ooc_context *other)
{
  ooc_allocator_merge(context->allocator, other->allocator);
}

#endif /* OOC_THREAD_USE */

#ifndef OOC_OOC_LIB_CONTEXT_H
#define OOC_OOC_LIB_CONTEXT_H

/*
 ******************************
 * Context management interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: context.h,v 1.5 2005/12/14 18:35:05 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/utils/thread.h>

/*
 * --------
 * Services
 * --------
 */

#if OOC_THREAD_USE

struct ooc_context* ooc_contextGet(void);
#else
#define             ooc_contextGet() ooc_contextMain
#endif

struct ooc_context* ooc_contextNew         (void);
void                ooc_contextDel         (struct ooc_context *context);
void                ooc_contextInitialize  (void);
void                ooc_contextDeinitialize(void);

/*
 * ---------------------------------
 * Multi-thread environment services
 * ---------------------------------
 */

#if OOC_THREAD_USE

/*
 * Share
 */

void              ooc_contextSwitchToGlobal    (void);
void              ooc_contextSwitchToLocal     (Object *ex);
struct allocator* ooc_contextGetGlobalAllocator(void);

/*
 * Children management
 */

struct ooc_context* 
     ooc_contextGetChild   (struct ooc_context *context, ooc_thread(*thread));
void ooc_contextAddChild   (struct ooc_context *context, 
			    struct ooc_context *child  );
void ooc_contextRemoveChild(struct ooc_context *context, 
			    struct ooc_context *child  );
void ooc_contextRegister   (struct ooc_context *context);
void ooc_contextMerge      (struct ooc_context *context, 
			    struct ooc_context *other  );

#endif /* OOC_THREAD_USE */


/*
 * ----------------------
 * Context Data Structure
 * ----------------------
 */

struct ooc_context {
  /* public: */
  struct ooc_exception ex; /* must be the first ! */

  /* private: */
  struct allocator      *allocator;
  struct ooc_exContext_ *ex_context;
  struct ooc_exContext_  ex_context_default;

#if OOC_THREAD_USE
  ooc_thread(thread);
  void*                (*thread_routine)(void*);
  void                  *thread_arg;
  struct allocator      *local_allocator;
  struct ooc_context    *child;
  struct ooc_context    *next;
#endif
};

extern struct ooc_context ooc_contextMain[1];

#endif /* OOC_OOC_LIB_CONTEXT_H */

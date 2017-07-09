#ifndef OOC_OOC_THREAD_H
#define OOC_OOC_THREAD_H

/*
 ******************************
 * Thread interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: thread.h,v 1.1 2005/12/14 18:35:06 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#if OOC_POSIX_THREAD_USE

#include OOC_POSIX_THREAD_HDR

/*
 * ------------------------------
 * OOC Thread to Pthread Services
 * ------------------------------
 */

#define ooc_thread(thread)                 pthread_t(thread)
#define ooc_threadSelf()                   pthread_self ()
#define ooc_threadEqual(thread1, thread2)  pthread_equal(thread1, thread2)
#define ooc_threadExit(retval)             pthread_exit (retval)

#define ooc_threadMutex(mutex) \
        static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER
#define ooc_threadMutexLock(mutex)         pthread_mutex_lock  (mutex)
#define ooc_threadMutexUnlock(mutex)       ooc_threadMutexUnlock(mutex)

#define ooc_threadOnce(once) \
        static pthread_once_t once = PTHREAD_ONCE_INIT
#define ooc_threadOnceCall(once, init_func)  pthread_once(once, init_func)

#define ooc_threadKey(key)                 static pthread_key_t key
#define ooc_threadKeyCreate(key, attr)     pthread_key_create (key, attr)
#define ooc_threadKeyDestroy(key)          pthread_key_delete (key)
#define ooc_threadKeyGetSpecific(key)      pthread_getspecific(key)
#define ooc_threadKeySetSpecific(key, val) pthread_setspecific(key,  val)

static inline void
(ooc_threadMutexUnlock)(void *mutex)
{
  int err = pthread_mutex_unlock(mutex);

  if (err)
    ooc_error("ooc_threadMutexUnlock error code %d", err);
}

#else

#define ooc_thread(thread)
#define ooc_threadSelf()
#define ooc_threadEqual(thread1, thread2)
#define ooc_threadExit(retval)

#define ooc_threadMutex(mutex)             union OOC_CAT3(mutex,__,__LINE__)
#define ooc_threadMutexLock(mutex)
#define ooc_threadMutexUnlock(mutex)

#define ooc_threadOnce(once)               union OOC_CAT3(once ,__,__LINE__)
#define ooc_threadOnceCall(once, init_func)

#define ooc_threadKey(key)                 union OOC_CAT3(key  ,__,__LINE__)
#define ooc_threadKeyCreate(key, attr)
#define ooc_threadKeyDestroy(key)
#define ooc_threadKeyGetSpecific(key)
#define ooc_threadKeySetSpecific(key, val)

#endif /* OOC_POSIX_THREAD_USE */

#endif /* OOC_OOC_THREAD_H */

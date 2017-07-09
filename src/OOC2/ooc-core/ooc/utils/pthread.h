#ifndef OOC_UTILS_PTHREAD_H
#define OOC_UTILS_PTHREAD_H

/*
 ******************************
 * PThread interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: pthread.h,v 1.1 2005/12/14 18:35:06 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#if OOC_POSIX_THREAD_USE

#include OOC_POSIX_THREAD_HDR

/*
 * OOC Pthread Overload
 */

int ooc_pthread_create(pthread_t *thread, pthread_attr_t *attr, 
		       void *(*thread_routine)(void *), void *arg);
int ooc_pthread_join  (pthread_t thread, void **ret_value);

#endif /* OOC_POSIX_THREAD_USE */

#endif /* OOC_UTILS_PTHREAD_H */

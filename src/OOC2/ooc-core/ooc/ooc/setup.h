#ifndef OOC_OOC_OOC_H
#error "libooc: use ooc/ooc/ooc.h instead of ooc/ooc/setup.h directly"
#endif 

/*
 ******************************
 * Setup configuration
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: setup.h,v 1.6 2005/11/15 18:37:11 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

/*
 * -------------------------
 *  POSIX dialect
 * -------------------------
 */

#if OOC_POSIX_SOURCE_USE > 0
#  ifndef _POSIX_SOURCE
#  define _POSIX_SOURCE 1
#  endif

#  ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 1
#  endif
#endif

/*
 * -------------------------
 *  GCC dialect
 * -------------------------
 */

#ifdef __GNUC__

#  ifndef __STRICT_ANSI__
#    define OOC_GNU_C 1
#  endif

#  if OOC_ISO_C < OOC_ISO_C99
#    define inline   __inline__
#    define restrict __restrict__
#  endif

#else

#  undef  __attribute__    /* not a macro but...    */
#  define __attribute__(a) /* disable GCC attribute */

#endif

/*
 * -------------------------
 *  Pre-C99 and C99
 * -------------------------
 */

#if OOC_ISO_C < OOC_ISO_C99 /* NOTE-INFO: Pre-C99 */

#  if  !__bool_true_false_are_defined
#define __bool_true_false_are_defined 1
#    ifndef bool
       typedef unsigned char bool;
#      define bool bool
#    endif
#    ifndef false
#    define false 0
#    endif
#    ifndef true
#    define true 1
#    endif
#  endif

#  ifndef inline   /* disable inline */
#  define inline
#  endif

#  ifndef restrict /* disable restrict */
#  define restrict
#  endif

#else /* NOTE-INFO: C99 */

#  include <stdbool.h>

#  ifndef OOC_VA_MACROS
#  define OOC_VA_MACROS 1
#  endif

#endif

/*
 * ------------------------------
 * Thread Portable Implementation
 * ------------------------------
 */

#if OOC_POSIX_THREAD_USE

#define OOC_THREAD_USE 1

#endif


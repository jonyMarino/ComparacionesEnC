#ifndef OOC_CONFIG_OOC_H
#define OOC_CONFIG_OOC_H

/*
 ******************************
 * OOC configuration
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: config_ooc.h,v 1.15 2005/12/18 19:04:40 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

/*
 * -------------------------
 * Memory Management Settings (Allocator/Pool)
 * -------------------------
 */

/* NOTE-CONF: Allocator
 * Block chunk specifies the number of page allocated in each chunk
 * Page size must be a power of two (2048, 4096, 8192, 16384)
 * Remark: objects with size > (page_size - page_header)/2 are malloc'ed
 */
#define OOC_POOL_PAGECHUNK 10
#define OOC_POOL_PAGESIZE  8192

/*
 * -------------------------
 *  Garbage collector (Boehm's GC)
 * -------------------------
 */

/* NOTE-CONF: GC
 * Set the following defines if you want to use Boehm's garbage collector.
 * Setting the garbage collector override the use of OOC allocator/pool.
 * To enable GC debug mode, compile OOC with -DGC_DEBUG
 */
#define OOC_GC_USE 0
#define OOC_GC_HDR <gc/gc.h>
#define OOC_GC_LIB_DL -lgc
#define OOC_GC_LIB_AR /us/lib/libgc.a

/*
 * -------------------------
 *  Foreign Function Interface
 * -------------------------
 */

/* NOTE-CONF: FFI
 * Set the following defines if you want to use the FFI library.
 * Used by the reflection/inspector for non-object parameters.
 */
#define OOC_FFI_USE 0
#define OOC_FFI_HDR <ffi.h>
#define OOC_FFI_LIB_DL -lffi    
#define OOC_FFI_LIB_AR /usr/lib/libffi.a

/*
 * -------------------------
 *  POSIX Dynamic Loader
 * -------------------------
 */

/* NOTE-CONF: dynamic linking loader
 * Set the following defines if you want to use POSIX dynamic loader
 */
#define OOC_POSIX_DLINK_USE 0
#define OOC_POSIX_DLINK_HDR <dlfcn.h>
#define OOC_POSIX_DLINK_LIB_DL -ldl
#define OOC_POSIX_DLINK_LIB_AR /usr/lib/libdl.a

/*
 * -------------------------
 *  POSIX Threads
 * -------------------------
 */

/* NOTE-CONF: Posix threads
 * Set the following defines if you want to use Posix threads
 * Library extension (LIB_EX) will be added to the thread version of libooc
 */
#define OOC_POSIX_THREAD_USE 0
#define OOC_POSIX_THREAD_HDR <pthread.h>
#define OOC_POSIX_THREAD_LIB_DL -lpthread
#define OOC_POSIX_THREAD_LIB_AR /usr/lib/libpthread.a
#define OOC_POSIX_THREAD_LIB_EX _pth

/*
 * -------------------------
 *  C dialect
 * -------------------------
 */

/* NOTE-CONF: variadic macros (not needed for GCC)
 * Force the use of C99 variadic macros (e.g. c99 cpp + c89 cc)
 *   Remark: alternative C99 preprocessor at http://pornin.nerim.net/ucpp/
 */
#define OOC_VA_MACROS 0

/*
 * -------------------------
 *  POSIX dialect
 * -------------------------
 */

/* NOTE-CONF: headers
 * Set the following define if you want to enhance the use of POSIX headers
 */
#define OOC_POSIX_SOURCE_USE 1

#endif /* OOC_CONFIG_OOC_H */

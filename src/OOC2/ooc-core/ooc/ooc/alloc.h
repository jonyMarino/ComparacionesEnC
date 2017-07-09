#ifndef OOC_OOC_OOC_H
#error "libooc: use ooc/ooc/ooc.h instead of ooc/ooc/alloc.h directly"
#endif 

/*
 *******************************
 * Alloc interface
 * -----
 * Object Oriented C progamming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: alloc.h,v 1.3 2005/11/16 17:59:08 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

/*
 * -------------------------
 *  Alloc interface
 * -------------------------
 */

/* NOTE-USER: allocation behavior
   - [e]malloc    allocates memory uncleared (default:  malloc)
   - [e]rawalloc  allocates memory uncleared (default:  malloc)
   - [e]realloc reallocates memory uncleared (default: realloc)
   - exception-version rely on null-version
 */

/* memory (de)allocation, return null pointer upon failure */
extern void* (*ooc_malloc  )(size_t size);
extern void* (*ooc_rawalloc)(size_t size);
extern void* (*ooc_realloc )(void *ptr, size_t size);
extern void  (*ooc_free    )(void *ptr); /* accept null pointer */

#define ooc_free(ptr) (ooc_free(ptr), (ptr) = 0)

/* memory allocation, throw ExBadAlloc upon failure */
#define ooc_emalloc(size)      ooc_emalloc  (     size, __FILE__, __LINE__)
#define ooc_erawalloc(size)    ooc_erawalloc(     size, __FILE__, __LINE__)
#define ooc_erealloc(ptr,size) ooc_erealloc (ptr, size, __FILE__, __LINE__)

void* (ooc_emalloc  )(           size_t size, const char *file, int line);
void* (ooc_erawalloc)(           size_t size, const char *file, int line);
void* (ooc_erealloc )(void *ptr, size_t size, const char *file, int line);

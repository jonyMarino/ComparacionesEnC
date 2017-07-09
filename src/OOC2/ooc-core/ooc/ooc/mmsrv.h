#ifndef OOC_OOC_OOC_H
#error "libooc: use ooc/ooc/ooc.h instead of ooc/ooc/mmsrv.h directly"
#endif 

/*
 ******************************
 * Memory management services
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: mmsrv.h,v 1.7 2005/12/15 16:58:59 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

/* Objects services */
bool   ooc_memIsObject      (Object obj);

/* Raw pointers services */
void*  ooc_memAlloc         (size_t size);
void   ooc_memFree          (void   *ptr);
bool   ooc_memIsAllocated   (void   *ptr);

/* Statistics services */
size_t ooc_memObjectCnt     (size_t    size);
size_t ooc_memClassObjectCnt(constClass cls);

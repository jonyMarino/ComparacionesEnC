#ifndef OOC_OOC_LIB_PAGER_H
#define OOC_OOC_LIB_PAGER_H

/*
 ******************************
 * Pager interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: pager.h,v 1.3 2005/11/28 17:42:03 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

struct pager *ooc_pager_new    (void);
void          ooc_pager_del    (void);
struct page  *ooc_pager_alloc  (void);
void          ooc_pager_dealloc(struct page *page);

#endif /* OOC_OOC_LIB_PAGER_H */ 

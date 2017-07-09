#ifndef OOC_OOC_LIB_BIGPAGE_H
#define OOC_OOC_LIB_BIGPAGE_H

/*
 ******************************
 * BigPage interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: bigpage.h,v 1.5 2006/11/27 16:59:38 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/Object.h>
#include <ooc/type/ctype.h>
#include <ooc/ooc/lib/page.h>

/*
 * -----------
 * Page layout
 * -----------
 */

struct bigpage_base {
  struct bigpool *pool;

  struct bigpage *next;
  struct bigpage *prev;
};        
  
struct bigpage {
  struct bigpage_base base;

  union {
    struct Object obj[1];
    union ooc_ctype _;
  } alig;
};

struct bigpage_raw {
  struct bigpage_base base;
  struct page_rawCell cell;
};

/*
 * ----------------------------------
 * Object offset in bigpage structure
 * ----------------------------------
 */

#define OOC_BIGPAGE_HEADER_SIZE     offsetof(struct bigpage    , alig.obj)
#define OOC_BIGPAGE_RAW_HEADER_SIZE offsetof(struct bigpage_raw, cell.ptr)

/*
 * -------------
 * Page services
 * -------------
 */

static inline struct bigpage*
ooc_bigpage_getPage(void *ptr)
{
  return (struct bigpage*)    ((char*)ptr - OOC_BIGPAGE_HEADER_SIZE);
}

static inline struct bigpage_raw*
ooc_bigpage_rawGetPage(void *ptr)
{
  return (struct bigpage_raw*)((char*)ptr - OOC_BIGPAGE_RAW_HEADER_SIZE);
}

static inline Object
ooc_bigpage_getObj(struct bigpage *page)
{
  return (Object)((char*)page + OOC_BIGPAGE_HEADER_SIZE);
}

static inline void*
ooc_bigpage_rawGetPtr(struct bigpage_raw *page)
{
  return (Object)((char*)page + OOC_BIGPAGE_RAW_HEADER_SIZE);
}

#endif /* OOC_OOC_LIB_BIGPAGE_H */

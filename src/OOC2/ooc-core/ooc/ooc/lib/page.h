#ifndef OOC_OOC_LIB_PAGE_H
#define OOC_OOC_LIB_PAGE_H

/*
 ******************************
 * Page interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: page.h,v 1.6 2006/11/27 16:59:38 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/Object.h>
#include <ooc/type/ctype.h>
#include <ooc/ooc/lib/allocator.h>

/*
 * --------------
 * Page structure
 * --------------
 */

struct page {
  struct block     *block; /* filled by pager */

  struct pool      *pool;
  struct page      *next;
  struct page      *prev;
  struct page      *next_free;
  struct page      *prev_free;
  struct page_cell *first_free;
  size_t            obj_cnt;
  size_t            tmp_cnt;

  union {
    struct Object obj[1];
    union ooc_ctype _;
  } alig;
};

/*
 * -------------------
 * Page cell structure
 * -------------------
 */

struct page_cell {    /* for objects */
  Class  isa;
  struct page_cell *next;
};

struct page_rawCell { /* for raw pointers */
  union {
    struct page_rawCell *next;
    void (*dealloc_srv)(void*);
  } hdr;

  union ooc_ctype ptr[1];
};

/*
 * -----
 * Dummy
 * -----
 */

extern struct page ooc_page_null[1];

/*
 * -----------
 * Page macros
 * -----------
 */

#define OOC_PAGE_HEADER_SIZE         offsetof(struct page,    alig.obj)
#define OOC_PAGE_RAWCELL_HEADER_SIZE offsetof(struct page_rawCell, ptr)

#define OOC_PAGE_EFFECTIVESIZE      (OOC_POOL_PAGESIZE - OOC_PAGE_HEADER_SIZE)
#define OOC_PAGE_MAX_CHUNKSIZE \
      ((OOC_PAGE_EFFECTIVESIZE/2) & ~OOC_ALLOCATOR_SIZE_MASK)


/* 
 * --------
 * Services
 * --------
 */

void ooc_page_init   (struct page *page, struct pool *pool);
void ooc_page_rawInit(struct page *page, struct pool *pool);


/* 
 * ---------------
 * Inline services
 * ---------------
 */

static inline void*
ooc_page_get(void *ptr)
{
#if defined(UINTPTR_MIN) || defined(UINTPTR_MAX)

  return (void*)((uintptr_t)(ptr) & (~(OOC_POOL_PAGESIZE-1)));

#else

  if (sizeof(size_t) >= sizeof(void*))
    return (void*)((size_t)(ptr) & (~(OOC_POOL_PAGESIZE-1)));

  if (sizeof(unsigned long) >= sizeof(void*))
    return (void*)((unsigned long)(ptr) & (~(OOC_POOL_PAGESIZE-1)));

  /* NOTE-PORT: pointer to integer conversion */
  ooc_abort("Non-portable pointer to integer conversion");

  return 0;

#endif
}

static inline void*
ooc_page_firstObject(struct page *page)
{
  return (char*)page + OOC_PAGE_HEADER_SIZE;
}

static inline size_t
ooc_page_objectCnt(size_t obj_size)
{
  return OOC_PAGE_EFFECTIVESIZE/obj_size;
}

static inline bool
ooc_page_isAligned(void *ptr, struct page *page, size_t obj_size)
{
  char *first = ooc_page_firstObject(page);

  return ((char*)ptr - first) % obj_size == 0;
}

static inline bool
ooc_page_fitSize(size_t size)
{
  return size <= OOC_PAGE_MAX_CHUNKSIZE;
}

static inline bool
ooc_page_rawFitSize(size_t size)
{
  return size <= OOC_PAGE_MAX_CHUNKSIZE - OOC_PAGE_RAWCELL_HEADER_SIZE;
}

static inline void*
ooc_page_rawGetPtr(struct page_rawCell *cell)
{
  return (char*)cell + OOC_PAGE_RAWCELL_HEADER_SIZE;
}

static inline struct page_rawCell*
ooc_page_rawGetCell(void *ptr)
{
  return (struct page_rawCell*)((char*)ptr - OOC_PAGE_RAWCELL_HEADER_SIZE);
}

#endif /* OOC_OOC_LIB_PAGE_H */ 

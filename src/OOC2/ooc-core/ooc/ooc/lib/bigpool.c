/*
 ******************************
 * Big Pool implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: bigpool.c,v 1.19 2005/12/12 10:03:10 oachim Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/ooc/lib/context.h>
#include <ooc/ooc/lib/allocator.h>
#include <ooc/ooc/lib/bigpage.h>

#include <ooc/ooc/lib/bigpool.h>

/*
 * ------
 * Dummys
 * ------
 */

struct bigpool ooc_bigpool_null[1] = {{ 0, ooc_bigpool_null }};

/*
 * ------------
 * Pool helpers
 * ------------
 */

static inline void
bigpage_insert(struct bigpage *page, struct bigpool *pool)
{
  page->base.pool  = pool;

  page->base.next = pool->first_page;
  page->base.prev = 0;
  if (pool->first_page)
    pool->first_page->base.prev = page;

  pool->first_page = page;
}

static inline void
bigpage_remove(struct bigpage *page)
{
  struct bigpool *pool = page->base.pool;

  if (!page->base.prev)
    pool->first_page = page->base.next;
  else
    page->base.prev->base.next = page->base.next;

  if (page->base.next)
    page->base.next->base.prev = page->base.prev;
}

static inline void
bigpool_del(struct bigpool *pool)
{
  if (pool != ooc_bigpool_null) {
    struct bigpage *curr = pool->first_page;
    size_t obj_cnt = 0;

    while (curr) {
      struct bigpage *next = curr->base.next;
      
      ++obj_cnt;
      ooc_free(curr);

      curr = next;
    }

    ooc_free(pool);
    
    if (obj_cnt)
      ooc_warning("bigpool destroyed with %d objects", obj_cnt);
    else
      OOC_DBG(("bigpool destroyed with 0 objects"));
  }
}

/*
 * -------------------
 * Pool implementation
 * -------------------
 */

struct bigpool*
ooc_bigpool_new(void)
{
  struct bigpool *bigpool = ooc_emalloc(sizeof(struct bigpool));

  bigpool->first_page = 0;
  bigpool->raw        = ooc_bigpool_null;

  return bigpool;
}

void
ooc_bigpool_del(struct bigpool *pool)
{
  bigpool_del(pool->raw);
  bigpool_del(pool);
}

void
ooc_bigpool_release(struct bigpool *pool, unsigned id)
{
  struct bigpage *curr = pool->first_page;

  while (curr) {
    Object obj = ooc_bigpage_getObj(curr);
    struct bigpage *next = curr->base.next;
    
    if ((obj->_cnt & ~OOC_REFCNT_MASK) == id) /* current context */
      (ooc_delete)(obj);
    else
      (ooc_autorelease)(obj);                 /* new+drop+throw  */

    curr = next;
  }
}

void
ooc_bigpool_releaseAll(struct bigpool *pool)
{
  struct bigpage *curr = pool->first_page;
  
  while (curr) {
    Object obj = ooc_bigpage_getObj(curr);
    struct bigpage *next = curr->base.next;
    
    if (obj->_cnt & OOC_ATTACH_MASK) /* current context */
      (ooc_delete)(obj);
    else
      (ooc_autorelease)(obj);        /* new+drop+throw  */

    curr = next;
  }
}

bool
ooc_bigpool_isObject(struct bigpool *pool, Object obj)
{
  struct bigpage *curr = pool->first_page;
  struct bigpage *page = ooc_bigpage_getPage(obj);

  while (curr) {
    if (curr == page)
      break;

    curr = curr->base.next;
  }

  return curr != 0;
}

/* 
 * ---------------------------
 * Raw pointers implementation
 * ---------------------------
 */

/*
 * ------------
 * Pool helpers
 * ------------
 */

static inline struct bigpool*
bigpool_rawAlloc(struct bigpool *pool, size_t size)
{
  struct bigpage_raw *page;

  if (pool == ooc_bigpool_null)
    pool = ooc_bigpool_new();

  if (pool->raw == ooc_bigpool_null)
    pool->raw = ooc_bigpool_new();

  page = ooc_emalloc(OOC_BIGPAGE_RAW_HEADER_SIZE + size);
  page->cell.hdr.dealloc_srv = ooc_bigpool_rawDealloc;

  bigpage_insert((struct bigpage*)page, pool->raw);
  
  return pool;
}

static inline void
bigpool_rawDealloc(struct bigpage_raw *page)
{
  bigpage_remove((struct bigpage*)page);

  ooc_free(page);
}

/*
 * -------------------
 * Pool implementation
 * -------------------
 */

void*
ooc_bigpool_rawAlloc(size_t size)
{
  struct allocator *alloc = ooc_contextGet()->allocator;

  alloc->bigpool = bigpool_rawAlloc(alloc->bigpool, size);
  
  return ooc_bigpage_rawGetPtr
    ((struct bigpage_raw*)alloc->bigpool->raw->first_page);
}

void
ooc_bigpool_rawDealloc(void *ptr)
{
  struct bigpage_raw *page = ooc_bigpage_rawGetPage(ptr);

  bigpool_rawDealloc(page);
}

bool
ooc_bigpool_rawIsAllocated(struct bigpool *pool_obj, void *ptr)
{
  struct bigpool     *pool = pool_obj->raw;
  struct bigpage_raw *page = ooc_bigpage_rawGetPage(ptr);
  struct bigpage_raw *curr = (struct bigpage_raw*)pool->first_page;

  while (curr) {
    if (curr == page)
      break;
    
    curr = (struct bigpage_raw*)curr->base.next;
  }
    
  return curr != 0;
}

/* 
 * ----------
 * Statistics
 * ----------
 */

size_t
ooc_bigpool_objectCnt(struct bigpool *pool, size_t size)
{
  struct bigpage *curr = pool->first_page;
  size_t       obj_cnt = 0;

  while (curr) {
    Object obj = ooc_bigpage_getObj(curr);

    if (ooc_classInstanceSize(obj->_isa) == size)
      ++obj_cnt;

    curr = curr->base.next;
  }
  
  return obj_cnt;
}

size_t
ooc_bigpool_classObjectCnt(struct bigpool *pool, constClass cls)
{
  struct bigpage *curr = pool->first_page;
  size_t       obj_cnt = 0;

  while (curr) {
    Object obj = ooc_bigpage_getObj(curr);

    if ((Class)obj->_isa == cls)
      ++obj_cnt;

    curr = curr->base.next;
  }
  
  return obj_cnt;
}
/* 
 * -----------------------------------
 * Objects sub-services implementation
 * -----------------------------------
 */

struct bigpool*
ooc_bigpool_alloc(struct bigpool *pool, size_t size)
{
  struct bigpage *page;

  if (pool == ooc_bigpool_null)
    pool = ooc_bigpool_new();

  page = ooc_emalloc(OOC_BIGPAGE_HEADER_SIZE + size);

  bigpage_insert(page, pool);
  
  return pool;
}

void
ooc_bigpool_dealloc(struct bigpage *page)
{
  bigpage_remove(page);

  ooc_free(page);
}

/*
 * ---------------------
 * Multi-thread services
 * ---------------------
 */

#if OOC_THREAD_USE

static inline void
bigpool_merge(struct bigpool *pool, struct bigpool *other)
{
  if (!other->first_page)
    return;

  if (!pool->first_page)
    pool->first_page = other->first_page;
  else {
    struct bigpage *curr = pool->first_page;

    while (curr->base.next)
      curr = curr->base.next;
    
    curr->base.next = other->first_page;
    other->first_page->base.prev = curr;
  }

  other->first_page = 0;
}

struct bigpool*
ooc_bigpool_merge(struct bigpool *pool, struct bigpool *other)
{
  if (other != ooc_bigpool_null) {
    if (pool == ooc_bigpool_null)
      pool = ooc_bigpool_new();
    
    bigpool_merge(pool     , other     );
    bigpool_merge(pool->raw, other->raw);
  }
  
  return pool;
}

#endif /* OOC_THREAD_USE */

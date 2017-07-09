/*
 ******************************
 * Map implementation
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: map.c,v 1.2 2005/09/28 08:03:59 oachim Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/assert.h>
#include <ooc/utils/size.h>
#include <ooc/ex/ExBadSize.h>
#include <ooc/ex/ExBadAlloc.h>
#include <ooc/ex/ExBadPosition.h>
#include <ooc/ex/ExOverflow.h>
#include <string.h>

#define OOC_TYPE_MAP_C
#define map_H
#define map_T

#include <ooc/type/map_t.h>

typedef struct {
  ooc_function hash;
  ooc_function equal;

  size_t   *slot;
  size_t    slot_msk;
  size_t    slot_curr;
  size_t    slot_grow;
  char     *pool;
  size_t    pool_cnt;
  size_t    pool_curr;
  size_t    pool_free;
  size_t    pool_csize;
  unsigned  max_load;
} *T;

struct C {
  size_t next;
  size_t hkey;
};

#define POOL(cnt) \
        ((struct C*)(map->pool + (cnt)*map->pool_csize))

/*
 * -------------------------------
 *  Map implementation
 * -------------------------------
 */

static inline size_t
chk_size(size_t ecnt, size_t esize)
{
  size_t size = ecnt * esize;

  if (size < ecnt || size < esize)
    throw(new(ExOverflow));

  return size;
}

static inline void
enlarge_pool(T map)
{
  char  *pool  = map->pool + map->pool_csize;
  char  *pool2 = 0;
  size_t cnt   = map->pool_cnt;
  size_t cnt2  = 2*cnt;
  size_t i;
  
  while (cnt2 > cnt) {
    size_t size = cnt2 * map->pool_csize;

    OOC_DBG(("map pool expansion %lu (%u%%) -> %lu (%u%%)",
	     (unsigned long)cnt ,(unsigned)(100.0*cnt /(map->slot_msk+1)),
	     (unsigned long)cnt2,(unsigned)(100.0*cnt2/(map->slot_msk+1))));
    if (size > cnt2 && size > map->pool_csize) {
      pool2 = ooc_realloc(pool, size);
      if (pool2) break;
    }

    cnt2 -= cnt/10;
  }

  if (!pool2)
    throw(new(ExBadAlloc));
  
  map->pool = pool2 - map->pool_csize;
  map->pool_free = cnt+1;
  
  for (i = map->pool_free; i < cnt2; i++)
    POOL(i)->next = i+1;
  POOL(i)->next = 0;
}

static inline void
enlarge_slot(T map)
{
  size_t *slot = 0;
  size_t  cnt  = map->slot_msk + 1;
  size_t  cnt2 = ooc_size_nextPow2((100.0 * cnt) / map->max_load);
  size_t  size = cnt2 * sizeof *map->slot;
  size_t  idx  = 0;
  size_t  i;

  OOC_DBG(("map slot expansion %lu (%u%%) -> %lu (%u%%)",
	   (unsigned long)cnt , (unsigned)(100.0*map->pool_cnt/cnt ),
	   (unsigned long)cnt2, (unsigned)(100.0*map->pool_cnt/cnt2)));

  if (size > cnt2 && size > sizeof *map->slot) {
    slot = ooc_realloc(map->slot, size);
    map->slot_grow = cnt2 * (map->max_load/100.0);
  }

  if (!slot) {
    OOC_DBG(("map slot expansion canceled (memory allocation failed"));
    return;
  }
  
  map->slot     = slot;
  map->slot_msk = cnt2-1;

  for (i = 0; i < cnt; i++) {

    if (map->slot[i]) {
      struct C *cell = POOL(map->slot[i]);
      
      while(cell->next)
	cell = POOL(cell->next);
      
      cell->next = idx;
      idx = map->slot[i];
    }

    map->slot[i] = 0;
  }

  while(idx) {
    struct C *cell = POOL(idx);
    size_t *slot = map->slot + (cell->hkey & map->slot_msk);
    size_t next = cell->next;

    cell->next = *slot;
    *slot = idx;
    idx = next;
  }
}

/*
 * Global functions
 */

void*
ooc_map_new_(unsigned     max_load, /* in % */
	     size_t       cnt_hint,
	     size_t       csize,
	     ooc_function hash,
	     ooc_function equal)
{
  T map = 0; protectPtr(map, ooc_map_del_);
  size_t i;

  ooc_assert( hash && equal );

  map             = ooc_emalloc(sizeof *map);
  map->hash       = hash;
  map->equal      = equal;
  map->max_load   = max_load > 100 ? 100 : max_load;
  map->pool_csize = 0;
  map->pool       = 0;
  map->slot       = 0;

  if (cnt_hint < 16)
    cnt_hint = 16;

  map->slot_msk  = ooc_size_nextPow2(cnt_hint * (100.0/max_load));
  map->slot_curr = 0;
  map->slot_grow = map->slot_msk * (max_load/100.0);
  map->slot      = ooc_emalloc(chk_size(map->slot_msk, sizeof *map->slot));
  map->slot_msk -= 1;

  for (i = 0; i <= map->slot_msk; i++)
    map->slot[i] = 0;

  map->pool_cnt   = 0;
  map->pool_curr  = 0;
  map->pool_free  = 1;
  map->pool       = ooc_emalloc(chk_size(cnt_hint, csize));
  map->pool      -= csize;
  map->pool_csize = csize;

  for (i = 1; i < cnt_hint; i++)
    POOL(i)->next = i+1;
  POOL(i)->next = 0;

  unprotectPtr(map);

  OOC_DBG(("new map created: "
	   "max_load = %u%%, cnt_hint = %lu, csize = %lu bytes", max_load,
	   (unsigned long)cnt_hint, (unsigned long)csize));

  return map;
}

void
ooc_map_del_ (void *map_)
{
  OOC_DBG(("map del"));

  if (map_) {
    T map = map_;

    (ooc_free)(map->pool + map->pool_csize);
    ooc_free  (map->slot);
    ooc_free  (map);
  }
}

bool
ooc_map_size_(void *map_, size_t new_cnt)
{
  T map = map_;
  size_t pool_cnt, pool_idx;

  if (new_cnt < map->pool_cnt)
    throw(new(ExBadSize));

  if (!map->pool_free)
    return false;

  pool_cnt = map->pool_cnt;
  pool_idx = map->pool_free;

  while(pool_idx) {
    pool_idx = POOL(pool_idx)->next;
    ++pool_cnt;
  }

  if (new_cnt < pool_cnt) {
    size_t free_idx = map->pool_free;
    size_t slot_cnt = map->slot_msk+1;
    size_t slot_idx;
    size_t pool_prv;
  
    for (slot_idx = 0; slot_idx < slot_cnt; slot_idx++) {
      pool_idx = map->slot[slot_idx];
      pool_prv = 0;
	
      while (pool_idx) {
	if (pool_idx > new_cnt) {
	  size_t next;
	    
	  while(free_idx > new_cnt)
	    free_idx = POOL(free_idx)->next;
	  
	  next = POOL(free_idx)->next;
	  memcpy(POOL(free_idx), POOL(pool_idx), map->pool_csize);
	  if (pool_prv)
	    POOL(pool_prv)->next = free_idx;
	  else
	    map->slot[slot_idx] = free_idx;
	  free_idx = next;
	}
	
	pool_prv = pool_idx;
	pool_idx = POOL(pool_idx)->next;
      }
    }

    while(free_idx > new_cnt)
      free_idx = POOL(free_idx)->next;
    map->pool_free = pool_prv = free_idx;

    while(free_idx) {
      free_idx = POOL(free_idx)->next;

      while(free_idx > new_cnt)
	free_idx = POOL(free_idx)->next;
      pool_prv = POOL(pool_prv)->next = free_idx;
    }
  }

  {
    char *pool = map->pool + map->pool_csize;
    pool = ooc_erealloc(pool, chk_size(new_cnt, map->pool_csize));
    map->pool = pool - map->pool_csize;
    map->pool_cnt  = new_cnt;
    map->slot_curr = 0;
    map->pool_curr = 0;
  }

  if (new_cnt > pool_cnt) {
    for (pool_idx = pool_cnt+1; pool_idx < new_cnt; pool_idx++)
      POOL(pool_idx)->next = pool_idx+1;
    POOL(pool_idx)->next = map->pool_free;
    map->pool_free = pool_cnt+1;
  }

  return true;
}

void
ooc_map_grow_(void *map_)
{
  T map = map_;
  
  if (map->pool_cnt == map->slot_grow)
    enlarge_slot(map);
  
  if (!map->pool_free)
    enlarge_pool(map);
}

void
ooc_map_bad_(const char *file, int line)
{
  throwLoc(new(ExBadPosition), file, line);
}

/* template file, multiple inclusion allowed */

/*
 ******************************
 * Map interface
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: map_t.h,v 1.1 2005/07/04 13:52:09 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

/* NOTE-USER: Map interface

 o Types

   map_H : key   type (e.g. const char*)
   map_T : value type (e.g. struct my_struct)

 o Administration

   map      PREFIX_map_new     (unsigned max_load, // in %, [75%]
                                size_t   cnt_hint,
                                size_t (*hash )(map_H),
		                bool   (*equal)(map_H,map_H));
   void     PREFIX_map_del     (map m);
   size_t   PREFIX_map_cnt     (map m);
   unsigned PREFIX_map_load    (map m);     // in %
   void     PREFIX_map_resize  (map m, size_t cnt);

 o Absolute Access (returned value = false => not found,
                    set current position)

   bool     PREFIX_map_find    (map m, map_H key);
   bool     PREFIX_map_get     (map m, map_H key,       map_T *val);
   bool     PREFIX_map_put     (map m, map_H key, const map_T *val
					                map_T *orig_val);
   bool     PREFIX_map_remove  (map m, map_H key,
                                       map_H *orig_key, map_T *orig_val);

 o Relative Access (use current position)

   void     PREFIX_map_reset   (map m);
   void     PREFIX_map_set     (map m, map_T *val);
   void     PREFIX_map_key     (map m, map_T *key);
   void     PREFIX_map_value   (map m, map_T *val);
   void     PREFIX_map_erase   (map m);

 o Tranversal Access (use current position)

   bool     PREFIX_map_next    (map m); // false = no next

*/

#if !defined(map_H) || !defined(map_T)
#error "libooc: missing map_H or map_T definition"
#endif

#ifndef map_PREFIX
#define map_PREFIX map_T
#endif

/*
 * ----------
 *  Externals
 * ----------
 */

void*  ooc_map_new_ (unsigned max_load, size_t cnt_hint, size_t csize,
		     ooc_function hash, ooc_function equal);
void   ooc_map_del_ (void *map);
bool   ooc_map_size_(void *map, size_t cnt);
void   ooc_map_grow_(void *map);
void   ooc_map_bad_ (const char *file, int line);

/*
 * -------------------------------
 *  Map interface/implementation
 * -------------------------------
 */

#ifndef OOC_TYPE_MAP_C

#define T    OOC_CAT(map_PREFIX, _map)
#define C    F(cell)
#define F(f) OOC_CAT3(T,_,f)

typedef struct {
  size_t  (*hash )(map_H);
  bool    (*equal)(map_H,map_H);

  size_t   *slot;
  size_t    slot_msk;
  size_t    slot_curr;
  size_t    slot_grow;
  struct C *pool;
  size_t    pool_cnt;
  size_t    pool_curr;
  size_t    pool_free;
} *T;

struct C {
  size_t next;
  size_t hkey;
  map_H  key;
  map_T  val;
};

/*
 * Administration
 */

static inline T
F(new) (unsigned max_load, size_t cnt_hint,
	size_t (*hash )(map_H), bool (*equal)(map_H,map_H))
{
  return ooc_map_new_(max_load, cnt_hint, sizeof(struct C),
		      (ooc_function)hash, (ooc_function)equal);
}

static inline void
F(del) (T map)
{
  ooc_map_del_(map);
}

static inline size_t
F(cnt) (T map)
{
  return map->pool_cnt;
}

static inline unsigned
F(load) (T map)
{
  return (double)map->pool_cnt / (map->slot_msk + 1) * 100;
}

static inline bool
F(resize) (T map, size_t cnt)
{
  return ooc_map_size_(map, cnt);
}

/*
 * Relative Access
 */

static inline void
F(reset) (T map)
{
  map->slot_curr = 0;
  map->pool_curr = 0;
}

static inline void
F(set) (T map, const map_T *val)
{
  if (!map->pool_curr)
    ooc_map_bad_(__FILE__,__LINE__);
  
  map->pool[map->pool_curr].val = *val;
}

static inline void
F(key) (T map, map_H *key)
{
  if (!map->pool_curr)
    ooc_map_bad_(__FILE__,__LINE__);
  
  *key = map->pool[map->pool_curr].key;
}

static inline void
F(value) (T map, map_T *val)
{
  if (!map->pool_curr)
    ooc_map_bad_(__FILE__,__LINE__);
  
  *val = map->pool[map->pool_curr].val;
}

static inline void
F(erase) (T map)
{
  struct C *ref, *cell;

  if (!map->pool_curr)
    ooc_map_bad_(__FILE__,__LINE__);

  ref  = map->pool + map->pool_curr;
  cell = map->pool + map->slot[map->slot_curr];

  if (cell == ref) {
    map->slot[map->slot_curr] = cell->next;
    map->pool_curr = 0;
  } else {
    struct C *prev;
    
    do {
      prev = cell;
      cell = map->pool + cell->next;
    } while (cell != ref);

    prev->next = cell->next;
    map->pool_curr = prev - map->pool;
  }

  cell->next = map->pool_free;
  map->pool_free = ref - map->pool;
  --map->pool_cnt;
}

/*
 * Transversal Access
 */

static inline bool
F(next) (T map)
{
  size_t slot;

  if (map->pool_curr) {
    if (map->pool[map->pool_curr].next) {
      map->pool_curr = map->pool[map->pool_curr].next;
      return true;
    } else
      slot = map->slot_curr + 1;
  } else
    slot = map->slot_curr;

  while (slot <= map->slot_msk && !map->slot[slot])
    ++slot;
  
  if (slot > map->slot_msk) {
    F(reset)(map);
    return false;
  } else {
    map->slot_curr = slot;
    map->pool_curr = map->slot[slot];
    return true;
  }
}

/*
 * Absolute Access
 */

static inline bool
F(find_) (T map, map_H key, size_t hkey, size_t slot)
{
  size_t idx = map->slot[slot];

  while (idx) {
    struct C *cell = map->pool + idx;
    
    if (cell->hkey == hkey && map->equal(cell->key, key)) {
      map->slot_curr = slot;
      map->pool_curr = idx;
      return true;
    }
    
    idx = cell->next;
  }

  return false;
}

static inline bool
F(find) (T map, map_H key)
{
  size_t hkey = map->hash(key);
  size_t slot = hkey & map->slot_msk;

  return F(find_)(map, key, hkey, slot);
}

static inline bool
F(get) (T map, map_H key, map_T *val)
{
  if (F(find)(map, key)) {
    
    F(value)(map, val);
    return true;
  }
  
  return false;
}

static inline bool
F(put) (T map, map_H key, const map_T *val, map_T *orig_val)
{
  size_t hkey = map->hash(key);
  size_t slot = hkey & map->slot_msk;

  if (F(find_)(map, key, hkey, slot)) {
    if (orig_val)
      F(value)(map, orig_val);
    F(set)(map, val);

    return true;
  }

  if (!map->pool_free || map->pool_cnt == map->slot_grow)
    ooc_map_grow_(map);

  {
    size_t next = map->slot[slot];
    struct C *free_cell = map->pool + map->pool_free;
    
    map->slot_curr  = slot;
    map->pool_curr  = map->pool_free;
    map->slot[slot] = map->pool_free;
    map->pool_free  = free_cell->next;

    if (orig_val)
      *orig_val = free_cell->val;

    free_cell->next = next;
    free_cell->hkey = hkey;
    free_cell->key  = key;
    free_cell->val  = *val;

    ++map->pool_cnt;
  }

  return false;
}

static inline bool
F(remove) (T map, map_H key, map_H *orig_key, map_T *orig_val)
{
  if (F(find)(map, key)) {
    if (orig_key)
      F(key)(map, orig_key);
    if (orig_val)
      F(value)(map, orig_val);
    
    F(erase)(map);
    return true;
  }
  
  return false;
}

#undef T
#undef C
#undef F

#endif

#undef map_PREFIX
#undef map_T
#undef map_H

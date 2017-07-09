/* template file, multiple inclusion allowed */

/*
 ******************************
 * Raw Array interface
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: array_t.h,v 1.3 2006/11/27 16:59:39 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

/* NOTE-USER: raw array interface

   array_T : element type (e.g. int)
   array_T*: array   type (e.g. int*)

   array_T* PREFIX_array_new    (size_t cnt );
   array_T* PREFIX_array_alloc  (size_t cnt );
   array_T* PREFIX_array_cpy    (array_T *a1 , const array_T *a2);
   array_T* PREFIX_array_rawcpy (array_T *a1 , const array_T *src, size_t cnt);
   array_T* PREFIX_array_dup    (const array_T *a );
   array_T* PREFIX_array_rawdup (const array_T *src, size_t cnt);
   array_T* PREFIX_array_resize (array_T *a  , size_t cnt);
   array_T* PREFIX_array_realloc(array_T *a  , size_t cnt);
   void     PREFIX_array_del    (array_T *a );
   void     PREFIX_array_free   (array_T *a );
   size_t   PREFIX_array_cnt    (const array_T *a );
   array_T  PREFIX_array_get    (const array_T *a, size_t idx);
   void     PREFIX_array_set    (array_T *a, size_t idx, array_T val);
*/

#ifndef array_T
#error "libooc: missing array_T definition"
#endif

#ifndef array_PREFIX
#define array_PREFIX array_T
#endif

/*
 * ----------
 *  Externals
 * ----------
 */

void* ooc_array_new_   (            size_t cnt     , size_t esize, size_t hsize, bool ex);
void* ooc_array_resize_(void* self, size_t cnt     , size_t esize, size_t hsize, bool ex);
void* ooc_array_cpy_   (void* dst , const void* src, size_t esize, size_t hsize);
void* ooc_array_rawcpy_(void* dst , const void* src, size_t esize, size_t hsize, size_t cnt);
void* ooc_array_dup_   (            const void* src, size_t esize, size_t hsize);
void* ooc_array_rawdup_(            const void* src, size_t esize, size_t hsize, size_t cnt);
void  ooc_array_badrng_(const char *file, int line);

/*
 * -------------------------------
 *  Array interface/implementation
 * -------------------------------
 */

#ifndef OOC_TYPE_ARRAY_C

#define T    OOC_CAT(array_PREFIX, _array)
#define F(f) OOC_CAT3(T,_,f)
#define B(p) ((struct T*)((char*)(p) - offsetof(struct T, data)))

struct T {
  const size_t cnt;  /* read-only field */
#if OOC_ISO_C < OOC_ISO_C99
  array_T data[1];   /* public field, undefined behavior, but... */
#else
  array_T data[];    /* public field, defined behavior */
#endif
};

static inline array_T*
F(new) (size_t cnt)
{
  return
    ooc_array_new_(cnt, sizeof(array_T), offsetof(struct T, data), true);
}

static inline array_T*
F(alloc) (size_t cnt)
{
  return
    ooc_array_new_(cnt, sizeof(array_T), offsetof(struct T, data), false);
}

static inline array_T*
F(cpy) (array_T *dst, const array_T *src)
{
  return ooc_array_cpy_((void*)dst, (void*)src,
			sizeof(array_T), offsetof(struct T, data));
}

static inline array_T*
F(rawcpy) (array_T *dst, const array_T *src, size_t cnt)
{
  return ooc_array_rawcpy_((void*)dst, (void*)src,
			   sizeof(array_T), offsetof(struct T, data), cnt);
}

static inline array_T*
F(dup) (const array_T *src)
{
  return ooc_array_dup_((void*)src, sizeof(array_T),
			offsetof(struct T, data));
}

static inline array_T*
F(rawdup) (const array_T *src, size_t cnt)
{
  return ooc_array_rawdup_((void*)src, sizeof(array_T),
			   offsetof(struct T, data), cnt);
}

static inline array_T*
F(resize) (array_T *self, size_t cnt)
{
  return ooc_array_resize_((void*)self, cnt,
			   sizeof(array_T), offsetof(struct T, data), true);
}

static inline array_T*
F(realloc) (array_T *self, size_t cnt)
{
  return ooc_array_resize_((void*)self, cnt,
			   sizeof(array_T), offsetof(struct T, data), false);
}

static inline void
F(del) (array_T *self)
{
  if (self)
    (ooc_free)(B(self));
}

static inline void
F(free) (array_T *self)
{
  F(del)(self);
}

static inline size_t
F(cnt) (const array_T *self)
{
  return B(self)->cnt;
}

static inline array_T
F(get) (const array_T *self, size_t idx)
{
  if (idx >= B(self)->cnt)
    ooc_array_badrng_(__FILE__, __LINE__);
  
  return self[idx];
}

static inline void
F(set) (array_T *self, size_t idx, array_T val)
{
  if (idx >= B(self)->cnt)
    ooc_array_badrng_(__FILE__, __LINE__);
  
  self[idx] = val;
}

#undef T
#undef F
#undef B

#endif

#undef array_PREFIX
#undef array_T


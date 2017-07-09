/*
 ******************************
 * StaticField implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: StaticField.c,v 1.12 2005/12/16 16:56:03 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <string.h>
#include <ooc/Object.h>
#include <ooc/assert.h>
#include <ooc/type/stdType.h>
#include <ooc/type/Type.h>
#include <ooc/ex/ExBadType.h>
#include <ooc/ex/ExBadArgument.h>
#include <ooc/ex/ExBadAccess.h>
#include <ooc/ex/ExNotSupported.h>

#include Implementation

#define StaticField_PRIVATE_DEF			\
        private(struct ooc_meta_fld*, meta)	\
        private(constClass          , cls )	\
        private(constType           , type)

#include <ooc/reflect/StaticField.h>

static inline int
get_qualifier(constSELF)
{
  return *(self->meta->name-1);
}

static inline bool
is_array(constSELF)
{
  return *(self->meta->name-3) == ']';
}

/*
 * Initialization
 */

method2(TYPE, initWith, constClass cls, struct ooc_meta_fld *meta)
{
  scall0(init);

  self->cls  = cls;
  self->meta = meta;
  self->type = 0;

  if (!ooc_typeIsEncoded(self->meta->type)) {
    const char *ptr, *end;

    for (ptr = self->meta->name-3; *ptr; --ptr)
      ;
    
    self->meta->type = ooc_typeEncodeFromStr(++ptr, &end);
    ooc_assert(ooc_typeIsValid(self->meta->type) && *end == '\0');
  }

  return self;
}

method0(void, deinit)
{
  if (self->type)
    release(self->type);

  scall0(deinit);
}

/*
 * Getters
 */

constMethod0(const char*, getName)
{
  return self->meta->name;
}

constMethod0(constClass, getClass)
{
  return self->cls;
}

constMethod0(constType, getType)
{
  if (!self->type) {
    TYPE fld = (TYPE)self;

    fld->type = own(new1(Type, initWith, self->meta->type));
  }

  return self->type;
}

constMethod0(int, getQualifier)
{
  return get_qualifier(self);
}

constMethod0(size_t, getSize)
{
  return self->meta->elem_size;
}

constMethod0(size_t, getCnt)
{
  return self->meta->elem_cnt;
}

constMethod1(constObject, get, constObject obj)
{
  char *ref;

  ooc_assert(obj);

  if (!isInstanceOf(obj, self->cls))
    throw(new(ExBadArgument));

  if (get_qualifier(self) == 'P')
    throw(new(ExBadAccess));

  ref = (char*)obj + self->meta->offset;

  switch (ooc_typeDecode(self->meta->type)) {
  case ooc_type_object:
    return *(Object*)ref;

  case ooc_type_enum:
  case ooc_type_struct:
  case ooc_type_union:
  case ooc_type_typedef: {
    TypedArrayPtr v = drop(new(TypedArrayPtr));
    v->ptr  = ref;
    v->cnt  = self->meta->elem_cnt;
    v->size = self->meta->elem_size * self->meta->elem_cnt;
    v->type = self->meta->type;
    return (Object)v;
  }

  case ooc_type_pointer: {
    TypedArrayPtr v = drop(new(TypedArrayPtr));
    if (is_array(self)) {
      v->ptr  = ref;
      v->cnt  = self->meta->elem_cnt;
      v->size = self->meta->elem_size * self->meta->elem_cnt;
      v->type = self->meta->type;
    } else {
      v->ptr  = *(void**)ref;
      v->cnt  = 1;
      v->size = ooc_typeSize(self->meta->type);
      v->type = self->meta->type;
    }
    return (Object)v;
  }

  case ooc_type_function: {
    Function v = drop(new(Function));
    v->fct = *(ooc_function*)ref;
    return (Object)v;
  }

  case ooc_type_bool: {
    Bool v = drop(new(Bool));
    v->val = *(bool*)ref;
    return (Object)v;
  }

  case ooc_type_char:
  case ooc_type_unsigned_char: {
    Char v = drop(new(Char));
    v->val = *(unsigned char*)ref;
    return (Object)v;
  }

  case ooc_type_short:
  case ooc_type_unsigned_short: {
    Int v = drop(new(Int));
    v->val = *(short*)ref;
    return (Object)v;
  }

  case ooc_type_int:
  case ooc_type_unsigned_int: {
    Int v = drop(new(Int));
    v->val = *(int*)ref;
    return (Object)v;
  }

  case ooc_type_long:
  case ooc_type_unsigned_long: {
    Long v = drop(new(Long));
    v->val = *(long*)ref;
    return (Object)v;
  }

  case ooc_type_long_long:
  case ooc_type_unsigned_long_long: {
    LongLong v = drop(new(LongLong));
    v->val = *(ooc_llong*)ref;
    return (Object)v;
  }

  case ooc_type_float: {
    Float v = drop(new(Float));
    v->val = *(float*)ref;
    return (Object)v;
  }

  case ooc_type_double: {
    Double v = drop(new(Double));
    v->val = *(double*)ref;
    return (Object)v;
  }

  case ooc_type_long_double: {
    LongDouble v = drop(new(LongDouble));
    v->val = *(long double*)ref;
    return (Object)v;
  }

  case ooc_type_complex: {
    Complex v = drop(new(Complex));
    v->val = *(ooc_complex*)ref;
    return (Object)v;
  }

  case ooc_type_invalid:
  case ooc_type_not_scan:
  default:
    throw(new(ExNotSupported));
    return 0;
  }

  throw(new(ExNotSupported));
  return 0;
}

#define GET1(M, T, TYPE)				\
constMethod1(T, get##M, constObject obj)		\
{							\
  ooc_assert(obj);					\
							\
  if (!isInstanceOf(obj, self->cls))			\
    throw(new(ExBadArgument));				\
							\
  if (get_qualifier(self) == 'P')			\
    throw(new(ExBadAccess));				\
							\
  if (ooc_typeDecode(self->meta->type) != TYPE)		\
    throw(new(ExBadType));				\
							\
  return *(T*)((char*)obj + self->meta->offset);	\
}

#define GET2(M, T, TYPE1, TYPE2)			\
constMethod1(T, get##M, constObject obj)		\
{							\
  enum ooc_type_id type;				\
							\
  ooc_assert(obj);					\
							\
  if (!isInstanceOf(obj, self->cls))			\
    throw(new(ExBadArgument));				\
							\
  if (get_qualifier(self) == 'P')			\
    throw(new(ExBadAccess));				\
							\
  type = ooc_typeDecode(self->meta->type);		\
	  						\
  if (type != TYPE1 && type != TYPE2)			\
    throw(new(ExBadType));				\
							\
  return *(T*)((char*)obj + self->meta->offset);	\
}

constMethod1(int, getChr, constObject obj)
{
  enum ooc_type_id type;

  ooc_assert(obj);

  if (!isInstanceOf(obj, self->cls))
    throw(new(ExBadArgument));

  if (get_qualifier(self) == 'P')
    throw(new(ExBadAccess));

  type = ooc_typeDecode(self->meta->type);

  if (type != ooc_type_char && type != ooc_type_unsigned_char)
    throw(new(ExBadType));

  return *(unsigned char*)((char*)obj + self->meta->offset);
}

GET1(Bool , bool         , ooc_type_bool       )
GET2(Int  , int          , ooc_type_int        , ooc_type_unsigned_int      )
GET2(Lng  , long         , ooc_type_long       , ooc_type_unsigned_long     )
GET2(LLng , ooc_llong    , ooc_type_long_long  , ooc_type_unsigned_long_long)
GET1(Flt  , float        , ooc_type_float      )
GET1(Dbl  , double       , ooc_type_double     )
GET1(LDbl , long double  , ooc_type_long_double)
GET1(Cpx  , ooc_complex  , ooc_type_complex    )
GET1(Ptr  , void*        , ooc_type_pointer    )
GET1(Fct  , ooc_function , ooc_type_function   )

/*
 * Setters
 */

constMethod2(void, set, Object obj, Object val)
{
  char *ref;

  ooc_assert(obj);

  if (!isInstanceOf(obj, self->cls))
    throw(new(ExBadArgument));

  if (get_qualifier(self) != 'W')
    throw(new(ExBadAccess));

  ref = (char*)obj + self->meta->offset;

  switch (ooc_typeDecode(self->meta->type)) {
  case ooc_type_object: {
    Object *fld = (Object*)ref;

    if (*fld) {
      if (!isSame(val, *fld))
	throw(new(ExBadArgument));
      
      release(*fld);
    }

    *fld = retain(val);
    return;
  }

  case ooc_type_enum:
  case ooc_type_struct:
  case ooc_type_union:
  case ooc_type_typedef: {
    ArrayPtr v = ecastTo(val, ArrayPtr);
    memcpy(ref, v->ptr, v->size);
    return;
  }

  case ooc_type_pointer: {
    if (is_array(self)) {
      ArrayPtr v = ecastTo(val, ArrayPtr);
      memcpy(ref, v->ptr, v->size);
    } else
      *(void**)ref = ecastTo(val, Pointer)->ptr;
    return;
  }
    
  case ooc_type_function: {
    *(ooc_function*)ref = ecastTo(val, Function)->fct;
    return;			    				   
  }
    
  case ooc_type_bool: {
    *(bool*)ref = ecastTo(val, Bool)->val;
    return;			    				   
  }
    
  case ooc_type_char:
  case ooc_type_unsigned_char: {
    *(unsigned char*)ref = ecastTo(val, Char)->val;
    return;
  }

  case ooc_type_short:
  case ooc_type_unsigned_short: {
    *(short*)ref = ecastTo(val, Int)->val;
    return;			    				   
  }

  case ooc_type_int:
  case ooc_type_unsigned_int: {
    *(int*)ref = ecastTo(val, Int)->val;
    return;			    				   
  }

  case ooc_type_long:
  case ooc_type_unsigned_long: {
    *(long*)ref = ecastTo(val, Long)->val;
    return;			    				   
  }

  case ooc_type_long_long:
  case ooc_type_unsigned_long_long: {
    *(ooc_llong*)ref = ecastTo(val, LongLong)->val;
    return;			    				   
  }

  case ooc_type_float: {
    *(float*)ref = ecastTo(val, Float)->val;
    return;			    				   
  }

  case ooc_type_double: {
    *(double*)ref = ecastTo(val, Double)->val;
    return;			    				   
  }

  case ooc_type_long_double: {
    *(long double*)ref = ecastTo(val, LongDouble)->val;
    return;			    				   
  }

  case ooc_type_complex: {
    *(ooc_complex*)ref = ecastTo(val, Complex)->val;
    return;			    				 
  }  

  case ooc_type_invalid:
  case ooc_type_not_scan:
  default:
    throw(new(ExNotSupported));
  }
  
  throw(new(ExNotSupported));
}

#define SET1(M, T, TYPE)			\
constMethod2(void, set##M, Object obj, T val)	\
{						\
  ooc_assert(obj);				\
						\
  if (!isInstanceOf(obj, self->cls))		\
    throw(new(ExBadArgument));			\
						\
  if (get_qualifier(self) != 'W')		\
    throw(new(ExBadAccess));			\
						\
  if (ooc_typeDecode(self->meta->type) != TYPE)	\
    throw(new(ExBadType));			\
						\
  *(T*)((char*)obj + self->meta->offset) = val;	\
}

#define SET2(M, T, TYPE1, TYPE2)		\
constMethod2(void, set##M, Object obj, T val)	\
{						\
  enum ooc_type_id type;			\
						\
  ooc_assert(obj);				\
						\
  if (!isInstanceOf(obj, self->cls))		\
    throw(new(ExBadArgument));			\
						\
  if (get_qualifier(self) != 'W')		\
    throw(new(ExBadAccess));			\
						\
   type = ooc_typeDecode(self->meta->type);	\
						\
  if (type != TYPE1 && type != TYPE2)		\
    throw(new(ExBadType));			\
						\
  *(T*)((char*)obj + self->meta->offset) = val;	\
}

constMethod2(void, setChr, Object obj, int val)
{
  enum ooc_type_id type;

  ooc_assert(obj);

  if (!isInstanceOf(obj, self->cls))
    throw(new(ExBadArgument));

  if (get_qualifier(self) != 'W')
    throw(new(ExBadAccess));

  type = ooc_typeDecode(self->meta->type);

  if (type != ooc_type_char && type != ooc_type_unsigned_char)
    throw(new(ExBadType));

  *(unsigned char*)((char*)obj + self->meta->offset) = val;
}

SET1(Bool , bool         , ooc_type_bool       )
SET2(Int  , int          , ooc_type_int        , ooc_type_unsigned_int      )
SET2(Lng  , long         , ooc_type_long       , ooc_type_unsigned_long     )
SET2(LLng , ooc_llong    , ooc_type_long_long  , ooc_type_unsigned_long_long)
SET1(Flt  , float        , ooc_type_float      )
SET1(Dbl  , double       , ooc_type_double     )
SET1(LDbl , long double  , ooc_type_long_double)
SET1(Cpx  , ooc_complex  , ooc_type_complex    )
SET1(Ptr  , void*        , ooc_type_pointer    )
SET1(Fct  , ooc_function , ooc_type_function   )

/*
 * By reference
 */

constMethod2(void, getByRef, constObject obj, void* dst)
{
  ooc_assert(obj && dst);

  if (get_qualifier(self) == 'P')
    throw(new(ExBadAccess));

  memcpy(dst, (char*)obj + self->meta->offset, 
	 self->meta->elem_size * self->meta->elem_cnt);
}

constMethod2(void, setByRef, Object obj, const void* src)
{
  ooc_assert(obj && src);

  if (get_qualifier(self) != 'W')
    throw(new(ExBadAccess));

  memcpy((char*)obj + self->meta->offset, src, 
	 self->meta->elem_size * self->meta->elem_cnt);
}

/*
 * Class methods
 */

staticMethod0(void, initialize)
{
  inhibit(init);

  override( initWith     );
  override( deinit       );

  override( getName      );
  override( getClass     );
  override( getType      );
  override( getQualifier );
  override( getSize      );
  override( getCnt       );

  override( get          );
  override( getBool      );
  override( getChr       );
  override( getInt       );
  override( getLng       );
  override( getLLng      );
  override( getFlt       );
  override( getDbl       );
  override( getLDbl      );
  override( getCpx       );
  override( getPtr       );
  override( getFct       );

  override( set          );
  override( setBool      );
  override( setChr       );
  override( setInt       );
  override( setLng       );
  override( setLLng      );
  override( setFlt       );
  override( setDbl       );
  override( setLDbl      );
  override( setCpx       );
  override( setPtr       );
  override( setFct       );

  override( getByRef     );
  override( setByRef     );
}

#include End

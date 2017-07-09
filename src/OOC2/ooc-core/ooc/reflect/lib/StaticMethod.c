/*
 ******************************
 * StaticField implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: StaticMethod.c,v 1.12 2005/12/09 17:43:10 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <string.h>
#include <stdlib.h>
#include <ooc/Object.h>
#include <ooc/assert.h>
#include <ooc/type/stdType.h>
#include <ooc/type/ctype.h>
#include <ooc/ex/ExBadType.h>
#include <ooc/ex/ExNotSupported.h>
#include <ooc/ex/ExBadArgument.h>

#if OOC_FFI_USE
#include OOC_FFI_HDR
#endif

/*
 * Class implementation
 */

#include Implementation

#define StaticMethod_PRIVATE_DEF		\
        private(struct ooc_meta_mth*, meta  )	\
        private(constClass          , cls   )	\
        private(constType           , retype)	\
        private(constType*          , types )

#include <ooc/reflect/StaticMethod.h>

/*
 * Local declaration
 */

enum { max_objparam = 10, max_param = 32 };

/*
 * Static methods
 */

static inline
int
get_qualifier(constSELF)
{
  return *(self->meta->name-1);
}

static inline
bool
is_ret_compat(void)
{
  return sizeof(void*) == sizeof(ooc_function) &&
         sizeof(void*) == sizeof(Object);
}

static inline
void
init_types_info(SELF)
{
  static const char *self_str[] = { "Object self)", "constObject self)" };
  
  const char *ptr, *param, *end;
  ooc_type type;
  size_t param_obj = 0;
  size_t i;

  for (ptr = self->meta->name-3; *ptr; --ptr);
  param = ptr+1;
    
  ooc_assert( *param++ == '(' );
    
  if (self->meta->param_cnt == (unsigned char)-1) { /* C99 */
    size_t n_param = 0;
      
    do {
      type = ooc_typeEncodeFromStr(param, &end);
	
      ooc_assert(ooc_typeIsValid(type) && (*end == ',' || *end == ')'));
	
      ++n_param, param = end;
    } while (*end != ')');
      
    self->meta->param_cnt = get_qualifier(self) != 'S' ? n_param+1 : n_param;
    param = ptr+2;
  }
    
  for (--ptr; *ptr; --ptr);
    
  /* alloc memory */
  self->meta->type = 
    ooc_emalloc((1+self->meta->param_cnt) * sizeof(ooc_type));
    
  /* return type */
  self->meta->type[0] = ooc_typeEncodeFromStr(++ptr, &end);
  ooc_assert(ooc_typeIsValid(self->meta->type[0]) && *end == '\0');
    
  /* parameters */
  if (get_qualifier(self) != 'S') {
    const char *str = get_qualifier(self) == 'W' ? self_str[0] : self_str[1];
    
    self->meta->type[1] = ooc_typeEncodeFromStr(str, &end);

    ooc_assert(ooc_typeIsObject(self->meta->type[1], 0) && *end == ')');
    
    ++param_obj;
  }

  for (i = param_obj+1; i <= self->meta->param_cnt; ++i) {
    self->meta->type[i] = ooc_typeEncodeFromStr(param, &end);
    
    ooc_assert(ooc_typeIsValid(self->meta->type[i]) && 
	       (*end == ',' || *end == ')'));
      
    if (ooc_typeIsObject(self->meta->type[i], 0))
      ++param_obj;

    if (*end == ')')
      break;

    param = end;
  }

  ooc_assert(i >= self->meta->param_cnt && *end == ')');

  self->meta->param_obj =
    self->meta->param_cnt == param_obj && is_ret_compat();
}

/*
 * Object methods
 */

method2(TYPE, initWith, constClass cls, struct ooc_meta_mth *meta)
{
  scall0(init);

  self->cls    = cls;
  self->meta   = meta;
  self->retype = 0;
  self->types  = 0;

  if (!self->meta->type)
    init_types_info(self);

  return self;
}

method0(void, deinit)
{
  if (self->types) {
    size_t i;

    for (i = 0; i < self->meta->param_cnt; ++i)
      if (self->types[i])
	release(self->types[i]);

    ooc_free(self->types);
  }

  if (self->retype)
    release(self->retype);
  
  scall0(deinit);
}

constMethod0(const char*, getName)
{
  return self->meta->name;
}

constMethod0(constClass, getClass)
{
  return self->cls;
}

constMethod0(int, getQualifier)
{
  return get_qualifier(self);
}

constMethod0(constType, getRtnType)
{
  if (!self->retype) {
    TYPE self_ = (TYPE)self;

    self_->retype = own(new1(Type, initWith, self->meta->type[0]));
  }

  return self->retype;
}

constMethod0(size_t, getRtnSize)
{
  return ooc_typeSize(self->meta->type[0]);
}

constMethod0(size_t, getParamCnt)
{
  return self->meta->param_cnt;
}

constMethod1(constType, getParamType, size_t idx)
{
  TYPE self_ = (TYPE)self;

  ooc_assert(idx < self->meta->param_cnt);

  if (!self->types) {
    size_t i;
    
    self_->types = ooc_emalloc(self->meta->param_cnt * sizeof(constType));
    
    for (i = 0; i < self->meta->param_cnt; i++)
      self->types[i] = 0;
  }
  
  if (!self->types[idx]) 
    self_->types[idx] = own(new1(Type, initWith, self->meta->type[idx+1]));
  
  return self->types[idx];
}

constMethod1(size_t, getParamSize, size_t idx)
{
  ooc_assert(idx < self->meta->param_cnt);

  return ooc_typeSize(self->meta->type[idx]);
}

/*
 * Generic Method Invocation
 */

constMethod1(Object, invoke, Object O[])
{
  ooc_function fct;
  int qualifier = get_qualifier(self);

  if (qualifier != 'S' && !isInstanceOf(O[0], self->cls))
    throw(new(ExBadArgument));

  fct = *(ooc_function*)((char*)self->cls + self->meta->offset);

  if (self->meta->param_obj) {
    union ooc_ctype ret;

    OOC_DBG(("OBJ INVOKE"));

#define INVOKE ((FCT*)fct)
#define OBJ    Object
    switch(self->meta->param_cnt) {
    case 1: {
      typedef void*(FCT)(OBJ);
      ret.p = INVOKE(O[0]);
    } break;
    case 2: {
      typedef void*(FCT)(OBJ,OBJ);
      ret.p = INVOKE(O[0],O[1]);
    } break;
    case 3: {
      typedef void*(FCT)(OBJ,OBJ,OBJ);
      ret.p = INVOKE(O[0],O[1],O[2]);
    } break;
    case 4: {
      typedef void*(FCT)(OBJ,OBJ,OBJ,OBJ);
      ret.p = INVOKE(O[0],O[1],O[2],O[3]);
    } break;
    case 5: {
      typedef void*(FCT)(OBJ,OBJ,OBJ,OBJ,OBJ);
      ret.p = INVOKE(O[0],O[1],O[2],O[3],O[4]);
    } break;
    case 6: {
      typedef void*(FCT)(OBJ,OBJ,OBJ,OBJ,OBJ,OBJ);
      ret.p = INVOKE(O[0],O[1],O[2],O[3],O[4],O[5]);
    } break;
    case 7: {
      typedef void*(FCT)(OBJ,OBJ,OBJ,OBJ,OBJ,OBJ,OBJ);
      ret.p = INVOKE(O[0],O[1],O[2],O[3],O[4],O[5],O[6]);
    } break;
    case 8: {
      typedef void*(FCT)(OBJ,OBJ,OBJ,OBJ,OBJ,OBJ,OBJ,OBJ);
      ret.p = INVOKE(O[0],O[1],O[2],O[3],O[4],O[5],O[6],O[7]);
    } break;
    case 9: {
      typedef void*(FCT)(OBJ,OBJ,OBJ,OBJ,OBJ,OBJ,OBJ,OBJ,OBJ);
      ret.p = INVOKE(O[0],O[1],O[2],O[3],O[4],O[5],O[6],O[7],O[8]);
    } break;
    case 10: { /* max_objparam */
      typedef void*(FCT)(OBJ,OBJ,OBJ,OBJ,OBJ,OBJ,OBJ,OBJ,OBJ,OBJ);
      ret.p = INVOKE(O[0],O[1],O[2],O[3],O[4],O[5],O[6],O[7],O[8],O[9]);
    } break;
    default:
      throw(new(ExNotSupported));
      return 0; /* cc warning */
    }
#undef INVOKE
#undef OBJ

    if (ooc_typeIsObject(self->meta->type[0], 0))
      return ret.p;

    switch (ooc_typeDecode(self->meta->type[0])) {
    case ooc_type_void: 
      return 0;

    case ooc_type_function: {
      Function retobj = drop(new(Function));
      retobj->fct = ret.fp;
      return (Object)retobj;
    }
      
    case ooc_type_pointer: {
      TypedArrayPtr retobj = drop(new(TypedArrayPtr));
      retobj->ptr  = ret.p;
      retobj->cnt  = 1;
      retobj->size = ooc_typeSize(self->meta->type[0]);
      retobj->type = self->meta->type[0];
      return (Object)retobj;
    }

    case ooc_type_invalid:
    case ooc_type_not_scan:
    default:
      throw(new(ExNotSupported));
      return 0;
    }
  }

#if OOC_FFI_USE
  else if (self->meta->param_cnt <= max_param) {
    ffi_cif         cif;
    ffi_type       *rettyp;
    ffi_type       *types[max_param];
    void           *values[max_param];
    void           *retval;
    union ooc_ctype rettmp;
    Object          retobj = 0;
    int n;

    static ffi_type *cpx_elem[3] = { &ffi_type_double, &ffi_type_double , 0 };
    static ffi_type  cpx_type    = { 0, 0, FFI_TYPE_STRUCT, cpx_elem };

    /* returned type */
    if (ooc_typeIsObject(self->meta->type[0], 0)) {
      retval = &retobj;
      rettyp = &ffi_type_pointer;
    } else {      
      
      switch (ooc_typeDecode(self->meta->type[0])) {
      case ooc_type_void: {
	retval = 0;
	rettyp = &ffi_type_void;
	break;
      }

      case ooc_type_bool: {
	retval = &rettmp;
	rettyp = &ffi_type_uchar;
	break;
      }

      case ooc_type_char: 
      case ooc_type_unsigned_char: {
	retval = &rettmp;
	rettyp = &ffi_type_schar;
	break;
      }

      case ooc_type_short:
      case ooc_type_unsigned_short: {
	retval = &rettmp;
	rettyp = &ffi_type_sshort;
	break;
      }

      case ooc_type_int:
      case ooc_type_unsigned_int: {
	retval = &rettmp;
	rettyp = &ffi_type_sint;
	break;
      }

      case ooc_type_long:
      case ooc_type_unsigned_long: {
	retval = &rettmp;
	rettyp = &ffi_type_slong;
	break;
      }

      case ooc_type_long_long:
      case ooc_type_unsigned_long_long: {
	retval = &rettmp;
	rettyp = &ffi_type_slong;
	break;
      }

      case ooc_type_float: {
	retval = &rettmp;
	rettyp = &ffi_type_float;
	break;
      }

      case ooc_type_double: {
	retval = &rettmp;
	rettyp = &ffi_type_double;
	break;
      }

      case ooc_type_long_double: {
	retval = &rettmp;
	rettyp = &ffi_type_longdouble;
	break;
      }

      case ooc_type_complex: {
	retval = &rettmp;
	rettyp = &cpx_type;
	break;
      }

      case ooc_type_pointer: {
	retval = &rettmp;
	rettyp = &ffi_type_pointer;
      }

      case ooc_type_function: {
	if (sizeof(ooc_function) != sizeof(void*)) 
	  throw(new(ExNotSupported));
	
	retval = &rettmp;
	rettyp = &ffi_type_pointer;
	break;
      }

      case ooc_type_invalid:
      case ooc_type_not_scan:
      default:
	throw(new(ExNotSupported));
	return 0;
      }
    }
    
    /* method arguments */
    for (n = 0; n < self->meta->param_cnt; ++n) {

      if (ooc_typeIsObject(self->meta->type[n+1], 0)) {
	values[n] = &O[n];
	types [n] = &ffi_type_pointer;

      } else {
	switch (ooc_typeDecode(self->meta->type[n+1])) {
	
	case ooc_type_bool: {
	  values[n] = &ecastTo(O[n], Bool)->val;
	  types [n] = &ffi_type_uchar;
	  break;
	}
	  
	case ooc_type_char: 
	case ooc_type_unsigned_char: {
	  values[n] = &ecastTo(O[n], Char)->val;
	  types [n] = &ffi_type_schar;
	  break;
	}
	  
	case ooc_type_short:
	case ooc_type_unsigned_short: {
	  values[n] = &ecastTo(O[n], Int)->val;
	  types [n] = &ffi_type_sshort;
	  break;
	}

	case ooc_type_int:
	case ooc_type_unsigned_int: {
	  values[n] = &ecastTo(O[n], Int)->val;
	  types [n] = &ffi_type_sint;
	  break;
	}

	case ooc_type_long:
	case ooc_type_unsigned_long: {
	  values[n] = &ecastTo(O[n], Long)->val;
	  types [n] = &ffi_type_slong;
	  break;
	}

	case ooc_type_long_long:
	case ooc_type_unsigned_long_long: {
	  values[n] = &ecastTo(O[n], LongLong)->val;
	  types [n] = &ffi_type_slong;
	  break;
	}

	case ooc_type_float: {
	  values[n] = &ecastTo(O[n], Float)->val;
	  types [n] = &ffi_type_float;
	  break;
	}

	case ooc_type_double: {
	  values[n] = &ecastTo(O[n], Double)->val;
	  types [n] = &ffi_type_double;
	  break;
	}

	case ooc_type_long_double: {
	  values[n] = &ecastTo(O[n], LongDouble)->val;
	  types [n] = &ffi_type_longdouble;
	  break;
	}
      
	case ooc_type_complex: {
	  values[n] = &ecastTo(O[n], Complex)->val;
	  types [n] = &cpx_type;
	  break;
	}

	case ooc_type_pointer: {
	  values[n] = &ecastTo(O[n], ArrayPtr)->ptr;
	  types [n] = &ffi_type_pointer;
	  break;
	}

	case ooc_type_function: {
	  if (sizeof(ooc_function) != sizeof(void*))
	    throw(new(ExNotSupported));

	  values[n] = &ecastTo(O[n], Function)->fct;
	  types [n] = &ffi_type_pointer;
	  break;
	}
	
	case ooc_type_invalid:
	case ooc_type_not_scan:
	default:
	  throw(new(ExNotSupported));
	  return 0;
	}
      }
    }

    if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 
		     self->meta->param_cnt, rettyp, types) != FFI_OK)
      throw(new(ExBadType));

    ffi_call(&cif, fct, retval, values);

    if (ooc_typeIsObject(self->meta->type[0], 0))
      return retobj;

    switch (ooc_typeDecode(self->meta->type[0])) {
    case ooc_type_void:
      return 0;

    case ooc_type_bool: {
      Bool retobj = drop(new(Bool));
      retobj->val = rettmp.c;
      return (Object)retobj;
    }

    case ooc_type_char:
    case ooc_type_unsigned_char: {
      Char retobj = drop(new(Char));
      retobj->val = rettmp.c;
      return (Object)retobj;
    }
	    
    case ooc_type_short:
    case ooc_type_unsigned_short: {
      Int retobj = drop(new(Int));
      retobj->val = rettmp.h;
      return (Object)retobj;
    }
    
    case ooc_type_int:
    case ooc_type_unsigned_int: {
      Int retobj = drop(new(Int));
      retobj->val = rettmp.i;
      return (Object)retobj;
    }

    case ooc_type_long:
    case ooc_type_unsigned_long: {
      Long retobj = drop(new(Long));
      retobj->val = rettmp.l;
      return (Object)retobj;
    }
	
    case ooc_type_long_long:
    case ooc_type_unsigned_long_long: {
      LongLong retobj = drop(new(LongLong));
      retobj->val = rettmp.ll;
      return (Object)retobj;
    }

    case ooc_type_float: {
      Float retobj = drop(new(Float));
      retobj->val = rettmp.f;
      return (Object)retobj;
    }

    case ooc_type_double: {
      Double retobj = drop(new(Double));
      retobj->val = rettmp.d;
      return (Object)retobj;
    }

    case ooc_type_long_double: {
      LongDouble retobj = drop(new(LongDouble));
      retobj->val = rettmp.ld;
      return (Object)retobj;
    }

    case ooc_type_complex: {
      Complex retobj = drop(new(Complex));
      retobj->val = rettmp.z;
      return (Object)retobj;
    }

    case ooc_type_function: {
      Function retobj = drop(new(Function));
      retobj->fct = rettmp.fp;
      return (Object)retobj;
    }
    
    case ooc_type_pointer: {
      TypedArrayPtr retobj = drop(new(TypedArrayPtr));
      retobj->ptr  = rettmp.p;
      retobj->cnt  = 1;
      retobj->size = ooc_typeSize(self->meta->type[0]);
      retobj->type = self->meta->type[0];
      return (Object)retobj;
    }

    case ooc_type_invalid:
    case ooc_type_not_scan:
    default:
      throw(new(ExNotSupported));
      return 0;
    }
      
  }
#endif

  throw(new(ExNotSupported));
  return 0;
}

/*
 * Static methods
 */

staticMethod0(void, initialize)
{
  inhibit(init);

  override( initWith     );
  override( deinit       );

  override( getName      );
  override( getClass     );
  override( getQualifier );
  override( getRtnType   );
  override( getRtnSize   );
  override( getParamCnt  );
  override( getParamType );
  override( getParamSize );

  override( invoke       );
}

#include End

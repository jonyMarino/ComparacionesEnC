#define USING_OOC

#include <ooc/Object.h>
#include <ooc/type/type.h>
#include <ooc/type/stdType.h>
#include <ooc/reflect/Field.h>
#include <ooc/reflect/Method.h>
#include <ooc/reflect/ReflectMethods.h>
#include <ooc/reflect/ReflectFields.h>
#include <string.h>

#include "ClassTest.h"

#include Implementation

#define ReflectTest_PRIVATE_DEF \
        private(ClassTest, obj)

#include "ReflectTest.h"

/*
 * Static Type Signatures
 */

static const char *types_str[] = {
  "no_type", 
  "const int",
  "unsigned const int",
  "int *",
  "int **",
  "int *[]",
  "int (*)[]",
  "typedef test",
  "enum test",
  "union test",
  "const char *",
  /*   "const char * const", */ /* BUG ?? */
  "char const *",
  /*   "char const * const", */
  "(const int *a, int b, unsigned int n, size_t sz)",
  "(constDate obj)",
  "(constDate)",
  "(int *year,int *mon,int *day,int *hour,int *min,int *sec)",
  "(int year,int mon,int day,int hour,int min,int sec)",
  "(struct tm)",
  "(Date)",
  "(void)",
  "()",
};

static enum ooc_type_id types_ids[] = {
  ooc_type_typedef,
  ooc_type_int,
  ooc_type_unsigned_int,
  ooc_type_pointer,
  ooc_type_pointer,
  ooc_type_pointer,
  ooc_type_pointer,
  ooc_type_typedef,
  ooc_type_enum,
  ooc_type_union,
  ooc_type_pointer,
  /*   ooc_type_pointer, */
  ooc_type_pointer,
  /*   ooc_type_pointer, */
  ooc_type_pointer, ooc_type_int, ooc_type_unsigned_int, ooc_type_unsigned_int,
  ooc_type_pointer,
  ooc_type_pointer,
  ooc_type_pointer, ooc_type_pointer, ooc_type_pointer, 
                    ooc_type_pointer, ooc_type_pointer, ooc_type_pointer,
  ooc_type_int, ooc_type_int, ooc_type_int, 
                ooc_type_int, ooc_type_int, ooc_type_int,
  ooc_type_struct,
  ooc_type_pointer,
  ooc_type_void,
  ooc_type_not_scan
};

static const char *types_scan_str[] = {
  "?",
  "int const",
  "unsigned int const",
  "int *",
  "int **",
  "int **",
  "int **",
  "?",
  "enum ?",
  "union ?",
  "char const*",
  /*   "char const*const", */
  "char const*",
  /*   "char const*const", */
  "int const*", "int", "unsigned int", "unsigned int",
  "constObject",
  "constObject",
  "int *", "int *", "int *", "int *", "int *", "int *",
  "int", "int", "int", "int", "int", "int",
  "struct ?",
  "Object",
  "void",
  "not_scan const"
};

/*
 * Macros
 */

#define TEST_TYPEAT(obj, idx, val, func, ooctype)		\
{								\
  constField fld = call1(cls, newFieldAt, idx);			\
  constType type = call0(fld, getType);				\
								\
  ooc_testAssert(ooc_typeDecode(type->type) == ooctype);	\
  ooc_testAssert(val ==  call1(fld, func, (Object)obj));	\
								\
  delete(fld);							\
}

#define TEST_TYPEBYID(obj, id, val, func, ooctype)		\
{								\
  constField fld = call1(cls, newField, id);			\
  constType type = call0(fld, getType);				\
								\
  ooc_testAssert(ooc_typeDecode(type->type) == ooctype);	\
  ooc_testAssert(val ==  call1(fld, func, (Object)obj));	\
								\
  delete(fld);							\
}

/*
 * Tests
 */

method0(Object, testTypes)
{
  size_t i;
  size_t n = 0;

  (void)self;

  for (i = 0; i < OOC_ARRLEN(types_str); i++) {
    const char *sig = types_str[i];
    int c;

    if (*sig == '(')
      ++sig;

    for (c = 1; *sig; c++) {
      char str[256];
      const char *end;
      ooc_type type = ooc_typeEncodeFromStr(sig, &end);

      ooc_testAssert(ooc_typeDecode(type) == types_ids[n]);

      ooc_typeDecodeToStr(type, str, sizeof(str)-1);
      ooc_testAssert(!strcmp(str, types_scan_str[n]));

      ++n;

      if (*end && *end != ')')
	sig = end+1;
      else 
	break;
    }
  }

  return 0;
}

method0(Object, testFieldAccess)
{
  Class cls = (Class)Class(ClassTest);

  ooc_testAssert(call0(cls, fieldCnt) == 7);

  /* init object val */
  self->obj->i = 5;
  self->obj->d = 10.10;
  self->obj->f = 20.20;
  self->obj->b = true;
  self->obj->c = 'O';
    
  /* by id */
  TEST_TYPEAT(self->obj, 0, self->obj->i, getInt , ooc_type_int   );
  TEST_TYPEAT(self->obj, 1, self->obj->d, getDbl , ooc_type_double);
  TEST_TYPEAT(self->obj, 2, self->obj->f, getFlt , ooc_type_float );
  TEST_TYPEAT(self->obj, 3, self->obj->b, getBool, ooc_type_bool  );
  TEST_TYPEAT(self->obj, 4, self->obj->c, getChr , ooc_type_char  );
    
  /* by name */
  TEST_TYPEBYID(self->obj, "i", self->obj->i, getInt , ooc_type_int   );
  TEST_TYPEBYID(self->obj, "d", self->obj->d, getDbl , ooc_type_double);
  TEST_TYPEBYID(self->obj, "f", self->obj->f, getFlt , ooc_type_float );
  TEST_TYPEBYID(self->obj, "b", self->obj->b, getBool, ooc_type_bool  );
  TEST_TYPEBYID(self->obj, "c", self->obj->c, getChr , ooc_type_char  );

  delete(self->obj);

  return 0;
}

method0(Object, testFieldAccessArray)
{
  Class cls = (Class)Class(ClassTest);
  constField fld = call1(cls, newField, "array");
  TypedArrayPtr ret;
  size_t i;

  ooc_testAssert(call0(fld, getCnt) == 10);
  ooc_testAssert(ooc_typeDecode(call0(fld, getType)->type)==ooc_type_pointer);
  
  ret = (TypedArrayPtr)call1(fld, get, (Object)self->obj);		
  ooc_testAssert(ret->cnt == 10);
  for (i = 0; i < ret->cnt; i++)
    ooc_testAssert(self->obj->array[i] == *((int*)ret->ptr + i));

  autorelease(ret);

  delete(fld);

  return 0;
}

method0(Object, testMethods)
{
  Class cls = (Class)Class(ClassTest);
  constType   type;
  constMethod mthd;

  (void)self;
  
  ooc_testAssert(call0(cls, methodCnt) == 5);
  
  {
    mthd = call1(cls, newMethodAt, 0);
    ooc_testAssert(call0(mthd, getParamCnt) == 2);
    
    type = call0(mthd, getRtnType);
    ooc_testAssert(ooc_typeIsObject(type->type, 0));
    
    type = call1(mthd, getParamType, 0);
    ooc_testAssert(ooc_typeIsObject(type->type, 0));
    
    type = call1(mthd, getParamType, 1);
    ooc_testAssert(ooc_typeIsObject(type->type, 0));
    
    delete(mthd);
  }
  {
    mthd = call1(cls, newMethodAt, 1);
    ooc_testAssert(call0(mthd, getParamCnt) == 2);

    type = call0(mthd, getRtnType);
    ooc_testAssert(ooc_typeDecode(type->type) == ooc_type_int);
  
    type = call1(mthd, getParamType, 0);
    ooc_testAssert(ooc_typeIsObject(type->type, 0));
    type = call1(mthd, getParamType, 1);
    ooc_testAssert(ooc_typeDecode(type->type) == ooc_type_int);

    delete(mthd);
  }
  {
    mthd = call1(cls, newMethodAt, 2);
    ooc_testAssert(call0(mthd, getParamCnt) == 2);

    type = call0(mthd, getRtnType);
    ooc_testAssert(ooc_typeDecode(type->type) == ooc_type_double);
  
    type = call1(mthd, getParamType, 0);
    ooc_testAssert(ooc_typeIsObject(type->type, 0));
    type = call1(mthd, getParamType, 1);
    ooc_testAssert(ooc_typeDecode(type->type) == ooc_type_double);

    delete(mthd);
  }
  {
    mthd = call1(cls, newMethodAt, 3);
    ooc_testAssert(call0(mthd, getParamCnt) == 2);

    type = call0(mthd, getRtnType);
    ooc_testAssert(ooc_typeDecode(type->type) == ooc_type_complex);
  
    type = call1(mthd, getParamType, 0);
    ooc_testAssert(ooc_typeIsObject(type->type, 0));
    type = call1(mthd, getParamType, 1);
    ooc_testAssert(ooc_typeDecode(type->type) == ooc_type_complex);
    
    delete(mthd);
  }
  {
    mthd = call1(cls, newMethodAt, 4);
    ooc_testAssert(call0(mthd, getParamCnt) == 1);

    type = call0(mthd, getRtnType);
    ooc_testAssert(ooc_typeDecode(type->type) == ooc_type_int);
  
    type = call1(mthd, getParamType, 0);
    ooc_testAssert(ooc_typeDecode(type->type) == ooc_type_int);

    delete(mthd);
  }

  return 0;
}

method0(Object, testInvoke)
{
  Class cls = (Class)Class(ClassTest);
  constMethod mthd = call1(cls, newMethodAt, 0);
  Object args[2];

  args[0] = (Object)self->obj;
  args[1] = (Object)self->obj;
  call1(mthd, invoke, args);

  ooc_testAssert(self->obj->data_mth1 == (Object)self->obj);

  delete(mthd);

  return 0;
}

#ifdef OOC_USE_FFI
method0(Object, testInvokeFFI)
{
  Class cls = (Class)Class(ClassTest);
  constMethod mthd;
  Object args[2];
  
  {
    Integer i = new(Integer);
    Integer ret;

    mthd = call1(cls, newMethodAt, 1);
    
    i->val  = 5;
    args[0] = (Object)self->obj;
    args[1] = (Object)i;
    ret = (Integer)call1(mthd, invoke, args);
    ooc_testAssert(ret->val == 2*i->val);
    
    autorelease(ret);
    
    delete(mthd);
    delete(i);
  }
  { 
    Double d = new(Double);
    Double ret;
    
    mthd = call1(cls, newMethodAt, 2);

    d->val  = 5.56;
    args[0] = (Object)self->obj;
    args[1] = (Object)d;
    ret = (Double)call1(mthd, invoke, args);
    ooc_testAssert(ret->val == 2*d->val);
    
    autorelease(ret);
    
    delete(mthd);
    delete(d);
  }  
  { 
    Complex c = new(Complex);
    Complex ret;
    
    mthd = call1(cls, newMethodAt, 3);

    ooc_creal(c->val) = 1.0;
    ooc_cimag(c->val) = 2.0;
    args[0] = (Object)self->obj;
    args[1] = (Object)c;
    ret = (Complex)call1(mthd, invoke, args);
    ooc_testAssert(ooc_creal(ret->val) == ooc_creal(c->val) &&
		   ooc_cimag(ret->val) == -ooc_cimag(c->val));
    
    autorelease(ret);
    
    delete(mthd);
    delete(c);
  }  
  { 
    Integer i = new(Integer);
    Integer ret;
    
    mthd = call1(cls, newMethodAt, 4);

    i->val = 10;
    args[0] = (Object)i;
    ret = (Integer)call1(mthd, invoke, args);
    ooc_testAssert(2*i->val == r->val);
    
    autorelease(ret);
    
    delete(mthd);
    delete(i);
  }  

  return 0;
}
#else
method0(Object, testInvokeFFI)
{
  (void)self;

  return 0;
}
#endif

/*
 * Fixture
 */

method0(void, setup)
{
  self->obj = new(ClassTest);
}

method0(void, cleanup)
{
  delete(self->obj);
}

/*
 * Class Methods
 */

staticMethod0(void, initialize)
{
  override(setup  );
  override(cleanup);

  override(testTypes           );
  override(testFieldAccess     );
  override(testFieldAccessArray);
  override(testMethods         );
  override(testInvoke          );
  override(testInvokeFFI       );
}

#include End

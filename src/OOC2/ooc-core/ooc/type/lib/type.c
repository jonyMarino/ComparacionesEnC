/*
 *******************************
 * Type identification implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: type.c,v 1.5 2005/11/17 10:01:35 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#define USING_OOC

#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <ooc/Object.h>
#include <ooc/assert.h>
#include <ooc/type/type.h>
#include <ooc/type/llong.h>
#include <ooc/type/complex.h>
#include <ooc/ex/ExBadArgument.h>

#if OOC_ISO_C >= OOC_ISO_C95
#include <wchar.h>
#endif

#if OOC_ISO_C >= OOC_ISO_C99
#include <stdint.h>
#endif

/*
Types letters:
  see also <ooc/type/type.h>

             ABCDEFGHIJKLMNOPQRSTUVWXYZ ?.
  lowercase  .xxx.x.xx..x..x.x....x..xx
  uppercase  ..xxx..xx..x....x.x.x....x

Types code:
  unsigned long -> min 32 bits -> min 12 pointer/array/function levels,
  see C99-5.2.4.1, Translation limits

   TTTTTTTC[PCPCPCPCPC..]

   TTTTTTT = type specifier (7 bits)
   C = 0 -> no const
   C = 1 -> const
   P = 0 -> T* or T[]
   P = 1 -> (*)
*/

#define MAX_ID           128
#define MAX_INDIRECTION  ((sizeof(unsigned long)*CHAR_BIT-8)/2)
#define CONST_CAST(tid)  ((tid) & (ULONG_MAX-1))
#define MK_TYPE(type)    OOC_STR(type), sizeof(OOC_STR(type))-1

struct specifier {
  const char *str;
  size_t   length;
  const char *in ;
  const char *out;
};

struct qualifier {
  const char *str;
  size_t   length;
  bool   is_const;
};

struct id_info {
  char        id;
  const char *str;
  size_t      length;
  size_t      size;
};

static struct specifier decl_specifier[] = {
  /*
   * Qualifiers
   */

  { MK_TYPE(auto)                    , 0 , 0 },
  { MK_TYPE(const)                   , 0 , ""},
  { MK_TYPE(extern)                  , 0 , 0 },
  { MK_TYPE(inline)                  , 0 , 0 }, /* C99 */
  { MK_TYPE(register)                , 0 , 0 },
  { MK_TYPE(restrict)                , 0 , 0 }, /* C99 */
  { MK_TYPE(static)                  , 0 , 0 },
  { MK_TYPE(typedef)                 , 0 , 0 },
  { MK_TYPE(volatile)                , 0 , 0 },

  /*
   * Aggregates
   */

  { MK_TYPE(enum)                    , "^", "E" },
  { MK_TYPE(struct)                  , "^", "S" },
  { MK_TYPE(union)                   , "^", "U" },

  /*
   * OOC aliases (+void)
   */

  { MK_TYPE(void)                    , "^", "v" },
  { MK_TYPE(ooc_void)                , "^", "v" },
  { MK_TYPE(ooc_llong)               , "^", "q" },
  { MK_TYPE(ooc_ullong)              , "^", "Q" },
  { MK_TYPE(ooc_complex)             , "^", "z" },

  { MK_TYPE(wchar_t)                 , "^", 
#ifdef WCHAR_MIN
    sizeof(wchar_t) == sizeof(char) ? (WCHAR_MIN ? "c" : "C") :
   (sizeof(wchar_t) == sizeof(short)? (WCHAR_MIN ? "h" : "H") :
   (sizeof(wchar_t) == sizeof(int)  ? (WCHAR_MIN ? "i" : "I") :
   (sizeof(wchar_t) == sizeof(long) ? (WCHAR_MIN ? "l" : "L") : "?")))},
#else
    sizeof(wchar_t) == sizeof(char) ? ( CHAR_MIN ? "c" : "C") :
   (sizeof(wchar_t) == sizeof(short)? ( CHAR_MIN ? "h" : "H") :
   (sizeof(wchar_t) == sizeof(int)  ? ( CHAR_MIN ? "i" : "I") :
   (sizeof(wchar_t) == sizeof(long) ? ( CHAR_MIN ? "l" : "L") : "?")))},
#endif

  { MK_TYPE(size_t)                  , "^",
    sizeof(size_t) == sizeof(int) ? "I" :
   (sizeof(size_t) == sizeof(long)? "L" :
   (sizeof(size_t) == sizeof(ooc_llong) ? "Q" : "?"))},

  { MK_TYPE(time_t)                  , "^", 
    sizeof(time_t) == sizeof(int) ? "I" :
   (sizeof(time_t) == sizeof(long)? "L" :
   (sizeof(time_t) == sizeof(ooc_llong) ? "Q" : "?"))},

  /*
   * Integral types
   */

  { MK_TYPE(_Bool)                   , "^", "b" },
  { MK_TYPE(bool)                    , "^", "b" },

  { MK_TYPE(char)                    , "^iI", CHAR_MIN ? "ccC" : "CcC" },
  { MK_TYPE(short)                   , "^iI"      , "hhH" },
  { MK_TYPE(int)                     , "^iIhHlLqQ", "iiIhHlLqQ" },
  { MK_TYPE(long)                    , "^iIlL"    , "llLqQ" },

  { MK_TYPE(signed)                  , "^", "i" },
  { MK_TYPE(unsigned)                , "^", "I" },

    /* Exact-size integral types aliases */

#ifdef INT8_MAX
  { MK_TYPE(int8_t)                  , "^",
    sizeof(int8_t) == sizeof(char) ? "c" : "?"},
#endif

#ifdef INT16_MAX
  { MK_TYPE(int16_t)                 , "^",
    sizeof(int16_t) == sizeof(short)? "h" :
   (sizeof(int16_t) == sizeof(int)  ? "i" : "?")},
#endif

#ifdef INT32_MAX
  { MK_TYPE(int32_t)                 , "^",
    sizeof(int32_t) == sizeof(long) ? "l" :
   (sizeof(int32_t) == sizeof(int)  ? "i" :
   (sizeof(int32_t) == sizeof(short)? "h" : "?"))},
#endif

#ifdef INT64_MAX
  { MK_TYPE(int64_t)                 , "^",
    sizeof(int64_t) == sizeof(long)     ? "l" :
   (sizeof(int64_t) == sizeof(ooc_llong)? "q" : "?")},
#endif

#ifdef UINT8_MAX
  { MK_TYPE(uint8_t)                 , "^",
    sizeof(uint8_t) == sizeof(char) ? "C" : "?"},
#endif

#ifdef UINT16_MAX
  { MK_TYPE(uint16_t)                , "^",
    sizeof(uint16_t) == sizeof(short)? "H" :
   (sizeof(uint16_t) == sizeof(int)  ? "I" : "?")},
#endif

#ifdef UINT32_MAX
  { MK_TYPE(uint32_t)                , "^",
    sizeof(uint32_t) == sizeof(long) ? "L" :
   (sizeof(uint32_t) == sizeof(int)  ? "I" :
   (sizeof(uint32_t) == sizeof(short)? "H" : "?"))},
#endif

#ifdef UINT64_MAX
  { MK_TYPE(uint64_t)                , "^",
    sizeof(uint64_t) == sizeof(long)      ? "L" :
   (sizeof(uint64_t) == sizeof(ooc_ullong)? "Q" : "?")},
#endif

    /* Least-size integral types aliases */

#ifdef INT_LEAST8_MAX
  { MK_TYPE(int_least8_t)            , "^",
    sizeof(int_least8_t) == sizeof(char) ? "c" :
   (sizeof(int_least8_t) == sizeof(short)? "h" :
   (sizeof(int_least8_t) == sizeof(int)  ? "i" : "?"))},
#endif

#ifdef INT_LEAST16_MAX
  { MK_TYPE(int_least16_t)           , "^",
    sizeof(int_least16_t) == sizeof(short)? "h" :
   (sizeof(int_least16_t) == sizeof(int)  ? "i" : "?")},
#endif

#ifdef INT_LEAST32_MAX
  { MK_TYPE(int_least32_t)           , "^",
    sizeof(int_least32_t) == sizeof(long) ? "l" :
   (sizeof(int_least32_t) == sizeof(int)  ? "i" :
   (sizeof(int_least32_t) == sizeof(short)? "h" : "?"))},
#endif

#ifdef INT_LEAST64_MAX
  { MK_TYPE(int_least64_t)           , "^",
    sizeof(int_least64_t) == sizeof(long)     ? "l" :
   (sizeof(int_least64_t) == sizeof(ooc_llong)? "q" : "?")},
#endif

#ifdef UINT_LEAST8_MAX
  { MK_TYPE(uint_least8_t)           , "^",
    sizeof(uint_least8_t) == sizeof(char) ? "C" :
   (sizeof(uint_least8_t) == sizeof(short)? "H" :
   (sizeof(uint_least8_t) == sizeof(int)  ? "I" : "?"))},
#endif

#ifdef UINT_LEAST16_MAX
  { MK_TYPE(uint_least16_t)          , "^",
    sizeof(uint_least16_t) == sizeof(short)? "H" :
   (sizeof(uint_least16_t) == sizeof(int)  ? "I" : "?")},
#endif

#ifdef UINT_LEAST32_MAX
  { MK_TYPE(uint_least32_t)          , "^",
    sizeof(uint_least32_t) == sizeof(long) ? "L" :
   (sizeof(uint_least32_t) == sizeof(int)  ? "I" :
   (sizeof(uint_least32_t) == sizeof(short)? "H" : "?"))},
#endif

#ifdef UINT_LEAST64_MAX
  { MK_TYPE(uint_least64_t)          , "^",
    sizeof(uint_least64_t) == sizeof(long)      ? "L" :
   (sizeof(uint_least64_t) == sizeof(ooc_ullong)? "Q" : "?")},
#endif

    /* Fast-size integral types aliases */

#ifdef INT_FAST8_MAX
  { MK_TYPE(int_fast8_t)             , "^",
    sizeof(int_fast8_t) == sizeof(char) ? "c" :
   (sizeof(int_fast8_t) == sizeof(short)? "h" :
   (sizeof(int_fast8_t) == sizeof(int)  ? "i" : "?"))},
#endif

#ifdef INT_FAST16_MAX
  { MK_TYPE(int_fast16_t)            , "^",
    sizeof(int_fast16_t) == sizeof(short)? "h" :
   (sizeof(int_fast16_t) == sizeof(int)  ? "i" : "?")},
#endif

#ifdef INT_FAST32_MAX
  { MK_TYPE(int_fast32_t)            , "^",
    sizeof(int_fast32_t) == sizeof(long) ? "l" :
   (sizeof(int_fast32_t) == sizeof(int)  ? "i" :
   (sizeof(int_fast32_t) == sizeof(short)? "h" : "?"))},
#endif

#ifdef INT_FAST64_MAX
  { MK_TYPE(int_fast64_t)            , "^",
    sizeof(int_fast64_t) == sizeof(long)     ? "l" :
   (sizeof(int_fast64_t) == sizeof(ooc_llong)? "q" : "?")},
#endif

#ifdef UINT_FAST8_MAX
  { MK_TYPE(uint_fast8_t)            , "^",
    sizeof(uint_fast8_t) == sizeof(char) ? "C" :
   (sizeof(uint_fast8_t) == sizeof(short)? "H" :
   (sizeof(uint_fast8_t) == sizeof(int)  ? "I" : "?"))},
#endif

#ifdef UINT_FAST16_MAX
  { MK_TYPE(uint_fast16_t)           , "^",
    sizeof(uint_fast16_t) == sizeof(short)? "H" :
   (sizeof(uint_fast16_t) == sizeof(int)  ? "I" : "?")},
#endif

#ifdef UINT_FAST32_MAX
  { MK_TYPE(uint_fast32_t)           , "^",
    sizeof(uint_fast32_t) == sizeof(long) ? "L" :
   (sizeof(uint_fast32_t) == sizeof(int)  ? "I" :
   (sizeof(uint_fast32_t) == sizeof(short)? "H" : "?"))},
#endif

#ifdef UINT_FAST64_MAX
  { MK_TYPE(uint_fast64_t)           , "^",
    sizeof(uint_fast64_t) == sizeof(long)      ? "L" :
   (sizeof(uint_fast64_t) == sizeof(ooc_ullong)? "Q" : "?")},
#endif

    /* Maximum-size integral types aliases */

#ifdef INTMAX_MAX
  { MK_TYPE(intmax_t)                , "^",
    sizeof(intmax_t) == sizeof(long)     ? "l" :
   (sizeof(intmax_t) == sizeof(ooc_llong)? "q" : "?")},
#endif

#ifdef UINTMAX_MAX
  { MK_TYPE(uintmax_t)               , "^",
    sizeof(uintmax_t) == sizeof(long)      ? "l" :
   (sizeof(uintmax_t) == sizeof(ooc_ullong)? "q" : "?")},
#endif

    /* Common integral types aliases */

  { MK_TYPE(char_t)                  , "^",  "c" },
  { MK_TYPE(short_t)                 , "^",  "h" },
  { MK_TYPE(int_t)                   , "^",  "i" },
  { MK_TYPE(long_t)                  , "^",  "l" },
  { MK_TYPE(llong_t)                 , "^",  "q" },

  { MK_TYPE(uchar_t)                 , "^",  "C" },
  { MK_TYPE(ushort_t)                , "^",  "H" },
  { MK_TYPE(uint_t)                  , "^",  "I" },
  { MK_TYPE(ulong_t)                 , "^",  "L" },
  { MK_TYPE(ullong_t)                , "^",  "Q" },

  /*
   * Floating-point types
   */
  { MK_TYPE(float)                   , "^"  , "f"   },
  { MK_TYPE(double)                  , "^l" , "dD"  },

  { MK_TYPE(complex)                 , "fdD", "xzZ" },
  { MK_TYPE(imaginary)               , "fdD", "XyY" },
  { MK_TYPE(_Complex)                , "fdD", "xzZ" },
  { MK_TYPE(_Imaginary)              , "fdD", "XyY" },

    /* Common floating-point types aliases */

#if   FLT_EVAL_METHOD == 0
  { MK_TYPE(float_t)                 , "^",  "f" },
  { MK_TYPE(double_t)                , "^",  "d" },
#elif FLT_EVAL_METHOD == 1
  { MK_TYPE(float_t)                 , "^",  "d" },
  { MK_TYPE(double_t)                , "^",  "d" },
#elif FLT_EVAL_METHOD == 2
  { MK_TYPE(float_t)                 , "^",  "D" },
  { MK_TYPE(double_t)                , "^",  "D" },
#else
  { MK_TYPE(float_t)                 , "^",  "?" },
  { MK_TYPE(double_t)                , "^",  "?" },
#endif
};

static struct qualifier type_qualifier[] = {
  { MK_TYPE(const)    , true  },
  { MK_TYPE(restrict) , false }, /* C99, pointer only */
  { MK_TYPE(static)   , false }, /* C99, parameter array only */
  { MK_TYPE(volatile) , false },
};

static struct id_info id_info[] = {
{ ooc_type_not_scan             , MK_TYPE(not_scan)              , 0                     },

{ ooc_type_invalid              , MK_TYPE(invalid_type)          , 0                     },

{ ooc_type_void                 , MK_TYPE(void)                  , 0                     },

{ ooc_type_bool                 , MK_TYPE(bool)                  , sizeof(bool)          },
#if CHAR_MIN
{ ooc_type_char                 , MK_TYPE(char)                  , sizeof(char)          },
#else
{ ooc_type_char                 , MK_TYPE(signed char)           , sizeof(signed char)   },
#endif
{ ooc_type_unsigned_char        , MK_TYPE(unsigned char)         , sizeof(unsigned char) },
{ ooc_type_short                , MK_TYPE(short)                 , sizeof(short)         },
{ ooc_type_unsigned_short       , MK_TYPE(unsigned short)        , sizeof(unsigned short)},
{ ooc_type_int                  , MK_TYPE(int)                   , sizeof(int)           },
{ ooc_type_unsigned_int         , MK_TYPE(unsigned int)          , sizeof(unsigned int)  },
{ ooc_type_long                 , MK_TYPE(long)                  , sizeof(long)          },
{ ooc_type_unsigned_long        , MK_TYPE(unsigned long)         , sizeof(unsigned long) },
{ ooc_type_long_long            , MK_TYPE(long long)             , sizeof(ooc_llong)     },
{ ooc_type_unsigned_long_long   , MK_TYPE(unsigned long long)    , sizeof(ooc_ullong)    },
{ ooc_type_float                , MK_TYPE(float)                 , sizeof(float)         },
{ ooc_type_double               , MK_TYPE(double)                , sizeof(double)        },
{ ooc_type_long_double          , MK_TYPE(long double)           , sizeof(long double)   },
{ ooc_type_complex              , MK_TYPE(ooc_complex)           , sizeof(ooc_complex)   },
{ ooc_type_float_complex        , MK_TYPE(float _Complex)        , 0                     },
{ ooc_type_double_complex       , MK_TYPE(double _Complex)       , sizeof(ooc_complex)   },
{ ooc_type_long_double_complex  , MK_TYPE(long double _Complex)  , 0                     },
{ ooc_type_float_imaginary      , MK_TYPE(float _Imaginary)      , sizeof(float)         },
{ ooc_type_double_imaginary     , MK_TYPE(double _Imaginary)     , sizeof(double)        },
{ ooc_type_long_double_imaginary, MK_TYPE(long double _Imaginary), sizeof(long double)   },


{ ooc_type_object               , MK_TYPE(Object)                , 0                     },

{ ooc_type_enum                 , MK_TYPE(enum ?)                , 0                     },
{ ooc_type_struct               , MK_TYPE(struct ?)              , 0                     },
{ ooc_type_union                , MK_TYPE(union ?)               , 0                     },
{ ooc_type_typedef              , MK_TYPE(?)                     , 0                     },

{ ooc_type_pointer              , MK_TYPE(*)                     , sizeof(void*)         },
{ ooc_type_function             , MK_TYPE(())                    , 0                     },

{ ooc_type_va_arg               , MK_TYPE(...)                   , 0                     },
};

static unsigned char id_index[MAX_ID];

static unsigned long      Object_tid;
static unsigned long constObject_tid;

static bool module_ok = false;

static int
findQualifier(const void *token_, const void *qualifier_)
{
  const char *token = token_;
  const struct qualifier *qualifier = qualifier_;
  int c;

  c = strncmp(token, qualifier->str, qualifier->length);

  if (c)
    return c;
    
  c = token[qualifier->length];
    
  return isalnum(c) || c == '_' ? c : 0;
}

static int
findSpecifier(const void *token_, const void *specifier_)
{
  const char *token = token_;
  const struct specifier *specifier = specifier_;
  int c;

  c = strncmp(token, specifier->str, specifier->length);
  
  if (c)
    return c;

  c = token[specifier->length];

  return isalnum(c) || c == '_' ? c : 0;
}

static int
compareSpecifier(const void *specifier1_, const void *specifier2_)
{
  const struct specifier *specifier1 = specifier1_;
  const struct specifier *specifier2 = specifier2_;

  return strcmp(specifier1->str, specifier2->str);
}

static unsigned long
setId(unsigned long tid, int id, bool is_const)
{
  if (id)
    switch (id) {
    case '*':
    case '[':
      tid <<= 2;
      break;
    
    case '(':
      tid <<= 2;
      tid |= 2;
      break;
    
    default:
      tid = (id << 1) & 0xFF;
    }
  
  return is_const ? (tid | 1) : CONST_CAST(tid);
}

static unsigned long
shiftId(unsigned long tid, int *id, bool *is_const)
{
  if (is_const)
    *is_const = tid & 1;

  if (tid > 0xFF) {
    if (id)
      *id = tid & 2 ? '(' : '*';
    return tid >> 2;
  } else {
    if (id)
      *id = tid >> 1;
    return 0;
  }
}

static void
init_module(void)
{
  size_t n, i;

  ooc_assert(OOC_ARRLEN(id_info) <= MAX_ID);

  /*
  for (n=0; n < OOC_ARRLEN(decl_specifier); n++)
    if (decl_specifier[n].in &&
        strlen(decl_specifier[n].in) != strlen(decl_specifier[n].out))
      ooc_error("%s(%d): incorrect transition state %s[%s] doesn't match "
		"[%s]", __FILE__, __LINE__, decl_specifier[n].str,
		decl_specifier[n].in, decl_specifier[n].out);
  */

  qsort(decl_specifier, OOC_ARRLEN(decl_specifier), sizeof *decl_specifier,
	compareSpecifier);

  /*
  for (n=1; n < OOC_ARRLEN(decl_specifier); n++)
    if (!strcmp(decl_specifier[n].str, decl_specifier[n-1].str))
      ooc_error("%s(%d): duplicated type %s", __FILE__, __LINE__,
                decl_specifier[n].str);
  */

  for (i = 0; i < OOC_ARRLEN(id_info); i++)
    if (id_info[i].id == ooc_type_typedef)
      break;
      
  for (n = 0; n < OOC_ARRLEN(id_index); n++)
    id_index[n] = i;

  for (n = 0; n < OOC_ARRLEN(id_info); n++)
    id_index[id_info[n].id & (MAX_ID-1)] = n;
  
  Object_tid      = setId(setId(0,'o',false),'*',false);
  constObject_tid = setId(setId(0,'o',true ),'*',false);

  module_ok = true;
}

static const char*
skipSpc(const char *str)
{
  int c;
  
  while((c = *str) && isspace(c))
    ++str;
  
  return str;
}

static const char*
skipToken(const char *str)
{
  int c;

  /*
   * parses C token
   */
  if ((c = *str) && (isalpha(c) || c == '_'))
    ++str;
  while((c = *str) && (isalnum(c) || c == '_'))
    ++str;
  
  return str;
}

static const char*
skipScope(const char *str, char open, char close)
{
  /*
   * parses scope from open to close: [...], {...}, (...)
   */
  if (*str == open) {
    int lvl = 1;
    
    for (++str; *str && lvl; ++str) {
      if (*str == open)
	++lvl;
      else if (*str == close)
	--lvl;
    }
  }
  
  return str;
}

static unsigned long
getObjectSpecifier(const char *str, const char **end)
{
  unsigned long tid = Object_tid;
  int c;

  /*
   * parses ("const"|"class")?[A-Z]+[a-z][A-Za-z0-9]*
   */

  c = *str;

  if (!isupper(c)) {

    /* ("const"|"class")? */
    if (!strncmp(str, "const", sizeof("const")-1) ||
	!strncmp(str, "class", sizeof("class")-1)) {
      tid = constObject_tid;
      str += 5;
    }
    
    if (!(c = *str) || !isupper(c))
      return 0;
  }

  /* [A-Z]+ */
  for (++str; (c = *str) && isupper(c); ++str)
    ;

  /* [a-z] */
  if (!((c = *str++) && islower(c)))
    return 0;

  /* [A-Za-z0-9]* */
  while((c = *str) && isalnum(c))
    ++str;

  if (end)
    *end = str;

  return tid;
}

static unsigned long
getDeclSpecifier(const char *str, const char **end)
{
  bool is_const = false;
  unsigned long tid = 0;
  int id = '^';
  
  while (1) {
    struct specifier *found;
    int c;

    str = skipSpc(str);

    if (!(c = *str) || !(isalpha(c) || c == '_'))
      break;

    if (id == '^') {
      tid = getObjectSpecifier(str, &str);
      if (tid) {
	OOC_DBG(("\tobject\n"));
	id = '*';
	continue;
      }
    }

    found = bsearch(str, decl_specifier, OOC_ARRLEN(decl_specifier),
		    sizeof *decl_specifier, findSpecifier);

    if (found) {
      if (found->in) {
	const char *p = strchr(found->in, id);

	OOC_DBG(("\tspecifier %s", found->str));
	ooc_assert(p && "invalid state"); /* bad state ? */
	
	id = found->out[p - found->in];
	OOC_DBG((" '%c'\n", id));

	if (strchr("ESU", id)) { /* enum, struct, union tag */
	  str = skipSpc(str+found->length);
	  str = skipToken(str);
	  str = skipSpc(str);
	  str = skipScope(str, '{', '}');
	  continue;
	}

      } else {
	OOC_DBG(("\tqualifier %s\n", found->str));
	if (found->out)
	  is_const = true;
      }
      
      str += found->length;
      continue;
    }

    if (id == '^') {
      OOC_DBG(("\ttypedef name\n"));
      id = '?';
      str = skipToken(str);
      continue;
    }

    break;
  }

  if (end)
    *end = str;

  if (id == '^') {
    ooc_assert(!tid);
    
    if (is_const) 
      return -1; /* parse error */
    else
      return 0;  /* no specifier */
  }
  
  return setId(tid, tid ? 0 : id, is_const);
}

static bool
getTypeQualifier(const char *str, const char **end)
{
  struct qualifier *found;
  bool is_const = false;

  do {
    str = skipSpc(str);

    found = bsearch(str, type_qualifier, OOC_ARRLEN(type_qualifier),
		    sizeof *type_qualifier, findQualifier);
    if (found) {
      OOC_DBG(("\tqualifier %s\n", found->str));
      is_const |= found->is_const;
      str += found->length;
    }
  } while (found);
  
  if (end)
    *end = str;
  
  return is_const;
}

static unsigned long
getAbstractDeclarator(unsigned long tid, const char *str, const char **end)
{
  bool identifier  = false;
  size_t ind_level = tid > 0xFF;
  size_t par_level = 0;
  
  while(ind_level <= MAX_INDIRECTION) {
    str = skipSpc(str);
    
    switch (*str) {

    case '*':
      tid = setId(tid, '*', getTypeQualifier(str+1, &str));
      ++ind_level;
      OOC_DBG(("\tpointer (%d)\n", ind_level));
      continue;
      
    case '[':
      tid = setId(tid, '[', getTypeQualifier(str+1, 0));
      str = skipScope(str, '[', ']');
      ++ind_level;
      OOC_DBG(("\tarray (%d)\n", ind_level));
      continue;

    case '(': {
      const char *after;

      if (identifier && !par_level) {
	tid = setId(tid, '(', false);
	str = skipScope(str, '(', ')');
	++ind_level;
	OOC_DBG(("\tfunction (%d)\n", ind_level));
	continue;
      }
      
      after = skipSpc(skipScope(str, '(', ')'));
      
      if (*after == '(') {
	tid = setId(tid, '(', false);
	++ind_level;
	OOC_DBG(("\tfunction (%d)\n", ind_level));

      } else if (*after == '[') {
	do {
	  tid = setId(tid, '[', getTypeQualifier(after+1, 0));
	  after = skipSpc(skipScope(after, '[', ']'));
	  ++ind_level;
	  OOC_DBG(("\tarray (%d)\n", ind_level));
	} while(*after == '[' && ind_level <= MAX_INDIRECTION);
      }

      ++par_level;
      ++str;
      continue;
    }

    case ')':
      if (par_level) {
	--par_level;

	str = skipSpc(str+1);

	if (*str == '(')
	  str = skipScope(str, '(', ')');
	else if (*str == '[') {
	  do
	    str = skipSpc(skipScope(str, '[', ']'));
	  while(*str == '[');
	}
	continue;
      } /* continue to default */

    default: {
      int c;

      if (!(c = *str) || !(isalpha(c) || c == '_')) {
	if (end)
	  *end = str;
	return tid;
      }
      
      if (!identifier) {
	OOC_DBG(("\tidentifier\n"));
	str = skipToken(str);
	identifier = true;
	continue;
      }
    }}
    
    break;
  }
  
  if (end)
    *end = str;
  
  return -1;
}

static unsigned long
getVaArg(const char *str, const char **end)
{
  str = skipSpc(str);

  if (str[0] != '.' || str[1] != '.' || str[2] != '.')
    return 0;

  str = skipSpc(str+3);

  if (end)
    *end = str;

  if (*str != ')')
    return -1;

  OOC_DBG(("\t...\n"));

  return setId(0, '.', false);
}

/*
 * ooc_type Implementation
 */

ooc_type
ooc_typeEncodeFromStr(const char *str, const char **end)
{
  unsigned long tid;
  ooc_type type;
  
  if (!module_ok)
    init_module();
  
  ooc_assert(str);

  tid = getVaArg(str, &str);
  if (!tid) {
    tid = getDeclSpecifier(str, &str);
    if (tid && tid != (unsigned long)-1)
      tid = getAbstractDeclarator(tid, str, &str);
  }
  
  if (tid == (unsigned long)-1 || tid == 0)
    type.id = ooc_type_invalid; /* parse error return invalid type */
  else
    type.id = tid;
  
  if (end)
    *end = str;

  OOC_DBG(("\tclosure = '%c'\n", *str));

  return type;
}

int 
ooc_typeDecodeToStr(ooc_type type, char *str, size_t size)
{
  struct {
    char type;
    bool is_const;
  } ind_stack [MAX_INDIRECTION];
  
  unsigned long tid;
  int func_lvl, ind, id;
  bool is_const;
  size_t n;
  
  ooc_assert(str && size);

  *str = '\0';

  if (!type.id)
    return 0;

  if (!module_ok)
    init_module();
  
  ind = 0;
  func_lvl = 0;
  tid = type.id;

  while (tid) {
    tid = shiftId(tid, &id, &is_const);
    if (tid) {
      if (ind >= (int)MAX_INDIRECTION)
	throw(new(ExBadArgument));
      
      ind_stack[ind].type = id;
      ind_stack[ind].is_const = is_const;
      ++ind;
      if (id == '(')
	++func_lvl;
    }
  }

  n = 0;
  if (id == 'o') {
    if (is_const) {
      strncat(str, "constObject", size);
      n += 11;
    } else {
      strncat(str, "Object", size);
      n += 6;
    }
    is_const = ind_stack[--ind].is_const;
  } else {
    struct id_info *found = &id_info[id_index[id & (MAX_ID-1)]];

    strncat(str+n, found->str, size-n);
    n += found->length;
  }

  if (n < size) {
    if (is_const) {
      strncat(str+n, " const", size-n);
      n += 6;
    } else if (ind > 0)
      str[n++] = ' ';
  }

  while(n < size && --ind >= 0) {
    str[n++] = ind_stack[ind].type;
    if (ind_stack[ind].is_const) {
      strncat(str+n, "const", size-n);
      n += 5;
    }
  }

  while(n < size && --func_lvl >= 0) {
    strncat(str+n, ")()", size-n);
    n += 3;
  }

  if (n >= size)
    n = size - 1;

  str[n] = '\0';

  return n;
}

int ooc_typeSize(ooc_type type)
{
  int id;

  if (type.id > 0x3FF && (type.id & 8))
    return sizeof(ooc_function);
  
  if (type.id > 0xFF && (type.id & 2))
    return 0;

  if (type.id > 0xFF)
    return sizeof(void*);

  if (!module_ok)
    init_module();
  
  id = type.id >> 1;
  
  return id_info[id_index[id & (MAX_ID-1)]].size;
}

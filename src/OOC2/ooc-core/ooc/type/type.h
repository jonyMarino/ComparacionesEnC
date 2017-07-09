#ifndef OOC_TYPE_TYPE_T_H
#define OOC_TYPE_TYPE_T_H

/*
 *******************************
 * Type encoding interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: type.h,v 1.4 2005/12/14 18:35:06 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

typedef struct {
  unsigned long id;
} ooc_type;

/*
 * ooc_type Flat Type
 */

enum ooc_type_id { 
  ooc_type_not_scan              = 0, 
  ooc_type_invalid               = 1, 

  ooc_type_void                  = 'v',  /* Type specifier */
  ooc_type_bool                  = 'b',
  ooc_type_char                  = 'c',
  ooc_type_unsigned_char         = 'C',
  ooc_type_short                 = 'h',
  ooc_type_unsigned_short        = 'H',
  ooc_type_int                   = 'i',
  ooc_type_unsigned_int          = 'I',
  ooc_type_long                  = 'l',
  ooc_type_unsigned_long         = 'L',
  ooc_type_long_long             = 'q',
  ooc_type_unsigned_long_long    = 'Q',
  ooc_type_float                 = 'f',
  ooc_type_double                = 'd',
  ooc_type_long_double           = 'D',
  ooc_type_complex               = 'z',
  ooc_type_float_complex         = 'x',
  ooc_type_double_complex        = 'z',
  ooc_type_long_double_complex   = 'Z',
  ooc_type_float_imaginary       = 'X',
  ooc_type_double_imaginary      = 'y',
  ooc_type_long_double_imaginary = 'Y',

  ooc_type_object                = 'o',           
                              /* typename: 
			       * ("const"|"class")?([A-Z]+[a-z][A-Za-z0-9]*
			       * TODO: 2 states for Class initialization */

  ooc_type_enum                  = 'E',
  ooc_type_struct                = 'S',
  ooc_type_union                 = 'U',
  ooc_type_typedef               = '?',

  ooc_type_pointer               = '*',  /* Type qualifier */ 
  ooc_type_function              = '(',

  ooc_type_va_arg                = '.'
};

/* NOTE-USER:

Standard typedef

   standard aliases
   size_t (unsigned), time_t (unsigned), wchar_t (signed or unsigned)
   int8_t, int16_t, int32_t, int64_t,     (if CHAR_BIT == 8)
   uint8_t, uint16_t, uint32_t, uint64_t, (if CHAR_BIT == 8)
   int_least8_t, int_least16_t, int_least32_t, int_least64_t,
   uint_least8_t, uint_least16_t, uint_least32_t, uint_least64_t,
   int_fast8_t, int_fast16_t, int_fast32_t, int_fast64_t,
   uint_fast8_t, uint_fast16_t, uint_fast32_t, uint_fast64_t,
   intmax_t, uintmax_t
   are identified by their equivalent integral types.
   float_t, double_t
   are identified by their equivalent floating-point types.

   common aliases
   char_t, short_t, int_t, long_t, llong_t,
   uchar_t, ushort_t, uint_t, ulong_t, ullong_t
   are supported.

   OOC aliases
   ooc_void ('v')
   ooc_llong ('q'), ooc_ullong ('Q'),
   ooc_complex ('z')
   
   imaginary types (float|double|long double) imaginary, _Imaginary
   are identified by their equivalent floating-point types.
*/

/*
 * ooc_type Services
 */

ooc_type ooc_typeEncodeFromStr(const char *str, const char **end);
int      ooc_typeDecodeToStr  (ooc_type type, char *str, size_t size);
int      ooc_typeSize         (ooc_type type);

/*
 * Static inline implementation
 */

static inline
enum ooc_type_id
ooc_typeDecode(ooc_type type)
{  
  if (type.id > 0xFF)
    return type.id & 2 ? ooc_type_function : ooc_type_pointer;

  return type.id >> 1;
}

static inline 
ooc_type ooc_typeShift(ooc_type type)
{
  if (type.id > 0xFF)
    type.id >>= 2;
  else
    type.id = ooc_type_invalid;

  return type;
}

static inline
bool ooc_typeIsConst(ooc_type type)
{
  return type.id & 1;
}

static inline
bool ooc_typeIsValid(ooc_type type)
{
  return 
    type.id != ooc_type_not_scan &&
    type.id != ooc_type_invalid;
}

static inline
bool ooc_typeIsEncoded(ooc_type type)
{
  return type.id != ooc_type_not_scan;
}

static inline
bool ooc_typeIsPointer(ooc_type type, bool *is_pointed_const)
{
  if (type.id > 0xFF) {
    if (is_pointed_const)
      *is_pointed_const = (type.id >> 2) & 1;
    
    return !(type.id & 2);
  }
  
  return false;
}

static inline
bool ooc_typeIsObject(ooc_type type, bool *is_pointed_const)
{
  return
    (ooc_typeIsPointer(type, is_pointed_const) &&
     ooc_typeDecode(ooc_typeShift(type)) == ooc_type_object);
}

static inline
bool ooc_typeIsStr(ooc_type type, bool *is_pointed_const)
{
  return
    (ooc_typeIsPointer(type, is_pointed_const) &&
     ooc_typeDecode(ooc_typeShift(type)) == ooc_type_char);
}

#endif /* OOC_TYPE_TYPE_T_H */

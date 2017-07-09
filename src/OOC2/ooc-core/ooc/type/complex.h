#ifndef OOC_TYPE_COMPLEX_T_H
#define OOC_TYPE_COMPLEX_T_H

/*
 *******************************
 * complex type interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: complex.h,v 1.3 2005/11/15 18:37:12 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

typedef struct { double _[2]; } ooc_complex;

#define ooc_creal(z) ((z)._[0])
#define ooc_cimag(z) ((z)._[1])

#define ooc_complex(re,im) ooc_complex_mk(re,im)

/* NOTE-PORT: ooc_complex packed array portability
   - before using packed array of ooc_complex,
     check if ooc_complex_ispacked() is true
 */

#define ooc_complex_ispacked() \
        (sizeof(ooc_complex[2]) == sizeof(double [4]))

/*
 * -------------------------
 *  Inline implementation
 * -------------------------
 */

static inline
ooc_complex
ooc_complex_mk(double re, double im)
{
  ooc_complex z;
  
  ooc_creal(z) = re, ooc_cimag(z) = im;

  return z;
}

#endif /* OOC_TYPE_COMPLEX_T_H */

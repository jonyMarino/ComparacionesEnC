#ifndef OOC_UTILS_CTYPE_H
#define OOC_UTILS_CTYPE_H

/*
 *******************************
 * Union of C types (alignment constraint)
 * -----
 * Object Oriented C progamming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: ctype.h,v 1.3 2005/11/16 12:33:50 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#include <ooc/type/llong.h>
#include <ooc/type/complex.h>

union ooc_ctype {
  bool                    b;
  char                    c;
  short                   h;
  int                     i;
  long                    l;
  ooc_llong               ll;

  size_t                  s;
  
  float                   f;
  double                  d;
  long double             ld;
  
  ooc_complex             z;
  
  void                   *p;
  ooc_function            fp;
};

#endif

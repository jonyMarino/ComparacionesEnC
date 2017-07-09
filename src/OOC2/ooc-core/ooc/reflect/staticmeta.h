#ifndef OOC_REFLECT_STATICMETA_T_H
#define OOC_REFLECT_STATICMETA_T_H

/*
 *******************************
 * Static meta type
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: staticmeta.h,v 1.3 2005/11/16 12:33:50 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#include <ooc/type/type.h>

struct ooc_meta_mth { /* IA32: 16 bytes/method + name */
  const char           *name;
  ooc_type             *type;
  size_t                offset;
  unsigned char         param_obj;
  unsigned char         param_cnt;
};

struct ooc_meta_fld { /* IA32: 16 bytes/field + name */
  const char           *name;
  ooc_type              type;
  size_t                offset;
  unsigned short        elem_size;
  size_t                elem_cnt;
};

#endif /* OOC_REFLECT_STATICMETA_T_H */

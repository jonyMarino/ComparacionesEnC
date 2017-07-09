#ifndef OOC_TYPE_TUPLE_T_H
#define OOC_TYPE_TUPLE_T_H

/*
 *******************************
 * Object tuple type interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: tuple.h,v 1.2 2005/11/15 18:37:12 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

/* NOTE-USER: tuple member access
   tuple types are public: tup._0, tup._1, tup._2 must be used to access the
   first, second and third element (no getter)
 */

typedef struct { Object _0, _1;     } ooc_tuple2;
typedef struct { Object _0, _1, _2; } ooc_tuple3;

#define ooc_tuple2(a,b)				\
        ooc_tuple2_mk((Object)&(a)->_isa,	\
		      (Object)&(b)->_isa)

#define ooc_tuple3(a,b,c)			\
        ooc_tuple3_mk((Object)&(a)->_isa,	\
		      (Object)&(b)->_isa,	\
		      (Object)&(c)->_isa)

static inline
ooc_tuple2
ooc_tuple2_mk(Object _0, Object _1)
{
  ooc_tuple2 t;

  t._0 = _0, t._1 = _1;

  return t;
}

static inline
ooc_tuple3
ooc_tuple3_mk(Object _0, Object _1, Object _2)
{
  ooc_tuple3 t;

  t._0 = _0, t._1 = _1, t._2 = _2;

  return t;
}

#endif /* OOC_TYPE_TUPLE_T_H */

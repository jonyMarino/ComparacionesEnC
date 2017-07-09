#ifndef OOC_STDTYPE_H
#define OOC_STDTYPE_H

/*
 *******************************
 * Standard C types interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: stdType.h,v 1.1 2005/12/09 17:43:10 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#include <ooc/type/Bool.h>
#include <ooc/type/Char.h>
#include <ooc/type/Int.h>
#include <ooc/type/Long.h>
#include <ooc/type/LongLong.h>

#include <ooc/type/Float.h>
#include <ooc/type/Double.h>
#include <ooc/type/LongDouble.h>

#include <ooc/type/Complex.h>

#include <ooc/type/Pointer.h>             /* pointer                */
#include <ooc/type/AllocPtr.h>            /* alloc pointer          */
#include <ooc/type/ArrayPtr.h>            /* pointer to array       */
#include <ooc/type/AllocArrayPtr.h>       /* alloc pointer to array */

#include <ooc/type/TypedPtr.h>            /* typed pointer                */
#include <ooc/type/TypedAllocPtr.h>       /* typed alloc pointer          */
#include <ooc/type/TypedArrayPtr.h>       /* typed pointer to array       */
#include <ooc/type/TypedAllocArrayPtr.h>  /* typed alloc pointer to array */

#include <ooc/type/Function.h>            /* function pointer */

/* NOTE-USER: BasicType hierarchy

Object (A)
<- BasicType (A)
   <- Number (A)
      <- Integral (A)
         <- Bool
   	 <- Char
   	 <- Int
   	 <- Long
   	 <- LongLong
      <- Floating (A)
   	 <- Float
   	 <- Double
   	 <- LongDouble
   	 <- Complex

   <- Pointer [ptr, size]
      <- AllocPtr [free]
      <- ArrayPtr [cnt]
         <- AllocArrayPtr [free]

      <- TypedPtr [type]
         <- TypedAllocPtr [free]
         <- TypedArrayPtr [cnt]
            <- TypedAllocArrayPtr [free]

   <- Function

Example:
  - To handle objects returned by invoke:
    o if you       need it, use operator retain() + release()
    o if you don't need it, use operator autorelease()
*/

#endif /* OOC_STDTYPE_H */

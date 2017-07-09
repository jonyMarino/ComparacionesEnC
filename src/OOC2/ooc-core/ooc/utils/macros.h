#ifndef OOC_UTILS_MACROS_H
#define OOC_UTILS_MACROS_H

/*
 ******************************
 * Macros utilities
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: macros.h,v 1.1 2005/11/15 14:36:36 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

/*
 * -------------------------
 *  Bool cast (ensure 0 or 1)
 * -------------------------
 */

#define OOC_BOOL_CAST(v) (!!(v))

/*
 * -------------------------
 *  Multi-dimensional array indexing
 * -------------------------
 */

#define OOC_2D(x,y,nx)           ((y)*(nx) + (x))
#define OOC_3D(x,y,z,nx,ny)      (((z)*(ny) + (y) )*(nx) + (x))
#define OOC_4D(x,y,z,t,nx,ny,nz) ((((t)*(nz) + (z) )*(ny) + (y) )*(nx)+(x))

/*
 * -------------------------
 *  Variables
 * -------------------------
 */

#define OOC_SWAP(a,b,t) ((t)=(a),(a)=(b),(b)=(t))

/*
 * -------------------------
 *  Numbers
 * -------------------------
 */

#define OOC_SQR(a)       ((a)*(a))
#define OOC_CMP(a,b)     ((a)>(b) ? 1 : ((a)<(b) ? -1 : 0))

#define OOC_SIGN(a)      ((a)<0 ? -1 : 1)
#define OOC_ABS(a)       ((a)<0 ? -(a) : (a))

#define OOC_MIN(a,b)     ((a)<(b) ? (a) : (b))
#define OOC_MAX(a,b)     ((a)>(b) ? (a) : (b))
#define OOC_MIN3(a,b,c)  ((a)<(b) ? OOC_MIN((a),(c)) : OOC_MIN((b),(c)))
#define OOC_MAX3(a,b,c)  ((a)>(b) ? OOC_MAX((a),(c)) : OOC_MAX((b),(c)))

#define OOC_ISNAN(a)     ((a) != (a))         /*may fail: not standard*/

#define OOC_ISPOW2(a)    (OOC_CAL1(a) == (a)) /*may fail: zero+see Bits*/

#define OOC_SIGNF(a)     ((a)!=0.0 ? OOC_SIGN(a) : (1.0/(a)<0.0 ? -1 : 1))
#define OOC_EQSIGN(a,b)  (((a)<0) == ((b)<0))
#define OOC_EQSIGNF(a,b) (OOC_SIGNF(a) == OOC_SIGNF(b))

/*
 * -------------------------
 *  Bits manipulation
 *  (warning: only valid for Integral types using two's complement)
 * -------------------------
 */

#define OOC_CL1(a)  ((a) & (a)-1)/*clear the lowest 1 bit*/
#define OOC_CAL1(a) ((a) & -(a)) /*clear all bits except the lowest 1 bit*/

#define OOC_SL0(a)  ((a) | (a)+1) /*set the lowest 0 bit*/
#define OOC_SAL0(a) ((a) | ~(a)-1)/*set all bits except the lowest 0 bit*/

#endif /* OOC_UTILS_MACROS_H */

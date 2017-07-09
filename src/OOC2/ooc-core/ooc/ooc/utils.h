#ifndef OOC_OOC_OOC_H
#error "libooc: use ooc/ooc/ooc.h instead of ooc/ooc/utils.h directly"
#endif

/*
 *******************************
 * General utilities
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: utils.h,v 1.10 2006/08/21 11:58:01 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

/*
 * -------------------------
 *  Compilation flags
 * -------------------------
 */

#define OOC_NONE 0
#define OOC_DONE 1

/*
 * -------------------------
 *  Static assert
 * -------------------------
 */

#define OOC_STATIC_ASSERT(cond)					\
  struct   OOC_CAT(STATIC_ASSERT_,__LINE__) {			\
    enum { OOC_CAT(STATIC_ASSERT_,__LINE__) = !(cond) } _;	\
    int STATIC_ASSERT[(cond) ? 1 : -1];				\
  }

/*
 * -------------------------
 *  Const cast (remove cast)
 * -------------------------
 */

#define OOC_CONST_CAST(T,V) (*(T*)&(V))

/*
 * -------------------------
 *  Variadic macro manipulation
 *
 *  Original idea from P. Mensonides in c.s.c 27/11/2004
 * -------------------------
 */

#if OOC_GNU_C /* GCC */

#define OOC_VA_HAS2P(t,f, args...) \
  OOC_VA_PN(0, OOC_VA_PN(1, OOC_VA_IF2P(args, OOC_VA_DUPP(f)), t))
#define OOC_VA_HAS3P(t,f, args...) \
  OOC_VA_HAS2P(t,f, OOC_VA_PN(1, args))

#define OOC_VA_PN(i, args...) OOC_VA_P##i(args)
#define OOC_VA_P0(a, args...) a
#define OOC_VA_P1(a, args...) args

#define OOC_VA_DUPP(a) a, a
#define OOC_VA_IF2P(a, b, args...) b

#elif OOC_VA_MACROS /* C99 */

#define OOC_VA_HAS2P(t,f, ...) \
  OOC_VA_PN(0, OOC_VA_PN(1, OOC_VA_IF2P(__VA_ARGS__, OOC_VA_DUPP(f)), t))

#define OOC_VA_HAS3P(t,f, ...) \
  OOC_VA_HAS2P(t,f, OOC_VA_PN(1, __VA_ARGS__))

#define OOC_VA_PN(i, ...) OOC_VA_P##i(__VA_ARGS__)
#define OOC_VA_P0(a, ...) a
#define OOC_VA_P1(a, ...) __VA_ARGS__

#define OOC_VA_DUPP(a) a, a
#define OOC_VA_IF2P(a, b, ...) b

#endif

/*
 * -------------------------
 *  Token manipulation
 * -------------------------
 */

#define OOC_STR(a) OOC_STR_(a)
#define OOC_STR_(a) # a

#define OOC_CAT(a,b) OOC_CAT_(a,b)
#define OOC_CAT_(a,b) a ## b

#define OOC_CAT3(a,b,c) OOC_CAT3_(a,b,c)
#define OOC_CAT3_(a,b,c) a ## b ## c

#define OOC_CATD_(a,b) OOC_CATD__(a,b)
#define OOC_CATP_(a,b) OOC_CATP__(a,b)
#define OOC_CATD__(a,b) a ## b
#define OOC_CATP__(a,b) a ## b

#define OOC_AMS /* Avoid Macro Substitution */

/*
 * -------------------------
 *  Formatted strings
 * -------------------------
 */

/* NOTE-INFO: GCC checks for printf-like and scanf-like format string */
#define OOC_PRINTF(n)  __attribute__((__format__ (__printf__, n, n+1)))
#define OOC_VPRINTF(n) __attribute__((__format__ (__printf__, n, 0  )))
#define OOC_SCANF(n)   __attribute__((__format__ (__scanf__ , n, n+1)))
#define OOC_VSCANF(n)  __attribute__((__format__ (__scanf__ , n, 0  )))

/*
 * -------------------------
 *  Static array
 * -------------------------
 */

#define OOC_ARRLEN(a) (sizeof(a)/sizeof(*(a)))

/*
 * -------------------------
 *  Reference counting
 * -------------------------
 */

/* NOTE-INFO: Object's reference counting
 *
 * Reference counting patterns:
 *
 *  object's field _cnt (unsigned int)
 *
 *  Refcount: count of references to object
 *  Context : context identifier (unique for each try-catch block)
 *
 *  +---+---------+----------+
 *  | 1 | Context | Refcount |       (Attached to context)
 *  +---+---------+----------+ 
 * 
 *  +---+--------------------+
 *  | 0 |      Refcount      |       (Detached)
 *  +---+--------------------+ 
 *
 *  if an 'int' is 32 bits wide or more
 *    Context uses 15 bits (32768 contexts)
 *  else
 *    Context uses 7 bits (128 contexts)
 *
 *  Refcount uses the remaining bits (= #bit(int) - #bit(Context) - 1)
 */

#if UINT_MAX >= 2147483648UL
#  define OOC_CONTEXT_BIT 15
#else
#  define OOC_CONTEXT_BIT 7
#endif

#define OOC_ATTACH_MASK  (~(~0U >> 1))
#define OOC_REFCNT_MASK  (~0U >> (OOC_CONTEXT_BIT+1))
#define OOC_CONTEXT_MASK (~(OOC_ATTACH_MASK | OOC_REFCNT_MASK))
#define OOC_CONTEXT_UNIT (OOC_REFCNT_MASK+1)

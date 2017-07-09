#ifndef OOC_OOC_OOC_H
#error "libooc: use ooc/ooc/ooc.h instead of ooc/ooc/error.h directly"
#endif 

/*
 *******************************
 * Error (low level) handler interface
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: error.h,v 1.3 2005/12/05 17:42:25 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

/*
 * -------------------------
 *  Error handlers
 * -------------------------
 */

/* NOTE-USER: error handlers
 *  - all these handlers display on stderr
 *  - if fmt is ending by ':', the errno string is added
 *  - a '\n' is automatically added to the end
 */

void ooc_log      (const char *fmt, ...) OOC_PRINTF(1); /* returns */
void ooc_debug    (const char *fmt, ...) OOC_PRINTF(1); /* returns */
void ooc_warning  (const char *fmt, ...) OOC_PRINTF(1); /* returns */
void ooc_error    (const char *fmt, ...) OOC_PRINTF(1); /* returns */
void ooc_abort    (const char *fmt, ...) OOC_PRINTF(1)
                            __attribute__ ((noreturn)); /* abort   */

#ifdef  OOC_DBG
#undef  OOC_DBG
#define OOC_DBG(msg) ooc_debug msg
#else
#undef  OOC_DBG
#define OOC_DBG(msg) ((void)0)
#endif

#ifdef  OOC_LOG
#undef  OOC_LOG
#define OOC_LOG(msg) ooc_log msg
#else
#undef  OOC_LOG
#define OOC_LOG(msg) ((void)0)
#endif

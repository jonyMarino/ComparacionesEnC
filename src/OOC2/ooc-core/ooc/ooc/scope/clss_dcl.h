/* multiple inclusion allowed */

/*
 ******************************
 * Class declaration
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: clss_dcl.h,v 1.2 2005/12/14 18:35:06 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

/* protocol types */
#if   defined(ABSTRACT_PROTOCOL)
# define PROTOCOL       ABSTRACT_PROTOCOL
# define ABSTRACT_CLASS ABSTRACT_PROTOCOL
#elif defined(FINAL_PROTOCOL)
# define PROTOCOL       FINAL_PROTOCOL
# define FINAL_CLASS    FINAL_PROTOCOL
#endif

/* metaclass types */
#if   defined(ABSTRACT_METACLASS)
# define METACLASS      ABSTRACT_METACLASS
# define ABSTRACT_CLASS ABSTRACT_METACLASS
#elif defined(FINAL_METACLASS)
# define METACLASS      FINAL_METACLASS
# define FINAL_CLASS    FINAL_METACLASS
#endif

/* class types */
#if   defined(ABSTRACT_CLASS)
# define CLASS ABSTRACT_CLASS
#elif defined(FINAL_CLASS)
# define CLASS FINAL_CLASS
#elif defined(METACLASS)
# define CLASS METACLASS
#elif defined(PROTOCOL)
# define CLASS PROTOCOL
#endif

/* default superclass */
#ifndef SUPER_CLASS
#if    defined(PROTOCOL)
# define SUPER_CLASS Protocol
#elif  defined(METACLASS)
# define SUPER_CLASS Class
#else
# define SUPER_CLASS Object
#endif
#endif

/* default metaclass */
#ifndef META_CLASS
#if   defined(METACLASS)
# define META_CLASS MetaClass
#else
# define META_CLASS Class
#endif
#endif

/* default rootclass */
#ifndef ROOT_CLASS
#define ROOT_CLASS Object
#endif

/* check presence of class */
#ifndef CLASS
#error "libooc: missing define of either CLASS, ABSTRACT_CLASS, FINAL_CLASS or METACLASS, ABSTRACT_METACLASS, FINAL_METACLASS or PROTOCOL, ABSTRACT_PROTOCOL, FINAL_PROTOCOL"
#endif


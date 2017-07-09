#ifndef OOC_OOC_PROTOCOL_H
#define OOC_OOC_PROTOCOL_H

#ifndef OOC_OBJECT_H
#error "libooc: use ooc/Object.h instead of ooc/ooc/Protocol.h directly"
#endif

/*
 ******************************
 * Protocol interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Protocol.h,v 1.3 2005/12/02 11:05:42 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

/*
 * -------------------------
 *  Protocol interface
 *  Root of all OOC protocols
 * -------------------------
 */

#include ooc_Interface

#define ABSTRACT_PROTOCOL Protocol
#define SUPER_CLASS Object

#define PROTODEF_Protocol \
        /* must be empty */

#include ooc_End

#endif /* OOC_OOC_PROTOCOL_H */

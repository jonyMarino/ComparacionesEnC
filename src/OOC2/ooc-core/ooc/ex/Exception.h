#ifndef OOC_EX_EXCEPTION_H
#define OOC_EX_EXCEPTION_H

/*
 ******************************
 * Exception interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Exception.h,v 1.2 2005/12/05 18:00:33 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/Object.h>
#include <ooc/protocol/Copiable.h>

#include ooc_Interface

#define ABSTRACT_CLASS Exception

#define CLASSDEF_Exception \
        PROTODEF(Copiable)

#include ooc_End

#endif /* OOC_EX_EXCEPTION_H */

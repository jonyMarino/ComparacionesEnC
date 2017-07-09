#ifndef OOC_EX_EXSIGNAL_H
#define OOC_EX_EXSIGNAL_H

/*
 ******************************
 * ExSignal interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: ExSignal.h,v 1.4 2005/12/20 15:17:18 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/ex/Exception.h>

#include ooc_Interface

#define ABSTRACT_CLASS ExSignal
#define SUPER_CLASS Exception

#define CLASSDEF_ExSignal			\
        CLASSDEF_Exception			\
  ooc_visible(int, sig_id)			\
						\
  ooc_staticMethod0(bool, trap)

#include ooc_End

#endif /* OOC_EX_EXSIGNAL_H */

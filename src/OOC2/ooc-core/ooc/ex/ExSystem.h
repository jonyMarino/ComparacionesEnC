#ifndef OOC_EX_EXSYSTEM_H
#define OOC_EX_EXSYSTEM_H

/*
 ******************************
 * ExSystem interface
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: ExSystem.h,v 1.4 2005/12/20 15:17:18 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/ex/Exception.h>
#include <errno.h>

#include ooc_Interface

#define CLASS ExSystem
#define SUPER_CLASS Exception

#define CLASSDEF_ExSystem			\
        CLASSDEF_Exception			\
    ooc_visible(int, syserr)

#include ooc_End

#define ooc_throwSys(type)				\
  ((void)(errno || ooc_throwSys_(errno,			\
   (classExSystem)ooc_Class(type), __FILE__, __LINE__)))

/*
 * private services
 */

bool
ooc_throwSys_(int syserr, classExSystem cls, const char *file, int line);

#endif /* OOC_EX_EXSYSTEM_H */

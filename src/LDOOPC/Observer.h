/**********************************************************************************
 * Copyright: 
 * Project: RootElement
 * File: SOOPC/Observer.h
 * Code Management Tool File Version: 
 * SDD Component: Observer
 * Language: C
 * Author: 
 **********************************************************************************/

/*!
 * \file Observer.h
 * \brief Observer
 */

#ifndef Observer_H
#define Observer_H

/**********************************************************************************
 * Observer.h
 **********************************************************************************/

/*! 
 * \package Observer
 */
#include "../LDOOPC/ooc.h"

#undef  OBJECT

#define OBJECT Observer

BASEOBJECT_INTERFACE
BASEOBJECT_METHODS
  void constMethod_(update) int value __;
ENDOF_INTERFACE

ABSTRACTCLASS_INTERFACE

ENDOF_INTERFACE

#endif

/**********************************************************************************
 * File Path: Observer.h
 **********************************************************************************/

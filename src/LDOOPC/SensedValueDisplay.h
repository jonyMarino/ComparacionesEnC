/**********************************************************************************
 * Copyright: 
 * Project: RootElement
 * File: SOOPC/SensedValueDisplay.h
 * Code Management Tool File Version: 
 * SDD Component: SensedValueDisplay
 * Language: C
 * Author: 
 **********************************************************************************/

/*!
 * \file SensedValueDisplay.h
 * \brief SensedValueDisplay
 */

#ifndef SensedValueDisplay_H
#define SensedValueDisplay_H

/* Dependency with parent package */
#include "../LDOOPC/Observer.h"
/**********************************************************************************
 * SensedValueDisplay.h
 **********************************************************************************/

#undef  OBJECT
#define OBJECT SensedValueDisplay

OBJECT_INTERFACE

  INHERIT_MEMBERS_OF (Observer);

OBJECT_METHODS

  INHERIT_METHODS_OF (Observer);

ENDOF_INTERFACE

CLASS_INTERFACE

ENDOF_INTERFACE

#endif

/**********************************************************************************
 * File Path: SOOPC/SensedValueDisplay.h
 **********************************************************************************/

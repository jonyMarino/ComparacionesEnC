

/**********************************************************************************
 * Copyright: 
 * Project: RootElement
 * File: SOOPC/SensedValueDisplay.c
 * Code Management Tool File Version: 
 * SDD Component: SensedValueDisplay
 * Language: C
 * Author: 
 **********************************************************************************/

/*!
 * \file SOOPC/SensedValueDisplay.c
 * \brief SensedValueDisplay
 */

/* Dependency with stdio. */
#include <stdio.h>

#define IMPLEMENTATION

/* Dependency with own header */
#include "../LDOOPC/SensedValueDisplay.h"

void constMethodOvldDecl_(update, Observer) int value __
{
  printf("updated:%d\n", value);
}

OBJECT_IMPLEMENTATION

  SUPERCLASS(Observer)

ENDOF_IMPLEMENTATION

initClassDecl() /* class ctor, required */
{
  initSuper(Observer);
  overload(Observer.update) = methodOvldName(update, Observer);
}

dtorDecl() /* object dtor, required */
{
  Observer._Observer(super(this,Observer)); /* upcast */
}

CLASS_IMPLEMENTATION

ENDOF_IMPLEMENTATION
/**********************************************************************************
 * SOOPC/SensedValueDisplay.c
 **********************************************************************************/
/*## package SOOPC */

/**********************************************************************************
 * File Path: SOOPC/SensedValueDisplay.c
 **********************************************************************************/



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
/* Dependency with own header */
#include "SensedValueDisplay.h"
/* Dependency with stdio. */
#include <stdio.h>


/**********************************************************************************
 * SOOPC/SensedValueDisplay.c
 **********************************************************************************/
/*## package SOOPC */

/*## class TopLevel::SensedValueDisplay */






// Virtual Methods 
void SensedValueDisplay_update_ (SensedValueDisplay * self, int value){
	//Start of user code user code1
	printf("updated: %d\n",value);
	//End of user code
}


// Final Methods 
void SensedValueDisplay_ctor (SensedValueDisplay * self){
	static SensedValueDisplayVtbl const vtbl={
	SensedValueDisplay_update_};

	//Start of user code user code for ctor
 	self -> super.vptr = &vtbl; /* override the vptr */	
	//TO DO
	//End of user code
}


// Selectors    


/**********************************************************************************
 * File Path: SOOPC/SensedValueDisplay.c
 **********************************************************************************/

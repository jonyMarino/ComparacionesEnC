

/**********************************************************************************
 * Copyright: 
 * Project: RootElement
 * File: SOOPC/Observer.c
 * Code Management Tool File Version: 
 * SDD Component: Observer
 * Language: C
 * Author: 
 **********************************************************************************/

/*!
 * \file SOOPC/Observer.c
 * \brief Observer
 */
/* Dependency with own header */
#include "Observer.h"


/**********************************************************************************
 * SOOPC/Observer.c
 **********************************************************************************/
/*## package SOOPC */

/*## class TopLevel::Observer */






// Virtual Methods 


// Final Methods 


// Selectors    
void Observer_update (Observer * self, int value){
	 self-> vptr -> update(self, value );
}


/**********************************************************************************
 * File Path: SOOPC/Observer.c
 **********************************************************************************/

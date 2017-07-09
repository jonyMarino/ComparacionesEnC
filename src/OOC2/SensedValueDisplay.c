/*
 * Observer.c
 *
 *  Created on: 9 jul. 2017
 *      Author: marino
 */


#include "Observer.h"

#include OpenImplementation

#include "SensedValueDisplay.h"

// ... overridden or new methods definitions

method(void, update , SELF, int  value){
	printf("updated:%d\n", value);
}

#include CloseImplementation

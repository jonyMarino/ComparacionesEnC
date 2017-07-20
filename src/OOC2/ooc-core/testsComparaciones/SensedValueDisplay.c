/*
 * Observer.c
 *
 *  Created on: 9 jul. 2017
 *      Author: marino
 */

#define USING_OOC

#include <ooc/Object.h>

#include Implementation

#include "SensedValueDisplay.h"


method1(void, update , int  value){
	printf("updated:%d\n", value);
}

staticMethod0(void, initialize)
{
  override( update   );
}

#include End

/*
 *******************************
 * BigObj implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: BigObj.c,v 1.1 2005/10/25 12:11:34 oachim Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#define USING_OOC

#include <ooc/Object.h>

#include Implementation

#define BigObj_PRIVATE_DEF		\
	privateN(char, pad, [4096])

#include "BigObj.h"

/*
 * Static methods
 */

staticMethod0(void, initialize) {}

#include End

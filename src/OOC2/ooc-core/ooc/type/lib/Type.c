/*
 *******************************
 * Type implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Type.c,v 1.3 2005/12/16 16:56:04 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#define USING_OOC

#include <ooc/Object.h>

/*
 * Type Object Implementation
 */

#include Implementation

#include <ooc/type/Type.h>

method0(TYPE, init)
{
  self->type.id = ooc_type_invalid;

  return self;
}

method1(TYPE, initWith, ooc_type type)
{
  self->type = type;

  return self;
}

staticMethod0(void, initialize) 
{
  override( init     );
  override( initWith );
}

#include End

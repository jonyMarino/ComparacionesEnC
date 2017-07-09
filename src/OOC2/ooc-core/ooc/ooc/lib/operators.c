/*
 ******************************
 * Operators implementation
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: operators.c,v 1.5 2005/12/12 09:59:52 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/ex/ExBadCast.h>
#include <ooc/protocol/Copiable.h>

void*
(ooc_cloneLoc)(Object obj, const char *file, int line)
{
  if (obj) {
    Copiable cpy = ecastToProtoLoc(obj, Copiable, file, line);
    Object obj_c = newAs(obj->_isa);
    
    cpy->copy(obj_c, obj);
    
    return obj_c;
  }
  
  return 0;
}

/*
 * -------------------------
 *  Hidden services
 * -------------------------
 */

void
ooc_badcast_(const char *file, int line)
{
  throwLoc(new(ExBadCast), file, line);
}

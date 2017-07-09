/*
 ******************************
 * Abstract Object Memory implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: abspool_srv.c,v 1.10 2005/12/15 16:58:59 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/ex/ExBadClass.h>

/*
 * -----------------------
 * Abstract class services
 * -----------------------
 */

static
Object absobj_alloc(classObject cls)
{
  throw(new(ExBadClass));
  (void)cls;
  return 0;
}

static
void absobj_dealloc(Object obj)
{
  throw(new(ExBadClass));
  (void)obj;
}

static
void absobj_detach(Object obj)
{
  (void)obj;
}

/*
 * -----------------------
 * AbsPool public services
 * -----------------------
 */

struct ooc_memsrv ooc_memAbsSrv[1] = {{
  absobj_alloc,
  absobj_dealloc,
  absobj_detach
}};


/*
 ******************************
 * Big Pool Services implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: bigpool_srv.c,v 1.9 2005/12/15 16:58:59 ldeniau Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/ooc/lib/context.h>
#include <ooc/ooc/lib/allocator.h>
#include <ooc/ooc/lib/bigpage.h>

#include <ooc/ooc/lib/bigpool.h>

/*
 * --------------------
 * Big objects services
 * --------------------
 */

static Object
bigobj_alloc(classObject cls)
{
  struct ooc_context *context = ooc_contextGet();
  struct allocator     *alloc = context->allocator;
  Object obj;

  alloc->bigpool =
    ooc_bigpool_alloc(alloc->bigpool, ooc_classInstanceSize(cls));
  
  obj = ooc_bigpage_getObj(alloc->bigpool->first_page);

  OOC_CONST_CAST(classObject, obj->_isa) = cls;
  OOC_CONST_CAST(unsigned   , obj->_cnt) = alloc->id;

  return obj;
}

static void
bigobj_dealloc(Object obj)
{
  struct bigpage *page = ooc_bigpage_getPage(obj);
  
  ooc_bigpool_dealloc(page);
}

static void
bigobj_detach(Object obj)
{
  (void)obj;
}

/*
 * -----------------------
 * BigPool public services
 * -----------------------
 */

struct ooc_memsrv ooc_memBigSrv[1] = {{
  bigobj_alloc,
  bigobj_dealloc,
  bigobj_detach
}};

#if OOC_GC_USE

struct ooc_memsrv ooc_memGCSrv[1] = {{
  bigobj_alloc,
  bigobj_dealloc,
  bigobj_detach
}};

#endif

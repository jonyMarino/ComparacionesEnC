/*
 *******************************
 * Class implementation
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: MetaClass.c,v 1.1 2005/12/14 18:35:05 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#define USING_OOC

#include <ooc/ooc/ooc.h>

/*
 * -------------------------
 *  MetaClass implementation
 * -------------------------
 */

#include Implementation

#include <ooc/Object.h> /* friend classes */

/* reactivate MetaClass scope */
#include CloseScope
#define ABSTRACT_METACLASS MetaClass
#define ROOT_CLASS Class
#include OpenScope

/*
 * Static functions
 */

static void
check_metaclass_inheritance(MetaClass cls)
{
  MetaClass spr = (MetaClass)cls->_spr;
  classObject spr_root, cls_root;
  
  if (!ooc_classIsMetaClass(spr))
    ooc_abort("invalid inheritance, metaclass %s does not derive from a "
	      "metaclass (check SUPER_CLASS of %s)", ooc_className(cls),
	      ooc_className(cls));
  
  cls_root = cls->_dat->root;
  spr_root = spr->_dat->root;
  
  if (!isSubclassOfClass(cls_root, spr_root))
    ooc_abort("invalid inheritance, rootclass %s is not subclass of "
	      "rootclass %s (check ROOT_CLASS of %s)",
	      ooc_className(cls_root), ooc_className(spr_root),
	      ooc_className(cls));
}

/*
 * Class methods
 */

method0(TYPE, init)
{
  OOC_DBG((OOC_STR(CLASS)".init(%s)", ooc_className(self)));

  if (!isClassOf(self, Class))
    check_metaclass_inheritance(self);
  
  scall0(init);
  
  return self;
}

method0(void, deinit)
{
  OOC_DBG((OOC_STR(CLASS)".deinit(%s)", ooc_className(self)));
  
  scall0(deinit);
}

staticMethod0(void, initialize)
{
  override( init   );
  override( deinit );
}

#include End

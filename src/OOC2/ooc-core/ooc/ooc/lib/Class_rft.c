/*
 *******************************
 * Class implementation
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Class_rft.c,v 1.6 2005/12/09 17:43:09 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#define USING_OOC

#include <string.h>
#include <stdlib.h>
#include <ooc/ooc/ooc.h>

/*
 * -------------------------
 *  Class implementation
 * -------------------------
 */

#include ImplementationExtension

#include <ooc/Object.h>
#include <ooc/reflect/StaticField.h>
#include <ooc/reflect/StaticMethod.h>
#include <ooc/ex/ExBadRange.h>
#include <ooc/ex/ExNotFound.h>

/* restore Class scope */
#include ooc_CloseScope
#define ABSTRACT_METACLASS Class
#define SUPER_CLASS Object
#include ooc_OpenScope

/*
 * Static functions
 */

static inline int
find_fldName(const void *name_, const void *fld_)
{
  const char *name = name_;
  const struct ooc_meta_fld *fld = fld_;
  
  return strcmp(name, fld->name);
}

static inline int
find_mthdName(const void *name_, const void *mth_)
{
  const char *name = name_;
  const struct ooc_meta_mth *mth = mth_;
  
  return strcmp(name, mth->name);
}

/*
 * Class methods
 */

constMethod1(constClass, findSubclass, const char *name)
{
  constClass cls_itr = self;

  while(1) {
    const char *cls_name = ooc_className(cls_itr);
    
    if (cls_name == name || !strcmp(cls_name, name))
      return cls_itr;
    
    if (ooc_classSubClass(cls_itr)) {
      cls_itr = ooc_classSubClass(cls_itr);
      continue;
    }

    if (ooc_classNextClass(cls_itr)) {
      cls_itr = ooc_classNextClass(cls_itr);
      continue;
    }

    do {
      if (cls_itr == self)
	return 0;

      cls_itr = (Class)ooc_classSuper(cls_itr);
    } while(!ooc_classNextClass(cls_itr));

    cls_itr = ooc_classNextClass(cls_itr);
  }
}

staticMethod1(constClass, findClass, const char *name)
{
  constClass cls_o = (Class)Class(Object);
  constClass cls = call1(cls_o, findSubclass, name);

  if (!cls)
    cls = Class(Class)->loadClass(0, name);

  return cls;
}

constMethod0(size_t, fieldCnt)
{
  return ooc_classReflect(self)->fld_cnt;
}

constMethod1(constField, newField, const char *name)
{
  struct ooc_meta_fld *fld = 
    bsearch(name, 
	    ooc_classReflect(self)->fld, 
	    ooc_classReflect(self)->fld_cnt, 
	    sizeof(struct ooc_meta_fld), find_fldName);

  if (!fld)
    throw(new(ExNotFound));

  return (constField)new2(StaticField, initWith, self, fld);
}

constMethod1(constField, newFieldAt, size_t idx_)
{
  size_t idx;  

  if (idx_ >= ooc_classReflect(self)->fld_cnt) 
    throw(new(ExBadRange));

  idx = ooc_classReflect(self)->fld_lut[idx_];

  return (constField)new2(StaticField, initWith, self, 
			  &ooc_classReflect(self)->fld[idx]);
}

constMethod0(size_t, methodCnt)
{
  return ooc_classReflect(self)->mth_cnt;
}

constMethod1(constMethod, newMethod, const char *name)
{
  struct ooc_meta_mth *mth = 
    bsearch(name, 
	    ooc_classReflect(self)->mth, 
	    ooc_classReflect(self)->mth_cnt, 
	    sizeof(struct ooc_meta_mth), find_mthdName);

  if (!mth)
    throw(new(ExNotFound));

  return (constMethod)new2(StaticMethod, initWith, self, mth);
}

constMethod1(constMethod, newMethodAt, size_t idx)
{ 
  if (idx >= ooc_classReflect(self)->mth_cnt) 
    throw(new(ExBadRange));
    
  return (constMethod)new2(StaticMethod, initWith, self, 
			   &ooc_classReflect(self)->mth[idx]);
}

implementationExtension(rft)
{
  override( findClass    );
  override( findSubclass );

  override( fieldCnt     );
  override( newField     );
  override( newFieldAt   );
 
  override( methodCnt    );
  override( newMethod    );
  override( newMethodAt  );
}

#include End

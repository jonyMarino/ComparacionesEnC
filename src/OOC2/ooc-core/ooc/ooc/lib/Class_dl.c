/*
 *******************************
 * Class implementation
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Class_dl.c,v 1.4 2005/12/18 19:04:41 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#define USING_OOC

#include <ooc/ooc/ooc.h>

#if OOC_POSIX_DLINK_USE
#include <stdio.h>
#include <string.h>
#include <ooc/assert.h>
#include OOC_POSIX_DLINK_HDR
#endif

/*
 * -------------------------
 *  Class implementation
 * -------------------------
 */

#include ImplementationExtension

#include <ooc/Object.h>
#include <ooc/ex/ExNotFound.h>
#include <ooc/ex/ExNotSupported.h>

/* restore Class scope */
#include CloseScope
#define ABSTRACT_METACLASS Class
#define SUPER_CLASS Object
#include OpenScope

/*
 * Class methods
 */

staticMethod2(constClass, loadClass, const char *lib, const char *name)
{
#if OOC_POSIX_DLINK_USE
  Class cls;
  void *handle;
  char sym_name[256];
  size_t sym_maxlen = sizeof(sym_name)-sizeof(ooc_classDescSymStr());

  ooc_assert(name && strlen(name) <= sym_maxlen);

  handle = dlopen(lib, RTLD_GLOBAL | RTLD_LAZY);

  if (!handle) {
    ooc_error("unable to load class %s [dlopen]: %s", name, dlerror());
    throw(new(ExNotFound));
  }

  sprintf(sym_name, ooc_classDescSymStr(OOC_STR(%s)), name);

  cls = dlsym(handle, sym_name);

  if (!cls) {
    ooc_error("unable to load class %s [dlsym]: %s", name, dlerror());
    if (dlclose(handle))
      ooc_error("unable close dynamic library [dlclose]: %s", dlerror());
    throw(new(ExNotFound));
  }

  if (!lib) {
    if (dlclose(handle))
      ooc_error("unable close dynamic library [dlclose]: %s", dlerror());
  }
  
  ooc_classDescInitialize(cls);

  return cls;
  
#else
  (void)lib; (void)name;
  throw(new(ExNotSupported));
  return 0;
#endif
}

implementationExtension(dl)
{
  override( loadClass );
}

#include End

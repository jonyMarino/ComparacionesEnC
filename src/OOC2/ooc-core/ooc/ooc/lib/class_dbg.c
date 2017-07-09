/*
 *******************************
 * Class trace implementation extension
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: class_dbg.c,v 1.1 2005/07/04 13:52:05 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#define USING_OOC

#include <stdio.h>
#include <ooc/Object.h>

/*
 * -------------------------
 *  Local implementation
 * -------------------------
 */

static void
displayTree(constClass cls, int lvl)
{
  int i;

  if (ooc_classNextClass(cls))
    displayTree(ooc_classNextClass(cls), lvl);

  for(i = 0; i < lvl; i++)
    putchar(' '), putchar(' ');

  printf("- %s", ooc_className(cls));

  if (OOC_CLASSINFO_GET(cls, OOC_CLASSINFO_AFMP)) {
    printf(" (");
    
    if (ooc_classIsAbstract (cls)) putchar('A');
    if (ooc_classIsFinal    (cls)) putchar('F');
    if (ooc_classIsProtocol (cls)) putchar('P');
    if (ooc_classIsMetaClass(cls)) putchar('M');
	
    putchar(')');
  }

  putchar('\n');

  if (ooc_classSubClass(cls))
    displayTree(ooc_classSubClass(cls), lvl+1);
}

/*
 * -------------------------
 *  Global implementation
 * -------------------------
 */

void
ooc_classInheritanceTree(constClass cls)
{
  displayTree(cls, 0);
}

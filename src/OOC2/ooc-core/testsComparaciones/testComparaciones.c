#define USING_OOC

#include <ooc/Object.h>
#include <ooc/assert.h>
#include <ooc/init_ooc.h>
#include <ooc/test/TestSuite.h>
#include <ooc/test/TestResult.h>
#include <ooc/ex/ExSigALRM.h>
#include <ooc/ex/ExSigBUS.h>
#include <ooc/ex/ExSigFPE.h>
#include <ooc/ex/ExSigILL.h>
#include <ooc/ex/ExSigINT.h>
#include <ooc/ex/ExSigQUIT.h>
#include <ooc/ex/ExSigSEGV.h>
#include <ooc/ex/ExSigTERM.h>
#include <string.h>
#include <stdio.h>

#include "SensedValueDisplay.h"

int main(int argc, char *argv[])
{
  ooc_init_ooc();

	SensedValueDisplay display = ooc_new( SensedValueDisplay );
	display->_isa->update(display,4);
	ooc_delete(display);

  return 0;
}

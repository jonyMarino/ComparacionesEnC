#define USING_OOC

#include <ooc/Object.h>
#include <ooc/reflect/ReflectMethods.h>
#include <ooc/reflect/ReflectFields.h>

#include <stdlib.h>

#include Implementation

#define MemorySpeedTest_PRIVATE_DEF			\
        privateN(struct DummyObj, obj , [5000000])	\
        privateN(DummyObj       , pobj, [5000000])

#include "DummyObj.h"
#include "MemorySpeedTest.h"

/*
 * Local functions
 */

static inline
void testAutoN(SELF, int n)
{
  size_t loop = n, i = 0;

  for (i = 0; i < loop; i++) {
    self->obj[i]._isa = Class(DummyObj);
    self->obj[i]._cnt = 1;

    Class(DummyObj)->init(&self->obj[i]);
  }

  for (i = 0; i < loop; i++)
    Class(DummyObj)->deinit(&self->obj[i]);
}

static inline
void testMallocN(SELF, int n)
{
  size_t loop = n, i = 0;

  for (i = 0; i < loop; i++) {
    Class cls = (Class)Class(DummyObj);
    size_t size = ooc_classInstanceSize(cls);

    self->pobj[i] = malloc(size);
    
    Class(DummyObj)->init(self->pobj[i]);
  }

  for (i = 0; i < loop; i++)
    Class(DummyObj)->deinit(self->pobj[i]);
}

static inline
void testNewN(SELF, int n)
{
  size_t loop = n, i = 0;
  
  for (i = 0; i < loop; i++)
    self->pobj[i] = new(DummyObj);

  for (i = 0; i < loop; i++)
    delete(self->pobj[i]);
}

/*
 * Object methods
 */

method0(Object, speedTest5000000xAUTO)
{
  testAutoN(self, 5000000);

  return 0;
}

method0(Object, speedTest5000000xMALLOC)
{
  testMallocN(self, 5000000);

  return 0;
}

method0(Object, speedTest5000000xNEW)
{
  testNewN(self, 5000000);

  return 0;
}

method0(Object, speedTest2500000xAUTO)
{
  testAutoN(self, 2500000);

  return 0;
}

method0(Object, speedTest2500000xMALLOC)
{
  testMallocN(self, 2500000);

  return 0;
}

method0(Object, speedTest2500000xNEW)
{
  testNewN(self, 2500000);

  return 0;
}

method0(Object, speedTest1000000xAUTO)
{
  testAutoN(self, 1000000);

  return 0;
}

method0(Object, speedTest1000000xMALLOC)
{
  testMallocN(self, 1000000);

  return 0;
}

method0(Object, speedTest1000000xNEW)
{
  testNewN(self, 1000000);

  return 0;
}

/*
 * Class methods
 */

staticMethod0(void, initialize)
{
  override(speedTest5000000xAUTO  );
  override(speedTest5000000xMALLOC);
  override(speedTest5000000xNEW   );

  override(speedTest2500000xAUTO  );
  override(speedTest2500000xMALLOC);
  override(speedTest2500000xNEW   );

  override(speedTest1000000xAUTO  );
  override(speedTest1000000xMALLOC);
  override(speedTest1000000xNEW   );
}

#include End

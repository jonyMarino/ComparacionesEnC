#define USING_OOC

#include <ooc/Object.h>
#include <ooc/reflect/ReflectMethods.h>
#include <ooc/reflect/ReflectFields.h>
#include <ooc/type/Int.h>

#include "DummyObj.h"
#include "Point.h"

#include <stdlib.h>

#include Implementation

#define MemoryPureSpeedTest_PRIVATE_DEF		\
        private (DummyObj       , persis_dummy)	\
        private (Point          , persis_point)	\
        privateN(DummyObj       , dummy , [5])	\
        privateN(struct DummyObj, adummy, [5])	\
        privateN(Point          , point , [1])

#include "MemoryPureSpeedTest.h"

#define LOOP 2000000

/*
 * Object methods
 */

method0(Object, speedTestAlloc1)
{
  classObject cls = (classObject)Class(DummyObj);
  size_t i;

  for (i = 0; i < LOOP; i++) {
    self->dummy[0] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    (ooc_classMemSrv(self->dummy[0]->_isa)->dealloc)((Object)self->dummy[0]);
  }

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestAlloc3)
{
  classObject cls = (classObject)Class(DummyObj);
  size_t i;

  for (i = 0; i < LOOP; i++) {
    self->dummy[0] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    (ooc_classMemSrv(self->dummy[0]->_isa)->dealloc)((Object)self->dummy[0]);
    self->dummy[0] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    (ooc_classMemSrv(self->dummy[0]->_isa)->dealloc)((Object)self->dummy[0]);
    self->dummy[0] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    (ooc_classMemSrv(self->dummy[0]->_isa)->dealloc)((Object)self->dummy[0]);

  }

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestMultiAlloc1)
{
  classObject cls = (classObject)Class(DummyObj);
  size_t i;

  for (i = 0; i < LOOP/5; i++) {
    self->dummy[0] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    self->dummy[1] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    self->dummy[2] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    self->dummy[3] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    self->dummy[4] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    
    (ooc_classMemSrv(self->dummy[0]->_isa)->dealloc)((Object)self->dummy[0]);
    (ooc_classMemSrv(self->dummy[1]->_isa)->dealloc)((Object)self->dummy[1]);
    (ooc_classMemSrv(self->dummy[2]->_isa)->dealloc)((Object)self->dummy[2]);
    (ooc_classMemSrv(self->dummy[3]->_isa)->dealloc)((Object)self->dummy[3]);
    (ooc_classMemSrv(self->dummy[4]->_isa)->dealloc)((Object)self->dummy[4]);
  }

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestMultiAlloc3)
{
  classObject cls = (classObject)Class(DummyObj);
  size_t i;

  for (i = 0; i < LOOP/5; i++) {
    self->dummy[0] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    self->dummy[1] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    self->dummy[2] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    self->dummy[3] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    self->dummy[4] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    
    (ooc_classMemSrv(self->dummy[0]->_isa)->dealloc)((Object)self->dummy[0]);
    (ooc_classMemSrv(self->dummy[1]->_isa)->dealloc)((Object)self->dummy[1]);
    (ooc_classMemSrv(self->dummy[2]->_isa)->dealloc)((Object)self->dummy[2]);
    (ooc_classMemSrv(self->dummy[3]->_isa)->dealloc)((Object)self->dummy[3]);
    (ooc_classMemSrv(self->dummy[4]->_isa)->dealloc)((Object)self->dummy[4]);

    self->dummy[0] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    self->dummy[1] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    self->dummy[2] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    self->dummy[3] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    self->dummy[4] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    
    (ooc_classMemSrv(self->dummy[0]->_isa)->dealloc)((Object)self->dummy[0]);
    (ooc_classMemSrv(self->dummy[1]->_isa)->dealloc)((Object)self->dummy[1]);
    (ooc_classMemSrv(self->dummy[2]->_isa)->dealloc)((Object)self->dummy[2]);
    (ooc_classMemSrv(self->dummy[3]->_isa)->dealloc)((Object)self->dummy[3]);
    (ooc_classMemSrv(self->dummy[4]->_isa)->dealloc)((Object)self->dummy[4]);

    self->dummy[0] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    self->dummy[1] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    self->dummy[2] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    self->dummy[3] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    self->dummy[4] = (DummyObj)(ooc_classMemSrv(cls)->alloc)(cls);
    
    (ooc_classMemSrv(self->dummy[0]->_isa)->dealloc)((Object)self->dummy[0]);
    (ooc_classMemSrv(self->dummy[1]->_isa)->dealloc)((Object)self->dummy[1]);
    (ooc_classMemSrv(self->dummy[2]->_isa)->dealloc)((Object)self->dummy[2]);
    (ooc_classMemSrv(self->dummy[3]->_isa)->dealloc)((Object)self->dummy[3]);
    (ooc_classMemSrv(self->dummy[4]->_isa)->dealloc)((Object)self->dummy[4]);
  }

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestMalloc1)
{
  Class cls = (Class)Class(DummyObj);
  size_t i;

  for (i = 0; i < LOOP; i++) {
    self->dummy[0] = malloc(ooc_classInstanceSize(cls));
    free(self->dummy[0]);
  }

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestMalloc3)
{
  Class cls = (Class)Class(DummyObj);
  size_t i;

  for (i = 0; i < LOOP; i++) {
    self->dummy[0] = malloc(ooc_classInstanceSize(cls));
    free(self->dummy[0]);

    self->dummy[0] = malloc(ooc_classInstanceSize(cls));
    free(self->dummy[0]);

    self->dummy[0] = malloc(ooc_classInstanceSize(cls));
    free(self->dummy[0]);
  }

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestMultiMalloc2)
{
  Class cls = (Class)Class(DummyObj);
  size_t i;

  for (i = 0; i < LOOP/5; i++) {
    self->dummy[0] = malloc(ooc_classInstanceSize(cls));
    self->dummy[1] = malloc(ooc_classInstanceSize(cls));
    self->dummy[2] = malloc(ooc_classInstanceSize(cls));
    self->dummy[3] = malloc(ooc_classInstanceSize(cls));
    self->dummy[4] = malloc(ooc_classInstanceSize(cls));

    free(self->dummy[0]);
    free(self->dummy[1]);
    free(self->dummy[2]);
    free(self->dummy[3]);
    free(self->dummy[4]);

    self->dummy[0] = malloc(ooc_classInstanceSize(cls));
    self->dummy[1] = malloc(ooc_classInstanceSize(cls));
    self->dummy[2] = malloc(ooc_classInstanceSize(cls));
    self->dummy[3] = malloc(ooc_classInstanceSize(cls));
    self->dummy[4] = malloc(ooc_classInstanceSize(cls));

    free(self->dummy[0]);
    free(self->dummy[1]);
    free(self->dummy[2]);
    free(self->dummy[3]);
    free(self->dummy[4]);
  }

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestMultiMalloc5)
{
  Class cls = (Class)Class(DummyObj);
  size_t i;

  for (i = 0; i < LOOP/5; i++) {
    self->dummy[0] = malloc(ooc_classInstanceSize(cls));
    self->dummy[1] = malloc(ooc_classInstanceSize(cls));
    self->dummy[2] = malloc(ooc_classInstanceSize(cls));
    self->dummy[3] = malloc(ooc_classInstanceSize(cls));
    self->dummy[4] = malloc(ooc_classInstanceSize(cls));

    free(self->dummy[0]);
    free(self->dummy[1]);
    free(self->dummy[2]);
    free(self->dummy[3]);
    free(self->dummy[4]);

    self->dummy[0] = malloc(ooc_classInstanceSize(cls));
    self->dummy[1] = malloc(ooc_classInstanceSize(cls));
    self->dummy[2] = malloc(ooc_classInstanceSize(cls));
    self->dummy[3] = malloc(ooc_classInstanceSize(cls));
    self->dummy[4] = malloc(ooc_classInstanceSize(cls));

    free(self->dummy[0]);
    free(self->dummy[1]);
    free(self->dummy[2]);
    free(self->dummy[3]);
    free(self->dummy[4]);

    self->dummy[0] = malloc(ooc_classInstanceSize(cls));
    self->dummy[1] = malloc(ooc_classInstanceSize(cls));
    self->dummy[2] = malloc(ooc_classInstanceSize(cls));
    self->dummy[3] = malloc(ooc_classInstanceSize(cls));
    self->dummy[4] = malloc(ooc_classInstanceSize(cls));

    free(self->dummy[0]);
    free(self->dummy[1]);
    free(self->dummy[2]);
    free(self->dummy[3]);
    free(self->dummy[4]);

    self->dummy[0] = malloc(ooc_classInstanceSize(cls));
    self->dummy[1] = malloc(ooc_classInstanceSize(cls));
    self->dummy[2] = malloc(ooc_classInstanceSize(cls));
    self->dummy[3] = malloc(ooc_classInstanceSize(cls));
    self->dummy[4] = malloc(ooc_classInstanceSize(cls));

    free(self->dummy[0]);
    free(self->dummy[1]);
    free(self->dummy[2]);
    free(self->dummy[3]);
    free(self->dummy[4]);

    self->dummy[0] = malloc(ooc_classInstanceSize(cls));
    self->dummy[1] = malloc(ooc_classInstanceSize(cls));
    self->dummy[2] = malloc(ooc_classInstanceSize(cls));
    self->dummy[3] = malloc(ooc_classInstanceSize(cls));
    self->dummy[4] = malloc(ooc_classInstanceSize(cls));

    free(self->dummy[0]);
    free(self->dummy[1]);
    free(self->dummy[2]);
    free(self->dummy[3]);
    free(self->dummy[4]);
  }

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestNew1)
{
  size_t i;

  for (i = 0; i < LOOP; i++) {
    self->dummy[0] = new(DummyObj);
    delete(self->dummy[0]);
  }

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestNew3)
{
  size_t i;

  for (i = 0; i < LOOP; i++) {
    self->dummy[0] = new(DummyObj);
    delete(self->dummy[0]);

    self->dummy[0] = new(DummyObj);
    delete(self->dummy[0]);

    self->dummy[0] = new(DummyObj);
    delete(self->dummy[0]);
  }

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestMultiNew1)
{
  size_t i;

  for (i = 0; i < LOOP/5; i++) {
    self->dummy[0] = new(DummyObj);
    self->dummy[1] = new(DummyObj);
    self->dummy[2] = new(DummyObj);
    self->dummy[3] = new(DummyObj);
    self->dummy[4] = new(DummyObj);

    delete(self->dummy[0]);
    delete(self->dummy[1]);
    delete(self->dummy[2]);
    delete(self->dummy[3]);
    delete(self->dummy[4]);
  }

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestMultiNew3)
{
  size_t i;

  for (i = 0; i < LOOP/5; i++) {
    self->dummy[0] = new(DummyObj);
    self->dummy[1] = new(DummyObj);
    self->dummy[2] = new(DummyObj);
    self->dummy[3] = new(DummyObj);
    self->dummy[4] = new(DummyObj);

    delete(self->dummy[0]);
    delete(self->dummy[1]);
    delete(self->dummy[2]);
    delete(self->dummy[3]);
    delete(self->dummy[4]);

    self->dummy[0] = new(DummyObj);
    self->dummy[1] = new(DummyObj);
    self->dummy[2] = new(DummyObj);
    self->dummy[3] = new(DummyObj);
    self->dummy[4] = new(DummyObj);

    delete(self->dummy[0]);
    delete(self->dummy[1]);
    delete(self->dummy[2]);
    delete(self->dummy[3]);
    delete(self->dummy[4]);

    self->dummy[0] = new(DummyObj);
    self->dummy[1] = new(DummyObj);
    self->dummy[2] = new(DummyObj);
    self->dummy[3] = new(DummyObj);
    self->dummy[4] = new(DummyObj);

    delete(self->dummy[0]);
    delete(self->dummy[1]);
    delete(self->dummy[2]);
    delete(self->dummy[3]);
    delete(self->dummy[4]);
  }

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestNewPoint1)
{
  size_t i;

  for (i = 0; i < LOOP; i++) {
    self->point[0] = new(Point);
    delete(self->point[0]);
  }

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestNewPoint3)
{
  size_t i;

  for (i = 0; i < LOOP; i++) {
    self->point[0] = new(Point);
    delete(self->point[0]);

    self->point[0] = new(Point);
    delete(self->point[0]);

    self->point[0] = new(Point);
    delete(self->point[0]);
  }

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestInit1)
{
  size_t i;

  for (i = 0; i < LOOP; i++) {
    Class(DummyObj)->init(&self->adummy[0]);
    Class(DummyObj)->deinit(&self->adummy[0]);
  }

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestInit3)
{
  size_t i;

  for (i = 0; i < LOOP; i++) {
    Class(DummyObj)->init(&self->adummy[0]);
    Class(DummyObj)->deinit(&self->adummy[0]);

    Class(DummyObj)->init(&self->adummy[0]);
    Class(DummyObj)->deinit(&self->adummy[0]);

    Class(DummyObj)->init(&self->adummy[0]);
    Class(DummyObj)->deinit(&self->adummy[0]);
  }

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestInitNotCheck1)
{
  classDummyObj cls = ooc_classDesc(DummyObj);
  size_t i;

  for (i = 0; i < LOOP; i++) {
    cls->init  (&self->adummy[0]);
    cls->deinit(&self->adummy[0]);
  }

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestInitNotCheck3)
{
  classDummyObj cls = ooc_classDesc(DummyObj);
  size_t i;

  for (i = 0; i < LOOP; i++) {
    cls->init(&self->adummy[0]);
    cls->deinit(&self->adummy[0]);

    cls->init(&self->adummy[0]);
    cls->deinit(&self->adummy[0]);

    cls->init(&self->adummy[0]);
    cls->deinit(&self->adummy[0]);
  }

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestMthd1)
{
  size_t i;

  for (i = 0; i < LOOP; i++)
    call0(self->persis_point, mthd);

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestMthd3)
{
  size_t i;

  for (i = 0; i < LOOP; i++) {
    call0(self->persis_point, mthd);
    call0(self->persis_point, mthd);
    call0(self->persis_point, mthd);
  }

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestMthdArg1)
{
  size_t i;

  for (i = 0; i < LOOP; i++)
    call1(self->persis_point, mthdArg, 0);

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestMthdArg3)
{
  size_t i;

  for (i = 0; i < LOOP; i++) {
    call1(self->persis_point, mthdArg, 0);
    call1(self->persis_point, mthdArg, 0);
    call1(self->persis_point, mthdArg, 0);
  }

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestMthdRetArg1)
{
  size_t i;

  for (i = 0; i < LOOP; i++)
    call1(self->persis_point, mthdRetArg, 0);

  return drop(new1(Int, initWith, LOOP));
}

method0(Object, speedTestMthdRetArg3)
{
  size_t i;

  for (i = 0; i < LOOP; i++) {
    call1(self->persis_point, mthdRetArg, 0);
    call1(self->persis_point, mthdRetArg, 0);
    call1(self->persis_point, mthdRetArg, 0);
  }

  return drop(new1(Int, initWith, LOOP));
}

/*
 * Setup/Cleanup
 */
method0(void, setup)
{
  self->persis_dummy = own(new(DummyObj));
  self->persis_point = own(new(Point));
}

method0(void, cleanup)
{
  release(self->persis_dummy);
  release(self->persis_point);
}

/*
 * Class methods
 */

staticMethod0(void, initialize)
{
  override( setup   );
  override( cleanup );

  override( speedTestAlloc1        );
  override( speedTestAlloc3        );

  override( speedTestInit1         );
  override( speedTestInit3         );

  override( speedTestInitNotCheck1 );
  override( speedTestInitNotCheck3 );

  override( speedTestMalloc1       );
  override( speedTestMalloc3       );

  override( speedTestMthdArg1      );     
  override( speedTestMthdArg3      );     

  override( speedTestMthd1         );     
  override( speedTestMthd3         );     

  override( speedTestMthdRetArg1   );     
  override( speedTestMthdRetArg3   );     

  override( speedTestMultiAlloc1   );
  override( speedTestMultiAlloc3   );

  override( speedTestMultiMalloc2  );
  override( speedTestMultiMalloc5  );

  override( speedTestMultiNew1     );
  override( speedTestMultiNew3     );

  override( speedTestNew1          );
  override( speedTestNew3          );

  override( speedTestNewPoint1     );
  override( speedTestNewPoint3     );
}

#include End

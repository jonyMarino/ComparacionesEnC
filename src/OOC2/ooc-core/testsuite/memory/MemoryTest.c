#define USING_OOC

#include <ooc/Object.h>
#include <ooc/assert.h>
#include <ooc/reflect/ReflectMethods.h>
#include <ooc/reflect/ReflectFields.h>
#include <ooc/ooc/lib/pool.h>
#include <ooc/ex/ExBadClass.h>
#include <ooc/ex/ExBadArgument.h>

#include <stdio.h>
#include <stdlib.h>

#include Implementation

#define MemoryTest_PRIVATE_DEF			\
        privateN(DummyObj, obj, [5000])		\
        privateN(void*   , ptr, [5000])		\
						\
        private (size_t  ,  dummy_size)		\
        private (DummyObj,   dummy_obj)		\
						\
        private (size_t  ,    big_size)		\
        private (BigObj  ,     big_obj)		\
						\
        private (size_t  ,    no_dummy)		\
        private (size_t  ,      no_big)

#include "DummyObj.h"
#include "BigObj.h"
#include "MemoryTest.h"

/*
 * Local functions
 */

static
void allocN(SELF, size_t n)
{
  size_t i;

  for (i = 0; i < n; i++)
    self->obj[i] = new(DummyObj);
}

/* dealloc objects */
static
void deallocN_1(SELF, size_t n)
{
  size_t i;

  for (i = 0; i < n; i++)
    delete(self->obj[i]);
}

static
void deallocN_2(SELF, size_t n)
{
  int i;

  for (i = n-1; i >= 0; i--)
    delete(self->obj[i]);
}

static
void deallocN_3(SELF, size_t n)
{
  size_t obj_page = ooc_page_objectCnt(self->dummy_size);
  size_t pages = n/obj_page + 1;
  size_t i, j;

  for (i = 0; i < obj_page; i++) {
    for (j = 0; j < pages; j++) {
      size_t index = j * obj_page + i;

      if (index < n) 
	delete(self->obj[index]);
    }
  }
}

static
void deallocN_4(SELF, size_t n)
{
  size_t obj_page = ooc_page_objectCnt(self->dummy_size);
  size_t pages = n/obj_page + 1;
  int    i = pages/2;
  size_t j = pages/2+1;
    
  while (i >= 0 || j < pages) {
    size_t k;

    if (i >= 0) {
      for (k = 0; k < obj_page; k++)
	delete(self->obj[i*obj_page + k]);
      i--;
    }

    if (j < pages) {
      for (k = 0; k < obj_page; k++) {
	size_t index = j*obj_page + k;

	if (index < n)
	  delete(self->obj[index]);
      }
      j++;
    }
  }
}

/*
 * Object methods
 */

method0(Object, testAbstractPool)
{
  volatile bool excpt = false;

  (void)self;

  try {
    Object obj = new(Object);
      
    (void)obj;
  } catch (ExBadClass, ex) {
    excpt = true;
    delete(ex);
  } endTry;

  ooc_testAssert(excpt);

  return 0;
}

/* 
 * FastPool test(s)
 */ 

method0(Object, testPoolAllocation)
{
  self->dummy_obj = new(DummyObj);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy + 1);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big      );

  delete(self->dummy_obj);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy    );

  return 0;
}

method0(Object, testPoolNewRetainDeleteRelease)
{
  DummyObj ref;

  self->dummy_obj = new(DummyObj);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy + 1);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big      );

  ref = retain(self->dummy_obj);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy + 1);

  delete(self->dummy_obj);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy + 1);

  release(ref);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy    );

  return 0;
}

method0(Object, testPoolNewRetainReleaseDelete)
{
  DummyObj ref;

  self->dummy_obj = new(DummyObj);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy + 1);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big      );

  ref = retain(self->dummy_obj);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy + 1);

  release(self->dummy_obj);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy + 1);

  delete(ref);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy    );

  return 0;
}

method0(Object, testPoolOwn)
{
  self->dummy_obj = own(new(DummyObj));
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy + 1);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big      );

  release(self->dummy_obj);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy    );

  return 0;
}

method0(Object, testPoolManyObjects)
{
  allocN    (self, 5000);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy + 5000);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big  );
  deallocN_1(self, 5000);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy);

  allocN    (self, 4000);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy + 4000);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big  );
  deallocN_2(self, 4000);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy);

  allocN    (self, 3000);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy + 3000);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big  );
  deallocN_3(self, 3000);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy);

  allocN    (self, 1024);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy + 1024);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big  );
  deallocN_4(self, 1024);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy);

  return 0;
}

/* 
 * StdPool test(s)
 */ 

method0(Object, testBigPoolAllocation)
{
  self->big_obj = new(BigObj);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big + 1);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy  );

  delete(self->big_obj);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big  );
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy);

  return 0;
}

method0(Object, testBigPoolNewRetainDeleteRelease)
{
  BigObj ref;

  self->big_obj = new(BigObj);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big + 1);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy  );

  ref = retain(self->big_obj);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big + 1);

  delete(self->big_obj);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big + 1);

  release(ref);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big  );
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy);

  return 0;
}

method0(Object, testBigPoolNewRetainReleaseDelete)
{
  BigObj ref;

  self->big_obj = new(BigObj);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big + 1);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy  );

  ref = retain(self->big_obj);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big + 1);

  release(self->big_obj);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big + 1);

  delete(ref);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big  );
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy);

  return 0;
}

method0(Object, testBigPoolOwn)
{
  self->big_obj = own(new(BigObj));
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big + 1);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy  );

  release(self->big_obj);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big  );
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy);

  return 0;
}

/* 
 * Exception safe test(s)
 */

method0(Object, testProtectionSingleContext)
{
  try {
    self->dummy_obj = new(DummyObj);
    self->big_obj   = new(BigObj);
    ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy + 1);
    ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big   + 1);

    throw(new(ExBadArgument));

    delete(self->dummy_obj);
    delete(self->big_obj);
  } catch(Exception, ex) {

    delete(ex);

  } endTry;

  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big  );

  return 0;
}

/* Multiple context exception thrown test */
method0(Object, testProtectionMultiContext)
{
  (void)self;
  try {
    self->dummy_obj = new(DummyObj);
    ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy + 1);
    ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big      );

    try {
      self->big_obj = new(BigObj);
      ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy + 1);
      ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big   + 1);

      throw(new(ExBadArgument));

      delete(self->big_obj);
    } catch(Exception, ex) {

      rethrow(ex);

    } endTry;

    ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy + 1);
    ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big      );

    delete(self->dummy_obj);

  } catch(Exception, ex) {

    delete(ex);

  } endTry;

  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big  );

  return 0;
}

/* drop + throw test */
method0(Object, testProtectionDropUnRetainedObject)
{
  self->dummy_obj = drop(new(DummyObj));
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy + 1);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big      );

  try {
    DummyObj ref;

    throw(new(ExBadArgument));

    ref = retain(self->dummy_obj);

    release(ref);
  } catch(Exception, ex) {

    delete(ex);

  } endTry;

  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big  );

  return 0;
}


/* drop + retain + throw test */
method0(Object, testProtectionDropRetainedObject)
{
  volatile DummyObj array = 0;
  
  self->dummy_obj = drop(new(DummyObj));
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy + 1);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big      );

  try {
    array = retain(self->dummy_obj);
    ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy + 1);
   
    throw(new(ExBadArgument));
  } catch(Exception, ex) {
    
    delete(ex);

  } endTry;

  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy + 1);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big      );

  release(array);
  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big  );

  return 0;
}

method0(Object, testIsObject)
{
  self->dummy_obj = new(DummyObj);
  self->big_obj   = new(BigObj);

  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy + 1);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big   + 1);

  ooc_testAssert(ooc_memIsObject((Object)self->dummy_obj));
  ooc_testAssert(ooc_memIsObject((Object)self->big_obj));

  ooc_testAssert(!ooc_memIsObject((Object)((char*)self->dummy_obj + 2)));
  ooc_testAssert(!ooc_memIsObject((Object)((char*)self->big_obj   + 2)));

  ooc_testAssert(!ooc_memIsObject((Object)(self->dummy_obj + 2)));
  ooc_testAssert(!ooc_memIsObject((Object)(self->big_obj   + 2)));

  delete(self->dummy_obj);
  delete(self->big_obj);

  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big  );

  return 0;
}

method0(Object, testIsObjectManyObjects)
{
  size_t i;
  size_t n = 5000;

  for (i = 0; i < n; i++)
    self->obj[i] = new(DummyObj);

  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy + 5000);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big         );

  for (i = 0; i < n; i++)
    ooc_testAssert(ooc_memIsObject((Object)self->obj[i]));
  
  for (i = 0; i < n; i++)
    delete(self->obj[i]);

  ooc_testAssert(ooc_memObjectCnt(self->dummy_size) == self->no_dummy);
  ooc_testAssert(ooc_memObjectCnt(self->big_size)   == self->no_big  );

  return 0;
}

method0(Object, testRawAllocation)
{
  int i;

  for (i = 0; i < 5000; i++)
    self->ptr[i] = ooc_memAlloc(14);

  for (i = 0 ; i < 5000; i++)
    ooc_memFree(self->ptr[i]);

  for (i = 0; i < 5000; i++)
    self->ptr[i] = ooc_memAlloc(14);

  for (i = 5000 - 1 ; i >= 0; i--)
    ooc_memFree(self->ptr[i]);

  return 0;
}

method0(Object, testRawIsAllocated)
{
  int i;

  for (i = 0; i < 5000; i++)
    self->ptr[i] = ooc_memAlloc(2);
  for (i = 0; i < 5000; i++)
    ooc_testAssert(ooc_memIsAllocated(self->ptr[i]));
  for (i = 0 ; i < 5000; i++)
    ooc_memFree(self->ptr[i]);

  for (i = 0; i < 5000; i++)
    self->ptr[i] = ooc_memAlloc(17);
  for (i = 0; i < 5000; i++)
    ooc_testAssert(ooc_memIsAllocated(self->ptr[i]));
  for (i = 5000 - 1 ; i >= 0; i--)
    ooc_memFree(self->ptr[i]);

  for (i = 0; i < 2; i++)
    self->ptr[i] = ooc_memAlloc(4076);
  for (i = 0; i < 2; i++)
    ooc_testAssert(ooc_memIsAllocated(self->ptr[i]));
  for (i = 2 - 1 ; i >= 0; i--)
    ooc_memFree(self->ptr[i]);

  for (i = 0; i < 2; i++)
    self->ptr[i] = ooc_memAlloc(4080);
  for (i = 0; i < 2; i++)
    ooc_testAssert(ooc_memIsAllocated(self->ptr[i]));
  for (i = 2 - 1 ; i >= 0; i--)
    ooc_memFree(self->ptr[i]);

  for (i = 0; i < 2; i++)
    self->ptr[i] = ooc_memAlloc(8192);
  for (i = 0; i < 2; i++)
    ooc_testAssert(ooc_memIsAllocated(self->ptr[i]));
  for (i = 2 - 1 ; i >= 0; i--)
    ooc_memFree(self->ptr[i]);

  return 0;
}

method0(Object, testClassObjCnt)
{
  size_t dummy_cnt = ooc_memClassObjectCnt((Class)Class(DummyObj));
  size_t big_cnt   = ooc_memClassObjectCnt((Class)Class(BigObj));
  DummyObj dummy_obj = new(DummyObj);
  BigObj   big_obj   = new(BigObj);
  
  (void)self;

  ooc_testAssert(dummy_cnt + 1 == 
		 ooc_memClassObjectCnt((Class)Class(DummyObj)));
  ooc_testAssert(big_cnt   + 1 == ooc_memClassObjectCnt((Class)Class(BigObj)));

  delete(dummy_obj);

  ooc_testAssert(dummy_cnt == ooc_memClassObjectCnt((Class)Class(DummyObj)));

  delete(big_obj);

  ooc_testAssert(big_cnt   == ooc_memClassObjectCnt((Class)Class(BigObj)));

  return 0;
}

/*
 * Setup/cleanup
 */

method0(void, setup)
{
  self->dummy_size = ooc_classInstanceSize(Class(DummyObj));
  self->big_size   = ooc_classInstanceSize(Class(BigObj)  );

  self->no_dummy   = ooc_memObjectCnt(self->dummy_size);
  self->no_big     = ooc_memObjectCnt(self->big_size  );
}

method0(void, cleanup)
{
  (void)self;
}

/*
 * Class Methods
 */

staticMethod0(void, initialize)
{
  override(setup  );
  override(cleanup);

  override(testAbstractPool                  );

  override(testPoolAllocation                );
  override(testPoolNewRetainDeleteRelease    );
  override(testPoolNewRetainReleaseDelete    );
  override(testPoolOwn                       );
  override(testPoolManyObjects               );

  override(testBigPoolAllocation             );
  override(testBigPoolNewRetainDeleteRelease );
  override(testBigPoolNewRetainReleaseDelete );
  override(testBigPoolOwn                    );

  override(testProtectionSingleContext       );
  override(testProtectionMultiContext        );
  override(testProtectionDropUnRetainedObject);
  override(testProtectionDropRetainedObject  );

  override(testIsObject                      );
  override(testIsObjectManyObjects           );

  override(testRawAllocation                 );
  override(testRawIsAllocated                );

  override(testClassObjCnt                   );
}

#include End

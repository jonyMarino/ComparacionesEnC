/* Template for a TYPE definition
   - replace xxxxx by the type name
   - replace yyyyy by the inherited type name
   - replace zzzzz by the inherited interface name
   - add more xxxxx methods implementation
   - add more xxxxx methods initialization
   - add more xxxxx_new??? constructors implementation
   - remove this comment

   Special cases:
   - no *new* interface:
     . remove xxxxx_interfaces
   - abstract type:
     . remove xxxxx_new constructor
   - final type
     . replace xxxxx_p.h by xxxxx.h
   - root type
     . remove everything related to yyyyy
     . remove SUPER and AS_SUPER
     . define default xxxxx_interfaces
     . define default xxxxx_cast
   - no thread:
     . use object as root class or
     . remove/define _USE_TLS -/to an empty definition
   - with threads:
     . replace/define _USE_TLS by/to __thread (Thread Local Storage)
 */
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "SensedValueDisplay_p.h"

#define TYPE          struct SensedValueDisplay
#define INTERFACE     struct SensedValueDisplay_interface
#define SELF        ((struct SensedValueDisplay_attribute*)self)
#define AS_SELF(a)  ((struct SensedValueDisplay_attribute*)(a) )
#define SUPER       ((struct object          *)self)
#define AS_SUPER(a) ((struct object          *)(a) )

static INTERFACE interface;

static void*
SensedValueDisplay_interfaces(TYPE* self, void *ref_i)
{
  if (ref_i == &Observer_interface)
    return &self->i->update;

  return interface.super->interface(SUPER,ref_i);
}

static TYPE*
SensedValueDisplay_init(TYPE *self)
{
  //interface.super->init(SUPER);

  return self;
}

/* put xxxxx method implementation here */

void SensedValueDisplay_update(TYPE * self, int value){
	printf("updated:%d\n",value);
}

/* instance methods should be defined as:

   static ret_type xxxxx_method_name(TYPE* [, ..]) { .. }

   where most of the time ret_type is TYPE* or void
*/

/* type methods should be defined as:

   static ret_type xxxxx_method_name([..]) { .. }

   where most of the time ret_type is TYPE*
*/

static void
SensedValueDisplay_initialize(void)
{
  struct object_interface *super_interface = object_interface();

  memcpy(&interface, super_interface, sizeof *super_interface);
  memcpy(&interface.update, &Observer_interface,sizeof Observer_interface);
  
  interface.super        = super_interface;
  interface.interface    = SensedValueDisplay_interfaces;
  interface.init         = SensedValueDisplay_init;
  interface.update = SensedValueDisplay_update;
  /* put xxxxx methods initialization here */
}

/*
 * Public constructors
 */

INTERFACE*
SensedValueDisplay_interface(void)
{
  if (!interface.interface)
	  SensedValueDisplay_initialize();
  
  return &interface;
}

TYPE*
SensedValueDisplay_new(void)
{
  TYPE *self = SensedValueDisplay_interface()->alloc(sizeof *SELF);
  assert(self);
  
  self->i = &interface;
  
  return SensedValueDisplay_init(self);
}

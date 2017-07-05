/* Template for a TYPE definition
   - replace xxxxx by the type name
   - replace yyyyy by the inherited type name
   - replace zzzzz by the inherited interface name
   - add more xxxxx methods in the xxxxx_interface definition
   - add more xxxxx_new??? constructors
   - remove this comment

   Special cases:
   - no *new* interface:
     . remove everything related to zzzzz
   - abstract type:
     . remove xxxxx_new constructor
   - final type
     . replace XXXXX_INTERFACE by its content in INTERFACE definition
     . remove  XXXXX_INTERFACE
   - root type
     . remove everything related to yyyyy
     . the first INTERFACE field should be struct super_interface *super;
 */
#ifndef SENSED_VALUE_DISPLAY_H
#define SENSED_VALUE_DISPLAY_H

#include "object.h"
#include "Observer.h"

#define TYPE      struct SensedValueDisplay
#define INTERFACE struct SensedValueDisplay_interface

#define SENSED_VALUE_DISPLAY_INTERFACE           \
        OBJECT_INTERFACE                         \
        OBSERVER_INTERFACE                       \

TYPE {
  INTERFACE *i;
};

INTERFACE {
  struct object_interface *super;
  SENSED_VALUE_DISPLAY_INTERFACE
};

TYPE      *SensedValueDisplay_new      (void);
INTERFACE *SensedValueDisplay_interface(void);

#undef TYPE
#undef INTERFACE

#endif /* SENSED_VALUE_DISPLAY_H */

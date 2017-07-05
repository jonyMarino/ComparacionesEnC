/* Template for a TYPE private definition
   - replace xxxxx by the type name
   - replace yyyyy by the inherited type name
   - add more xxxxx attributes in the xxxxx_attribute definition
   - remove this comment

   Special cases:
   - public attributes:
     . put this content in the xxxxx.h file
   - final type:
     . put this content in the xxxxx.c file
   - root type:
     . remove everything related to yyyyy
     . the first attribute should be struct interface *_;
 */
#ifndef SENSED_VALUE_DISPLAY_PH
#define SENSED_VALUE_DISPLAY_PH

#include "SensedValueDisplay.h"
#include "object_p.h"

struct SensedValueDisplay_attribute {
  struct object_attribute object;
};

#endif /* SENSED_VALUE_DISPLAY_PH */

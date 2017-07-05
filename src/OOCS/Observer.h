/* Template for an INTERFACE definition
   - replace xxxxx by the interface name
   - replace xxx by the interface first method
   - add more xxxxx methods in the xxxxx_interface definition and
     use a method name very close the interface name for the 1st method
     e.g. clonable -> clone, copiable -> copy then swap, comparable -> compare
   - remove this comment
 */
#ifndef OBSERVER_H
#define OBSERVER_H

#define TYPE      struct Observer
#define INTERFACE struct Observer_interface

#define OBSERVER_INTERFACE                      \
  TYPE* (*update)(TYPE*,int value);             \

TYPE {
  struct interface *i;
};

INTERFACE {
	OBSERVER_INTERFACE
};

extern INTERFACE Observer_interface;

#undef TYPE
#undef INTERFACE

#endif /* XXXXX_H */

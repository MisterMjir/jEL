#ifndef JEL_COMPONENT_STRUCT_H
#define JEL_COMPONENT_STRUCT_H

#include "component_utility.h"

#define JEL_COMPONENT_STRUCT_MEMBERS_SET(type, name) \
  type name;

#define JEL_COMPONENT_STRUCT_CREATE(component, ...) \
  struct component { \
    JEL_COMPONENT_MEMBERS_ITERATE(JEL_COMPONENT_STRUCT_MEMBERS_SET, __VA_ARGS__) \
  };

#endif

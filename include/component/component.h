#ifndef JEL_COMPONENT_H
#define JEL_COMPONENT_H

#include <stdint.h>

// ========================================
//
// Components
//
// Components are user defined structs,
// which are stored in tables (like a database)
// based on their members
//
// Since I need the size of the members and there
// can be a variable amount of members, macros are
// used to create the structs
//
// Tables will be tightly packed with parallel arrays
//
// ========================================

typedef uint32_t JEL_ComponentInt;

#define JEL_COMPONENT_CREATE(component, members_num, ...) \
  JEL_COMPONENT_CREATE_STRUCT(component, __VA_ARGS__) \

#endif

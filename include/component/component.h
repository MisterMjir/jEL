#ifndef JEL_COMPONENT_H
#define JEL_COMPONENT_H

#include "component_types.h"
#include "component_struct.h"
#include "component_table.h"

// ========================================
//
// Components
//
// Components is a general term referring to data,
// it could be the struct that represents the data,
// the table where the data is stored, or the data
// itself in the table. Since it's somewhat
// ambiguous what a component is, it is somewhat
// fitting how it uses macro magic.
//
// Since I need the size of the members and there
// can be a variable amount of members, macros are
// used to create the structs
//
// Tables will be tightly packed with parallel arrays
//
// First, a component must be created in global scope,
// this defines the component types.
//
// Second, a component must be registered with the
// context (specifically the component stack)
//
// ========================================

#define JEL_COMPONENT_MAX ~((JEL_ComponentInt) 0)

#define JEL_COMPONENT_MEMBERS_SIZES(type, name) \
  sizeof(type),

#define JEL_COMPONENT_CREATE(component, members, ...) \
  JEL_COMPONENT_STRUCT_CREATE(component, __VA_ARGS__) \
  JEL_COMPONENT_TABLE_CREATE(component, __VA_ARGS__) \
  struct JEL_ComponentInfo const component##_info = {.members_num = members, .members_sizes = (size_t []){JEL_COMPONENT_MEMBERS_ITERATE(JEL_COMPONENT_MEMBERS_SIZES, __VA_ARGS__)}}; \
  JEL_ComponentInt component##_id = 0;

#define JEL_COMPONENT_REGISTER(component)

#endif

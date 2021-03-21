#ifndef JEL_COMPONENT_H
#define JEL_COMPONENT_H

#include "component_types.h"
#include "component_struct.h"
#include "table/table.h"

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
// First, a component must be created in global scope,
// this defines the component types.
//
// Second, a component must be registered with the
// context
//
// ========================================

#define JEL_COMPONENT_MAX ~((JEL_ComponentInt) 0)

// Component Creation
#define JEL_COMPONENT_MEMBERS_SIZES_P(type, name) \
  sizeof(type),

#define JEL_COMPONENT_MEMBERS_SIZES_TOTAL_P(type, name) \
  sizeof(type) +

// JEL_COMPONENT_CREATE
// Creates:
// Struct, Table Fragment, Info
// TODO: The info should be in the fragment file
#define JEL_COMPONENT_CREATE(component, ...) \
  JEL_COMPONENT_STRUCT_CREATE_P(component, __VA_ARGS__) \
  JEL_TABLE_FRAGMENT_CREATE_P(component, __VA_ARGS__) \
  struct JEL_ComponentInfo const component##_info = { \
    .members_num = JEL_COMPONENT_MEMBERS_COUNT_P(__VA_ARGS__), \
    .members_sizes = (size_t []){JEL_COMPONENT_MEMBERS_ITERATE_P(JEL_COMPONENT_MEMBERS_SIZES_P, __VA_ARGS__)}, \
    .members_sizes_total = JEL_COMPONENT_MEMBERS_ITERATE_P(JEL_COMPONENT_MEMBERS_SIZES_TOTAL_P, __VA_ARGS__) 0, \
    .update_pointers = component##_update_pointers_p \
  }; \
  JEL_ComponentId component##_id = {0, 0, 0, 0};

// Component Registration
// TODO: This assumes JEL_ComponentId is a JEL_ComponentInt and that a byte is 8 bits
#define JEL_COMPONENT_REGISTER_REGISTER(component) \
  component##_id[JEL_context_current->components_registered / (sizeof(JEL_ComponentInt) * 8)] |= 1 << (JEL_context_current->components_registered % (sizeof(JEL_ComponentInt) * 8)); \
  ++JEL_context_current->components_registered;

#endif

#ifndef JEL_COMPONENT_H
#define JEL_COMPONENT_H

#include "component_types.h"
#include "component_struct.h"
#include "component_table.h"
#include "core.h"
#include "component_table_utility.h"

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

// Component Creation
#define JEL_COMPONENT_MEMBERS_SIZES_P(type, name) \
  sizeof(type),

#define JEL_COMPONENT_MEMBERS_SIZES_TOTAL_P(type, name) \
  sizeof(type) +

#define JEL_COMPONENT_CREATE(component, members, ...) \
  JEL_COMPONENT_STRUCT_CREATE_P(component, __VA_ARGS__) \
  JEL_COMPONENT_TABLE_CREATE_P(component, __VA_ARGS__) \
  struct JEL_ComponentInfo const component##_info = { \
    .members_num = members, \
    .members_sizes = (size_t []){JEL_COMPONENT_MEMBERS_ITERATE_P(JEL_COMPONENT_MEMBERS_SIZES_P, __VA_ARGS__)}, \
    .members_sizes_total = JEL_COMPONENT_MEMBERS_ITERATE_P(JEL_COMPONENT_MEMBERS_SIZES_TOTAL_P, __VA_ARGS__) 0 \
  }; \
  JEL_ComponentInt component##_id = 0;

// Component Registration
#define JEL_COMPONENT_REGISTER(component) \
  component##_id = JEL_context_current->component_stack->tables_num; \
  JEL_component_stack_tables_push( \
      JEL_context_current->component_stack, \
      JEL_component_table_create(sizeof(component##Table), &component##_info, component##Table_pointers_update) \
      );

#endif

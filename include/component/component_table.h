#ifndef JEL_COMPONENT_TABLE_H
#define JEL_COMPONENT_TABLE_H

#include "entity.h"
#include "component_types.h"
#include "component_table_utility.h"
#include "component_utility.h"

// ========================================
// 
// Component Table
//
// ========================================

// TODO: ComponentFragment is weird name, ComponentTableFragment is long, TableFragment?
// Header info for all fragments (private)
struct JEL_ComponentFragmentHead_P {
  struct JEL_ComponentInfo const *const info;
  void                           *buffer_start; // Where this fragment's portion of the table buffer begins
};

// Generic fragment type
struct JEL_ComponentFragment {
  struct JEL_ComponentFragmentHead_P head;
};

// Generic table type
struct JEL_ComponentTable {
  JEL_EntityInt                               allocated;
  JEL_EntityInt                               num;
  void                                       *buffer;
  JEL_ComponentInt             const          fragments_num;
  JEL_ComponentInt             const *const   fragments_ids;
  struct JEL_ComponentFragment const        **fragments;
};

// Struct that holds all tables
struct JEL_ComponentTables {
  JEL_ComponentInt            tables_allocated;
  JEL_ComponentInt            tables_num;
  struct JEL_ComponentTable **tables;
  JEL_ComponentId            *tables_ids; 
};

// ========================================
//
// Table Creation
//
// Creates the table fragment struct for a
// component, as well as the update
// pointers function
//
// ========================================

#define JEL_COMPONENT_FRAGMENT_MEMBERS_SET_P(type, name) \
  type *name;

#define JEL_COMPONENT_FRAGMENT_CREATE_P(component, ...) \
  struct component##Fragment { \
    struct JEL_ComponentFragmentHead_P head; \
    JEL_COMPONENT_MEMBERS_ITERATE_P(JEL_COMPONENT_FRAGMENT_MEMBERS_SET_P, __VA_ARGS__) \
  }; \
  \
  void component##_update_pointers_p(void *fragment, JEL_EntityInt allocated) \
  { \
    JEL_COMPONENT_FRAGMENT_POINTERS_UPDATE_P(component, __VA_ARGS__) \
  } \

// ========================================
//
// Table Registration
//
// Sets the component id of a component fragment
//
// ========================================

// TODO: Don't rely on JEL_ComponentId being an array of JEL_ComponentInt
// TODO: Don't rely on byte being 8 bits
#define JEL_COMPONENT_FRAGMENT_REGISTER_P(component) \
  component##_id[JEL_context_current->components_registered / (sizeof(JEL_ComponentInt) * 8)] |= 1 << (JEL_context_current->components_registered % (sizeof(JEL_ComponentInt) * 8)); \
  ++JEL_context_current->components_registered;

#endif

#ifndef COMPONENT_TABLE_H
#define COMPONENT_TABLE_H

#include "component_types.h"
#include "entity.h"
#include "component_utility.h"
#include <stdint.h>
#include <stddef.h>
#include "utility.h"
#include "component/component_table_utility.h"
#include "component_stack_utility.h"
#include "core.h"

// ========================================
// 
// Component Table
//
// The 'database' for all the component data
//
// Creating a table creates types
//
// How 'generic' tables work
// Every table has a JEL_ComponentTableHead struct
// as its first member, and the idea is to cast
// all void pointers (which point to a valid table)
// into a JEL_ComponentTableGeneric, which has the
// head as the first member. The downside is I lose
// some struct packing, but the reward is as it's the
// first element, I don't need to worry about alignment
// so I can always ensure this works.
//
// ========================================

struct JEL_ComponentTableHead {
  JEL_EntityInt                    allocated;
  JEL_EntityInt                    num;
  void                            *buffer;
  void                           (*update_pointers)(void *);
  struct JEL_ComponentInfo const  *info;
};

struct JEL_ComponentTableGeneric {
  struct JEL_ComponentTableHead head;
};

// ========================================
//  Creating a Table
// ========================================
#define JEL_COMPONENT_TABLE_MEMBERS_SET(type, name) \
  type *name;

// Amazing naming right here
#define JEL_COMPONENT_TABLE_MEMBERS_UPDATE_POINTERS_SET(type, name) \
  *name

#define JEL_COMPONENT_TABLE_CREATE(component, ...) \
  struct component##Table { \
    struct JEL_ComponentTableHead head; \
    JEL_COMPONENT_MEMBERS_ITERATE(JEL_COMPONENT_TABLE_MEMBERS_SET, __VA_ARGS__) \
  }; \
  \
  void component##Table_update_pointers(void *table) \
  { \
    JEL_COMPONENT_TABLE_UPDATE_POINTERS(component, __VA_ARGS__) \
  }

#define JEL_COMPONENT_TABLE_GET(component) \
  ((struct component##Table *) JEL_context_current->component_stack->tables[component##_id])

#endif

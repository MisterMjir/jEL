#ifndef COMPONENT_TABLE_H
#define COMPONENT_TABLE_H

#include "component_types.h"
#include "entity.h"
#include "component_utility.h"
#include <stdint.h>
#include <stddef.h>
#include "utility.h"
#include "component/component_table_utility.h"

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

struct JEL_ComponentInfo {
  uint8_t             members_num;
  size_t const *const members_sizes;
};

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
  void JEL_##component##Table_update_pointers(void *table) \
  { \
    JEL_COMPONENT_TABLE_UPDATE_POINTERS(component, __VA_ARGS__) \
  }

#endif

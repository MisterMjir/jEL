#ifndef JEL_COMPONENT_TABLE_H
#define JEL_COMPONENT_TABLE_H

#include "component_types.h"
#include "entity.h"
#include "component_utility.h"
#include <stdint.h>
#include <stddef.h>
#include "utility.h"
#include "component/component_table_utility.h"
#include "component_stack_utility.h"
#include "core.h"
#include "error.h"

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
  void                           (*pointers_update)(void *);
  struct JEL_ComponentInfo const  *info;
};

struct JEL_ComponentTableGeneric {
  struct JEL_ComponentTableHead head;
};

// ========================================
//  Creating a Table
//
//  CRUD Operations
//  ---------------
//  Add    (Create)
//  Get    (Read)
//  Set    (Update)
//  Delete (Delete
//  ---------------
//  add and update without a member before
//  it assumes it's for a struct
// ========================================
#define JEL_COMPONENT_TABLE_MEMBERS_SET_P(type, name) \
  type *name;

#define JEL_COMPONENT_TABLE_ADD_SET_P(type, name) \
  table->name[table->head.num] = c.name; \

#define JEL_COMPONENT_TABLE_GET_SET_P(type, name) \
  .name = table->name[index],

#define JEL_COMPONENT_TABLE_MEMBER_GET_SET_P(component, type, name) \
  type component##Table_##name##_get(void *table_v, JEL_EntityInt index) \
  { \
    struct component##Table *table = (struct component##Table *) table_v; \
    return table->name[index]; \
  }

#define JEL_COMPONENT_TABLE_SET_SET_P(type, name) \
  table->name[index] = c.name;

#define JEL_COMPONENT_TABLE_MEMBER_SET_SET_P(component, type, name) \
  void component##Table_##name##_set(void *table_v, JEL_EntityInt index, type value) \
  { \
    struct component##Table *table = (struct component##Table *) table_v; \
    table->name[index] = value; \
  }

#define JEL_COMPONENT_TABLE_DELETE_SET_P(type, name) \
  table->name[index] = table->name[table->head.num - 1];

#define JEL_COMPONENT_TABLE_CREATE_P(component, ...) \
  struct component##Table { \
    struct JEL_ComponentTableHead head; \
    JEL_COMPONENT_MEMBERS_ITERATE_P(JEL_COMPONENT_TABLE_MEMBERS_SET_P, __VA_ARGS__) \
  }; \
  \
  void component##Table_pointers_update(void *table) \
  { \
    JEL_COMPONENT_TABLE_POINTERS_UPDATE_P(component, __VA_ARGS__) \
  } \
  \
  int component##Table_add(void *table_v, struct component c) \
  { \
    struct component##Table *table = (struct component##Table *) table_v; \
    if (table->head.allocated <= table->head.num) \
    { \
      if (JEL_component_table_allocate(table_v, table->head.allocated * 1.618)) { \
        struct JEL_Error e = {"Could not allocated components in component table add", -1}; \
        JEL_error_push(e); \
        return -1; \
      } \
    } \
    \
    JEL_COMPONENT_MEMBERS_ITERATE_P(JEL_COMPONENT_TABLE_ADD_SET_P, __VA_ARGS__) \
    \
    ++table->head.num; \
    return 0; \
  } \
  \
  struct component component##Table_get(void *table_v, JEL_EntityInt index) \
  { \
    struct component##Table *table = (struct component##Table *) table_v; \
    struct component c = {JEL_COMPONENT_MEMBERS_ITERATE_P(JEL_COMPONENT_TABLE_GET_SET_P, __VA_ARGS__)}; \
    return c; \
  } \
  \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_ITERATE_P(JEL_COMPONENT_TABLE_MEMBER_GET_SET_P, component, __VA_ARGS__) \
  \
  void component##Table_set(void *table_v, JEL_EntityInt index, struct component c) \
  { \
    struct component##Table *table = (struct component##Table *) table_v; \
    JEL_COMPONENT_MEMBERS_ITERATE_P(JEL_COMPONENT_TABLE_SET_SET_P, __VA_ARGS__) \
  } \
  \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_ITERATE_P(JEL_COMPONENT_TABLE_MEMBER_SET_SET_P, component, __VA_ARGS__) \
  \
  void component##Table_delete(void *table_v, JEL_EntityInt index) \
  { \
    struct component##Table *table = (struct component##Table *) table_v; \
    JEL_COMPONENT_MEMBERS_ITERATE_P(JEL_COMPONENT_TABLE_DELETE_SET_P, __VA_ARGS__) \
    --table->head.num; \
  }

// Utility/Easier Table Macros (Table must be registered for this!)

#define JEL_COMPONENT_TABLE_GET(component) \
  ((struct component##Table *) JEL_context_current->component_stack->tables[component##_id])

#define JEL_COMPONENT_TABLE_DATA_ADD(component, value) \
  component##Table_add(JEL_COMPONENT_TABLE_GET(component), value)

#define JEL_COMPONENT_TABLE_DATA_GET(component, index) \
  component##Table_get(JEL_COMPONENT_TABLE_GET(component), index)

#define JEL_COMPONENT_TABLE_MEMBER_DATA_GET(component, member, index) \
  component##Table_##member##_get(JEL_COMPONENT_TABLE_GET(component), index)

#define JEL_COMPONENT_TABLE_DATA_SET(component, index, value) \
  component##Table_set(JEL_COMPONENT_TABLE_GET(component), value)

#define JEL_COMPONENT_TABLE_MEMBER_DATA_SET(component, member, index, value) \
  component##Table_##member##_set(JEL_COMPONENT_TABLE_GET(component), index, value)

#define JEL_COMPONENT_TABLE_DATA_DELETE(component, index) \
  component##Table_delete(JEL_COMPONENT_TABLE_GET(component), index)

#endif

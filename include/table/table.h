#ifndef JEL_TABLE_H
#define JEL_TABLE_H

#include "entity.h"
#include "component/component_types.h"
#include "fragment.h"
#include "component/component_utility.h"

// ========================================
//
// Tables
//
// Entities are primary keys, components are
// data, and the data is further organized
// into table fragments
//
// ========================================

// Generic table struct
// TODO: Some of this stuff could be const
struct JEL_Table {
  JEL_EntityInt         allocated;
  JEL_EntityInt         num; // Num is like entries
  void                 *buffer;
  JEL_ComponentInt      fragments_num;
  JEL_TypeIndex        *fragments_types;
  struct JEL_Fragment **fragments;
};

// Table stack, holds pointers to all the tables
struct JEL_TableStack {
  JEL_ComponentInt   tables_allocated;
  JEL_ComponentInt   tables_num;
  struct JEL_Table **tables;
  JEL_Type          *tables_types;
};

// Utility
struct JEL_Table * JEL_table_get(JEL_Type);

#define JEL_ID_SET_HELPER_P(component) id[component##_id / 32] |= 1 << (component##_id % 32);

#define JEL_ID_SET(id, ...) \
  JEL_COMPONENTS_ITERATE_P(JEL_ID_SET_HELPER_P, __VA_ARGS__)

#define JEL_TABLE_GET(table, ...) \
{ \
  JEL_Type id = {0, 0, 0, 0}; \
  JEL_ID_SET(id, __VA_ARGS__) \
  table = JEL_table_get(id); \
} \

#endif

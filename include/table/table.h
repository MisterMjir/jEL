#ifndef JEL_TABLE_H
#define JEL_TABLE_H

#include "entity.h"
#include "component/component_types.h"
#include "table_fragment.h"

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
struct JEL_ComponentTable {
  JEL_EntityInt                           allocated;
  JEL_EntityInt                           num; // Num is like entries
  void                                   *buffer;
  JEL_ComponentInt         const          fragments_num;
  JEL_ComponentId          const *const   fragments_ids;
  struct JEL_TableFragment const        **fragments;
};

// Table stack, holds pointers to all the tables
struct JEL_TableStack {
  JEL_ComponentInt   tables_allocated;
  JEL_ComponentInt   tables_num;
  struct JEL_Table **tables;
  JEL_ComponentId   *tables_ids;
};

#endif

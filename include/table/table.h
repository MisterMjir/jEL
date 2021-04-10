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

// These functions are all from table_utility.h
struct JEL_Table *      JEL_table_create_p(JEL_ComponentInt, ...);
struct JEL_Table *      JEL_table_create_type_p(JEL_Type);
int                     JEL_table_destroy_p(struct JEL_Table *);

int                     JEL_table_add_p(struct JEL_Table *, ...);
int                     JEL_table_add_buffer_p(struct JEL_Table *, void *);
// TODO: Remove entity and remove index, so there is a faster version if there's more info
int                     JEL_table_remove_p(struct JEL_Table *, JEL_Entity);

JEL_EntityInt           JEL_table_index_get_p(struct JEL_Table *, JEL_Entity);

int                     JEL_table_row_move_p(struct JEL_Table *, JEL_Entity, struct JEL_Table *);

int                     JEL_table_allocate_p(struct JEL_Table *, JEL_EntityInt);

struct JEL_TableStack * JEL_table_stack_create_p(void);
int                     JEL_table_stack_destroy_p(struct JEL_TableStack *);

int                     JEL_table_stack_push_p(struct JEL_Table *);

int                     JEL_table_stack_allocate_p(struct JEL_TableStack *, JEL_ComponentInt);

// Back to non table_utility.h
#define JEL_ID_SET_HELPER_P(component) id[component##_id / 32] |= 1 << (component##_id % 32);

#define JEL_ID_SET(id, ...) \
  JEL_COMPONENTS_ITERATE_P(JEL_ID_SET_HELPER_P, __VA_ARGS__)

#define JEL_TABLE_GET(table, ...) \
{ \
  JEL_Type id = {0, 0, 0, 0}; \
  JEL_ID_SET(id, __VA_ARGS__); \
  table = JEL_table_get(id); \
} \

#define JEL_FRAGMENT_GET(fragment, table, component) \
{ \
  for (int i = 0; i < table->fragments_num; ++i) { \
    if (table->fragments_types[i] == component##_id) {  \
      fragment = (component##Fragment *) table->fragments[i]; \
      break; \
    } \
  } \
}

// TODO: Type could be an array of 8 or something
#define JEL_ID_SET_ARG_P(type, ...) \
{ \
  JEL_Type id = {type[0], type[1], type[2], type[3]}; \
  JEL_ID_SET(id, __VA_ARGS__); \
  type[0] = id[0]; \
  type[1] = id[1]; \
  type[2] = id[2]; \
  type[3] = id[3]; \
}

#define JEL_ENTITY_ADD(entity, ...) \
{ \
  struct JEL_Table *old_table = JEL_table_get(JEL_context_current->entity_manager->types[JEL_entity_index_get(entity)]); \
  JEL_ID_SET_ARG_P(JEL_context_current->entity_manager->types[JEL_entity_index_get(entity)], __VA_ARGS__); \
  struct JEL_Table *new_table = JEL_table_get(JEL_context_current->entity_manager->types[JEL_entity_index_get(entity)]); \
  if (new_table == NULL) { \
    new_table = JEL_table_create_type_p(JEL_context_current->entity_manager->types[JEL_entity_index_get(entity)]); \
    JEL_table_stack_push_p(new_table); \
  } \
  JEL_table_row_move_p(old_table, entity, new_table); \
}

#endif

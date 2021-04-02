#include "table_utility.h"
#include <stdlib.h>
#include "error.h"
#include "core.h"
#include <string.h>
#include <stdarg.h>

// ========================================
// JEL_table_create_p
//
// @param types_num
//   The number of types for the table
// @param ...
//   Component type indicies
// ========================================
struct JEL_Table * JEL_table_create_p(JEL_ComponentInt types_num, ...)
{
  va_list types;

  va_start(types, types_num);

  const int initial_count = 8;

  // Malloc and set non-bufffer/allocated members
  struct JEL_Table *new_table = malloc(sizeof(struct JEL_Table));
  new_table->fragments_num = types_num;
  new_table->fragments_types = malloc(types_num * sizeof(JEL_TypeIndex));
  new_table->fragments = malloc(types_num * sizeof(struct JEL_TableFragment *));

  for (int i = 0; i < types_num; ++i) {
    JEL_TypeIndex type = va_arg(types, JEL_TypeIndex);

    new_table->fragments_types[i] = type;
    new_table->fragments[i] = malloc(JEL_context_current->component_stack->table_fragments_sizes[type]);

    new_table->fragments[i]->head.buffer_start = NULL;
    new_table->fragments[i]->head.info = JEL_context_current->component_stack->fragments_infos[type];
  }

  // Allocate the table
  size_t total_size = 0;
  for (int i = 0; i < new_table->fragments_num; ++i) {
    total_size += new_table->fragments[i]->head.info->members_sizes_total;
  }

  new_table->buffer = malloc(initial_count * total_size);
  new_table->allocated = initial_count;
  new_table->num = 0;

  // Set fragment buffer_start and pointers
  void *buffer_start = new_table->buffer;
  for (int i = 0; i < new_table->fragments_num; ++i) {
    new_table->fragments[i]->head.buffer_start = buffer_start;

    new_table->fragments[i]->head.info->update_pointers(new_table->fragments[i], new_table->allocated);

    buffer_start += new_table->allocated * new_table->fragments[i]->head.info->members_sizes_total;
  }

  va_end(types);

  return new_table;
}

// ========================================
// JEL_table_destroy_p
// ========================================
int JEL_table_destroy_p(struct JEL_Table *table)
{
  // TODO: free buffer
  for (int i = 0; i < table->fragments_num; ++i) {
    free(table->fragments[i]);
  }

  free(table->fragments_types);
  free(table->fragments);

  free(table->buffer);

  free(table);

  return 0;
}

// ========================================
// JEL_component_tables_create_p
//
// @desc
//   Creates a JEL_ComponentTables, or
//   a container for "JEL_ComponentTable"s
// @return
//   A pointer to a JEL_ComponentTables,
//   NULL on failure
// ========================================
struct JEL_TableStack * JEL_table_stack_create_p(void)
{
  struct JEL_TableStack *new_component_tables;
  const int initial_count = 8; 

  if (!(new_component_tables = malloc(sizeof(struct JEL_TableStack)))) {
    // TODO: Error stuff
    return NULL;
  }

  // Allocate initial_count tables
  if (!(new_component_tables->tables = malloc(initial_count * sizeof(struct JEL_TableStack)))) {
    // TODO: Error stuff
    return NULL;
  }

  // Allocate initial_count ids
  if (!(new_component_tables->tables_types = malloc(initial_count * sizeof(struct JEL_TableStack)))) {
    // TODO: Error stuff
    return NULL;
  }

  new_component_tables->tables_allocated = initial_count;
  new_component_tables->tables_num = 0;

  return new_component_tables;
}

// ========================================
// JEL_table_stack_push_p
//
// @desc
//   Adds a table to the stack
// @return
//   0 on success
// ========================================
int JEL_table_stack_push_p(struct JEL_Table *table)
{
  if (JEL_context_current->table_stack->tables_allocated <= JEL_context_current->table_stack->tables_num) {
    if (JEL_table_stack_allocate_p(JEL_context_current->table_stack, JEL_context_current->table_stack->tables_allocated * 1.618)) {
      return -2;
    }
  }

  JEL_context_current->table_stack->tables[JEL_context_current->table_stack->tables_num] = table;

  // Set the id of the table
  JEL_Type table_type = {0, 0, 0, 0};
  for (int i = 0; i < table->fragments_num; ++i) {
    JEL_type_index_add(table_type, table->fragments_types[i]);
  }

  memcpy(JEL_context_current->table_stack->tables_types[JEL_context_current->table_stack->tables_num], table_type, sizeof(JEL_Type));

  ++(JEL_context_current->table_stack->tables_num);

  return 0;
}

// ========================================
// JEL_component_tables_destroy_p
//
// @desc
//   Destroys a JEL_ComponentTables
// @return
//   0 on success
// ========================================
int JEL_table_stack_destroy_p(struct JEL_TableStack *tables)
{
  for (JEL_ComponentInt i = 0; i < tables->tables_num; ++i) {
    JEL_table_destroy_p(tables->tables[i]);
  }

  free(tables->tables);
  free(tables->tables_types);

  free(tables);

  return 0;
}

// ========================================
// JEL_table_stack_allocate_p
// ========================================
int JEL_table_stack_allocate_p(struct JEL_TableStack *ts, JEL_ComponentInt count)
{
  if (count <= ts->tables_allocated)
    return -1;

  struct JEL_Table **new_tables;
  JEL_Type          *new_types;

  if (!(new_tables = malloc(count * sizeof(struct JEL_Table *)))) {
    return -2;
  }

  if (!(new_types = malloc(count * sizeof(JEL_Type)))) {
    return -2;
  }

  memcpy(new_tables, ts->tables, ts->tables_num * sizeof(struct JEL_Table *));
  free(ts->tables);
  ts->tables = new_tables;

  memcpy(new_types, ts->tables_types, ts->tables_num * sizeof(JEL_Type));
  free(ts->tables_types);
  ts->tables_types = new_types;

  return 0;
}

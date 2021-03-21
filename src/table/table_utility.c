#include "table_utility.h"
#include <stdlib.h>
#include "error.h"

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
  if (!(new_component_tables->tables_ids = malloc(initial_count * sizeof(struct JEL_TableStack)))) {
    // TODO: Error stuff
    return NULL;
  }

  new_component_tables->tables_allocated = initial_count;
  new_component_tables->tables_num = 0;

  return new_component_tables;
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
    free(tables->tables[i]);
  }

  free(tables->tables);
  free(tables->tables_ids);

  free(tables);

  return 0;
}

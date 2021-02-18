#include "component/component_table_utility.h"
#include "component/component_table.h"
#include <stdlib.h>

// TODO: All of this stuff

// ========================================
// JEL_component_table_create
//
// @desc
//   Creates a component table
// @return
//   The newly create component table
//   NULL on failure
// ========================================
void * JEL_component_table_create(size_t size)
{
  

  return NULL;
}

// ========================================
// JEL_component_table_destroy
//
// @desc
//   Frees a component table
// @param table
//   The table to destroy
// @return
//   0 on success
// ========================================
int JEL_component_table_destroy(void *table)
{
  struct JEL_ComponentTableGeneric *table_g = table;

  free(table_g->head.buffer); 

  free(table);

  return 0;
}

// ========================================
// JEL_component_table_allocate
//
// @desc
//   Allocates more data for a component table
// @param table
//   The table
// @param count
//   How much to allocate
// @param update_pointers
//   Function that updates the table's pointer
// @return
//   0 on success
// ========================================
int JEL_component_table_allocate(void *table, JEL_EntityInt count, void (*update_pointers)(void *))
{
  return 0;
}

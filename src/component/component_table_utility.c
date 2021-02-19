#include "component/component_table_utility.h"
#include "component/component_table.h"
#include <stdlib.h>
#include "error.h"
#include <string.h>

// ========================================
// JEL_component_table_create
//
// @desc
//   Creates a component table
// @param size
//   Size of the table being created
// @param component_info
//   The table's JEL_ComponentInfo
// @param pointers_update
//   Table's update pointers function
// @return
//   The newly create component table
//   NULL on failure
// ========================================
void * JEL_component_table_create(size_t size, struct JEL_ComponentInfo const *component_info, void (*pointers_update)(void *))
{ 
  const int initial_count = 8;

  struct JEL_ComponentTableGeneric *new_component_table;
  if (!(new_component_table = malloc(size))) {
    struct JEL_Error e = {"Could not allocate JEL_ComponentTableGeneric", -1};
    JEL_error_push(e);
    return NULL;
  }

  // Set component info
  new_component_table->head.info = component_info;

  // Initialize buffer
  if (!(new_component_table->head.buffer = malloc(component_info->members_sizes_total * initial_count))) {
    struct JEL_Error e = {"Could not allocate JEL_ComponentTableGeneric buffer", -1};
    JEL_error_push(e);
    return NULL;
  }
  new_component_table->head.allocated = 8;
  new_component_table->head.num = 1;

  // Set update pointers, and call because of an allocation
  new_component_table->head.pointers_update = pointers_update;
  pointers_update(new_component_table);

  return new_component_table;
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
// @param pointers_update
//   Function that updates the table's pointer
// @return
//    0 on success
//   -1 if there is already enough memory
//   -2 if malloc failed
// ========================================
int JEL_component_table_allocate(void *table, JEL_EntityInt count)
{
  struct JEL_ComponentTableGeneric *table_g = table;

  if (count <= table_g->head.allocated) {
    return -1;
  }

  void *new_buffer;

  if (!(new_buffer = malloc(count * table_g->head.info->members_sizes_total))) {
    struct JEL_Error e = {"Could not allocate JEL_ComponentTableGeneric buffer", -1};
    JEL_error_push(e);
    return -2;
  }

  // Copying elements
  //
  // Keep two pointers, one for the new and old buffers
  // Increase old buffer by sizeof the ith element * allocated
  // Increase new buffer by sizeof the ith element * count
  u_int8_t *nb = new_buffer;
  u_int8_t *ob = table_g->head.buffer;
  for (int i = 0; i < table_g->head.info->members_num; ++i) {
    memcpy(nb, ob, table_g->head.info->members_sizes[i] * table_g->head.num);
    ob += table_g->head.info->members_sizes[i] * table_g->head.allocated;
    nb += table_g->head.info->members_sizes[i] * count;
  }
  free(table_g->head.buffer);
  table_g->head.buffer = new_buffer;

  table_g->head.allocated = count;

  table_g->head.pointers_update(table);

  return 0;
}

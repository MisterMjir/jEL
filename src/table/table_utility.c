#include "table_utility.h"
#include <stdlib.h>
#include "error.h"
#include "core.h"
#include <string.h>
#include <stdarg.h>
#include <stdint.h>

/* TABLES */

/*
 * JEL_table_create_p
 *
 * @param types_num
 *   The number of types for the table
 * @param ...
 *   Component type indicies
 * @return
 *   Newly created table
 */
struct JEL_Table * JEL_table_create_p(JEL_ComponentInt types_num, ...)
{
  va_list types;

  va_start(types, types_num);

  const int initial_count = 8;

  /* Malloc and set non-bufffer/allocated members */
  struct JEL_Table *new_table = malloc(sizeof(struct JEL_Table));
  new_table->fragments_num = types_num;
  new_table->fragments_types = malloc(types_num * sizeof(JEL_TypeIndex));
  new_table->fragments = malloc(types_num * sizeof(struct JEL_TableFragment *));

  for (int i = 0; i < types_num; ++i) {
    JEL_TypeIndex type = va_arg(types, JEL_TypeIndex);

    new_table->fragments_types[i] = type;
    new_table->fragments[i] = malloc(JEL_context_current->component_stack->fragments_sizes[type]);

    new_table->fragments[i]->head.buffer_start = NULL;
    new_table->fragments[i]->head.info = JEL_context_current->component_stack->fragments_infos[type];
  }

  /* Allocate the table */
  size_t total_size = 0;
  for (int i = 0; i < new_table->fragments_num; ++i) {
    total_size += new_table->fragments[i]->head.info->members_sizes_total;
  }

  new_table->buffer = malloc(initial_count * total_size);
  new_table->allocated = initial_count;
  new_table->num = 0;

  /* Set fragment buffer_start and pointers */
  int8_t *buffer_start = new_table->buffer;
  for (int i = 0; i < new_table->fragments_num; ++i) {
    new_table->fragments[i]->head.buffer_start = buffer_start;

    new_table->fragments[i]->head.info->update_pointers(new_table->fragments[i], new_table->allocated);

    buffer_start += new_table->allocated * new_table->fragments[i]->head.info->members_sizes_total;
  }

  va_end(types);

  return new_table;
}

/*
 * JEL_table_create_type_p
 *
 * @desc
 *   Same as above but with a type instead of
 *   variadic parameters
 * @param t
 *   Type of table to create
 * @return
 *   Newly created struct
 */
struct JEL_Table * JEL_table_create_type_p(JEL_Type t)
{
  const int initial_count = 8;

  JEL_ComponentInt types_num = 0;
  for (int i = 0; i < JEL_TYPE_INTS; ++i) {
    /* TODO: Assumes a byte is 8 bits */
    for (int j = 0; j < sizeof(JEL_Type) / JEL_TYPE_INTS * 8; ++j) {
      if ((t[i] & (1 << j)) > 0) {
        ++types_num;
      }
    }
  }

  JEL_TypeIndex *types; /* Array of Type Indicies */
  types = malloc(types_num * sizeof(JEL_TypeIndex));

  {
    int i = 0;
    for (int j = 0; j < JEL_TYPE_INTS; ++j) {
      /* TODO: Assumes a byte is 8 bits */
      for (int k = 0; k < sizeof(JEL_Type) / JEL_TYPE_INTS * 8; ++k) {
        if ((t[j] & (1 << k)) > 0) {
          types[i++] = j * (sizeof(JEL_Type) / JEL_TYPE_INTS) + k;
        }
      }
    }
  }

  /* Malloc and set non-bufffer/allocated members */
  struct JEL_Table *new_table = malloc(sizeof(struct JEL_Table));
  new_table->fragments_num = types_num;
  new_table->fragments_types = malloc(types_num * sizeof(JEL_TypeIndex));
  new_table->fragments = malloc(types_num * sizeof(struct JEL_TableFragment *));

  for (int i = 0; i < types_num; ++i) {
    JEL_TypeIndex type = types[i];

    new_table->fragments_types[i] = type;
    new_table->fragments[i] = malloc(JEL_context_current->component_stack->fragments_sizes[type]);

    new_table->fragments[i]->head.buffer_start = NULL;
    new_table->fragments[i]->head.info = JEL_context_current->component_stack->fragments_infos[type];
  }

  free(types);

  /* Allocate the table */
  size_t total_size = 0;
  for (int i = 0; i < new_table->fragments_num; ++i) {
    total_size += new_table->fragments[i]->head.info->members_sizes_total;
  }

  new_table->buffer = malloc(initial_count * total_size);
  new_table->allocated = initial_count;
  new_table->num = 0;

  /* Set fragment buffer_start and pointers */
  int8_t *buffer_start = new_table->buffer;
  for (int i = 0; i < new_table->fragments_num; ++i) {
    new_table->fragments[i]->head.buffer_start = buffer_start;

    new_table->fragments[i]->head.info->update_pointers(new_table->fragments[i], new_table->allocated);

    buffer_start += new_table->allocated * new_table->fragments[i]->head.info->members_sizes_total;
  }

  return new_table;
}

/*
 * JEL_table_destroy_p
 *
 * @desc
 *   Cleans up a destroyed table
 * @param table
 *   Table to destroy
 * @return
 *   0 on success
 */
int JEL_table_destroy_p(struct JEL_Table *table)
{
  for (int i = 0; i < table->fragments_num; ++i) {
    free(table->fragments[i]);
  }

  free(table->fragments_types);
  free(table->fragments);

  free(table->buffer);

  free(table);

  return 0;
}

/*
 * JEL_table_add_p
 *
 * @desc
 *   Adds stuff to table
 * @param table
 *   Table to add stuff to
 * @param ...
 *   A list of values of all fragments'
 *   members, in order of table's > fragment's >
 *   members
 * TODO: This va_arg stuff doesn't work
 */
int JEL_table_add_p(struct JEL_Table *table, ...)
{
  va_list args;

  va_start(args, table);

  if (table->allocated <= table->num) {
    if (JEL_table_allocate_p(table, table->allocated * 1.618)) {
      return -1;
    }
  }

  for (int i = 0; i < table->fragments_num; ++i) {
    int8_t *bp = table->fragments[i]->head.buffer_start;

    for (int j = 0; j < table->fragments[i]->head.info->members_num; ++j) {
      size_t member_size = table->fragments[i]->head.info->members_sizes[j];
      
      void *np = (uint8_t *) bp + table->num * member_size;
      /* TODO: Below is wrong */
      int data = va_arg(args, int); /* The type doesn't matter */

      memcpy(np, &data, member_size);

      bp += member_size * table->allocated;
    }
  }

  ++table->num;

  va_end(args);

  return 0;
}

/*
 * JEL_table_add_buffer_p
 *
 * @desc
 *   Adds stuff to a table
 * @param table
 *   Table to add stuff to
 * @param buffer
 *   Pointer to buffer with the data to add,
 *   data must match and be contiguous
 * @return
 *    0 on success
 *   -1 if allocate fails
 */
int JEL_table_add_buffer_p(struct JEL_Table *table, void *buffer)
{
  if (table->allocated <= table->num) {
    if (JEL_table_allocate_p(table, table->allocated * 1.618)) {
      struct JEL_Error e = {"Cannot allocate table in table_add_buffer_p", JEL_ERROR_ALLOCATE};
      JEL_error_push(e);
      return JEL_ERROR_ALLOCATE;
    }
  }

  int8_t *bp = buffer;
  for (int i = 0; i < table->fragments_num; ++i) {
    int8_t *fbp = table->fragments[i]->head.buffer_start;

    for (int j = 0; j < table->fragments[i]->head.info->members_num; ++j) {
      size_t member_size = table->fragments[i]->head.info->members_sizes[j];

      int8_t *np = fbp + table->num * member_size;
      
      memcpy(np, bp, member_size);

      fbp += member_size * table->allocated;
      bp += member_size;
    }
  }

  ++table->num;
  
  return 0;
}

/*
 * JEL_table_remove_p
 *
 * @desc
 *   Removes a row from the table
 * @param table
 *   The table to have a row removed
 * @param entity
 *   The key of the row to remove, which
 *   is the row which matches the entity
 * @return
 *    0 on success
 *   -1 if entity is not in the table
 */
int JEL_table_remove_p(struct JEL_Table *table, JEL_Entity entity)
{
  JEL_EntityInt index = JEL_table_index_get_p(table, entity); /* Index is the row */

  for (int i = 0; i < table->fragments_num; ++i) {
    int8_t *buffer = table->fragments[i]->head.buffer_start;
    for (int j = 0; j < table->fragments[i]->head.info->members_num; ++j) {
      size_t member_size = table->fragments[i]->head.info->members_sizes[j];

      /* Buffer start + offset is the beginning of the fragment's member's memory */
      /* i is the index of the entity to remove */
      memcpy(buffer + member_size * index,
             buffer + member_size * (table->num - 1),
             member_size);

      buffer += member_size * table->allocated;
    }

    --table->num;

    return 0;
  }

  return -1;
}

/*
 * JEL_table_index_get_p
 *
 * TODO: Big structural problem
 *   Index can be 0, fix by having first row
 *   in table be for NULL entities
 * @desc
 *   Get index of entity in a table
 * @param table
 *   Table to check
 * @param entity
 *   Entity to check
 * @return
 *   the row index
 */
JEL_EntityInt JEL_table_index_get_p(struct JEL_Table *table, JEL_Entity entity)
{
  for (JEL_EntityInt i = 0; i < table->num; ++i) {
    if (((JEL_Entity *) table->buffer)[i] == entity) {
      return i;
    }
  }

  return 0;
}

/*
 * JEL_table_row_move_p
 *
 * @desc
 *   Moves a row from a table to a table
 * @param src
 *   The src table, old table, copy data
 *   from
 * @param key
 *   Entity of the row to move
 * @param dest
 *   The dest table, new table, copy data
 *   to
 * @return
 *   0 on success
 */
int JEL_table_row_move_p(struct JEL_Table *src, JEL_Entity key, struct JEL_Table *dest)
{
  /* TODO: Check if types match */
  JEL_EntityInt index = JEL_table_index_get_p(src, key);
  /* if (index == 0) */
    /* return -1; */

  /*
   * Loop through dest fragments
   * If dest has the fragment cool, copy it
   * If not, use 0
   * Make sure to remove from dest table
   */

  size_t total_size = 0;
  for (int i = 0; i < dest->fragments_num; ++i) {
    total_size += dest->fragments[i]->head.info->members_sizes_total;
  }

  int8_t *buffer;
  if (!(buffer = malloc(total_size))) {
    /* TODO: Error stuff */
    return JEL_ERROR_MALLOC;
  }

  int8_t *bp = buffer;

  /* Loop through dest fragments */
  for (int dest_fragment_index = 0; dest_fragment_index < dest->fragments_num; ++dest_fragment_index) {
    int matched = 0;
    /* Loop through all src fragments */
    for (int src_fragment_index = 0; src_fragment_index < src->fragments_num; ++src_fragment_index) {
      /* Check if the ith source fragment is the same type as the ith dest fragment */
      if (src->fragments_types[src_fragment_index] == dest->fragments_types[dest_fragment_index]) {
        matched = 1;
        int8_t *cp = src->fragments[src_fragment_index]->head.buffer_start; /* Pointer to beginning of fragment's member's memory */
        /* Loop through all the fragment members */
        for (int i = 0; i < src->fragments[src_fragment_index]->head.info->members_num; ++i) {
          size_t member_size = src->fragments[src_fragment_index]->head.info->members_sizes[i];

          memcpy(bp, cp + index * member_size, member_size);

          bp += member_size;
          cp += member_size * src->allocated;
        }

        break;
      }
    }
    if (!matched) {
      bp += dest->fragments[dest_fragment_index]->head.info->members_sizes_total;
    }
  }

  JEL_table_add_buffer_p(dest, buffer);
  JEL_table_remove_p(src, key);

  free(buffer);

  return 0;
}

/*
 * JEL_table_allocate_p
 *
 * @desc
 *   Allocates more memory for a table,
 *   updates all the fragment pointers
 * @param table
 *   Table to allocate
 * @param count
 *   How many entitities/rows to allocate
 * @return
 *    0 on success
 *   -1 if there is enough memory
 *   -2 if malloc fails
 */
int JEL_table_allocate_p(struct JEL_Table *table, JEL_EntityInt count)
{
  if (count <= table->allocated) {
    return -1;
  }

  int8_t *new_buffer;

  size_t row_size = 0;
  for (int i = 0; i < table->fragments_num; ++i) {
    row_size += table->fragments[i]->head.info->members_sizes_total;
  }

  if (!(new_buffer = malloc(count * row_size))) {
    struct JEL_Error e = {"Cannot malloc a table buffer in table_allocate", JEL_ERROR_MALLOC};
    JEL_error_push(e);
    return JEL_ERROR_MALLOC;
  }

  /*
   * Copying is kinda complicated
   * Pointer to buffer location
   * Loop through fragments
   * Loop through each member
   */

  int8_t *bp = new_buffer;    /* New buffer pointer */
  int8_t *op = table->buffer; /* Old buffer pointer */

  for (int i = 0; i < table->fragments_num; ++i) {
    table->fragments[i]->head.buffer_start = bp;

    for (int j = 0; j < table->fragments[i]->head.info->members_num; ++j) {
      size_t member_size = table->fragments[i]->head.info->members_sizes[j];

      memcpy(bp, op, table->num * member_size);

      bp += count * member_size;
      op += table->allocated * member_size;
    }

    table->fragments[i]->head.info->update_pointers(table->fragments[i], count);
  }

  free(table->buffer);
  table->buffer = new_buffer;

  table->allocated = count;

  return 0;
}

/* TABLE STACK */

/*
 * JEL_table_stack_create_p
 *
 * @desc
 *   Creates a JEL_ComponentTables, or
 *   a container for "JEL_ComponentTable"s
 * @return
 *   A pointer to a JEL_ComponentTables,
 *   NULL on failure
 */
struct JEL_TableStack * JEL_table_stack_create_p(void)
{
  struct JEL_TableStack *new_component_tables;
  const int initial_count = 8; 

  if (!(new_component_tables = malloc(sizeof(struct JEL_TableStack)))) {
    /* TODO: Error stuff */
    return NULL;
  }

  /* Allocate initial_count tables */
  if (!(new_component_tables->tables = malloc(initial_count * sizeof(struct JEL_TableStack)))) {
    /* TODO: Error stuff */
    return NULL;
  }

  /* Allocate initial_count ids */
  if (!(new_component_tables->tables_types = malloc(initial_count * sizeof(struct JEL_TableStack)))) {
    /* TODO: Error stuff */
    return NULL;
  }

  new_component_tables->tables_allocated = initial_count;
  new_component_tables->tables_num = 0;

  return new_component_tables;
}

/*
 * JEL_table_stack_push_p
 *
 * @desc
 *   Adds a table to the stack
 * @param table
 *   Table to push
 * @return
 *    0 on success
 *   -1 if table stack allocation fails
 */
int JEL_table_stack_push_p(struct JEL_Table *table)
{
  if (JEL_context_current->table_stack->tables_allocated <= JEL_context_current->table_stack->tables_num) {
    if (JEL_table_stack_allocate_p(JEL_context_current->table_stack, JEL_context_current->table_stack->tables_allocated * 1.618)) {
      struct JEL_Error e = {"Cannot allocate a table stack", JEL_ERROR_ALLOCATE};
      JEL_error_push(e);
      return JEL_ERROR_ALLOCATE;
    }
  }

  JEL_context_current->table_stack->tables[JEL_context_current->table_stack->tables_num] = table;

  /* Set the id of the table */
  JEL_Type table_type = {0, 0, 0, 0};
  for (int i = 0; i < table->fragments_num; ++i) {
    JEL_type_index_add(table_type, table->fragments_types[i]);
  }

  memcpy(JEL_context_current->table_stack->tables_types[JEL_context_current->table_stack->tables_num], table_type, sizeof(JEL_Type));

  ++(JEL_context_current->table_stack->tables_num);

  return 0;
}

/*
 * JEL_table_stack_destroy_p
 *
 * @desc
 *   Destroys a JEL_TableStack
 * @param tables
 *   Table stack to destroy
 * @return
 *   0 on success
 */
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

/*
 * JEL_table_stack_allocate_p
 *
 * @desc
 *   Allocates memory for a table stack
 * @param ts
 *   Table stack to allocate
 * @param count
 *   How many table stacks to allocate
 * @return
 *    0 on success
 *   -1 if enough memory
 *   -2 if malloc fails
 */
int JEL_table_stack_allocate_p(struct JEL_TableStack *ts, JEL_ComponentInt count)
{
  if (count <= ts->tables_allocated) {
    return -1;
  }

  struct JEL_Table **new_tables;
  JEL_Type          *new_types;

  if (!(new_tables = malloc(count * sizeof(struct JEL_Table *)))) {
    struct JEL_Error e = {"Cannot allocate a table stack tables", JEL_ERROR_MALLOC};
    JEL_error_push(e);
    return JEL_ERROR_MALLOC;
  }

  if (!(new_types = malloc(count * sizeof(JEL_Type)))) {
    struct JEL_Error e = {"Cannot allocate a table stack types", JEL_ERROR_MALLOC};
    JEL_error_push(e);
    return JEL_ERROR_MALLOC;
  }

  memcpy(new_tables, ts->tables, ts->tables_num * sizeof(struct JEL_Table *));
  free(ts->tables);
  ts->tables = new_tables;

  memcpy(new_types, ts->tables_types, ts->tables_num * sizeof(JEL_Type));
  free(ts->tables_types);
  ts->tables_types = new_types;

  return 0;
}

#include "table.h"
#include "core.h"
#include "logger/logger.h"
#include <string.h>

#define GROWTH_FACTOR 2

/*
 * JEL_table_create
 *
 * @desc
 * @param table
 * @param type
 * @return
 */
int JEL_table_create(struct JEL_Table *table, JEL_Type type)
{
  int initial_count = 8;
  JEL_type_set(table->type, type);

  /* Set up the extra type stuff */
  table->types_num = JEL_type_num(type);

  if (!(table->types = malloc(table->types_num * sizeof(*table->types)))) {
    JEL_log("Could not create table: Out of memory");
    return -1;
  }

  if (!(table->type_buffers = malloc(table->types_num * sizeof(*table->type_buffers)))) {
    JEL_log("Could not create table: Out of memory");
    return -1;
  }

  /* Set total size and types */
  size_t size = 0;
  for (unsigned int type_index = 1, ti = 0; type_index < sizeof(JEL_Type) * 8; ++type_index) {
    if (JEL_TYPE_GET(table->type, type_index)) {
      table->types[ti++] = type_index;
      size += JEL_component_size(&JEL_CTX->component_table.components[type_index]);
    }
  }
 
  /* Make the buffer */
  table->size = size;
  if (!(table->buffer = malloc(initial_count * size))) {
    JEL_log("Could not create table: Out of memory");
    return -1;
  }

  /* Set the type buffers */
  size = 0;
  for (unsigned int ti = 0; ti < table->types_num; ++ti) {
    table->type_buffers[ti] = (char *) table->buffer + size * initial_count;
    size += JEL_component_size(&JEL_CTX->component_table.components[table->types[ti]]);
  }

  table->count = 1;
  table->allocated = initial_count;

  return 0;
}

/*
 * JEL_table_destroy
 *
 * @desc
 * @param table
 */
void JEL_table_destroy(struct JEL_Table *table)
{
  free(table->buffer);
  free(table->types);
  free(table->type_buffers);
}

/*
 * JEL_table_allocate
 *
 * @desc
 * @param table
 * @param count
 * @return
 */
int JEL_table_allocate(struct JEL_Table *table, unsigned int count)
{
  void *buffer;
  char *np, *op;

  if (count <= table->allocated) {
    JEL_log("Cannot allocate table: Already have enough memory");
    return -1;
  }

  if (!(buffer = malloc(count * table->size))) {
    JEL_log("Cannot allocate table: Out of memory");
    return -1;
  }

  np = buffer;
  op = table->buffer;

  for (unsigned int i = 0; i < table->types_num; ++i) {
    table->type_buffers[i] = np;

    for (unsigned int prop = 0; prop < JEL_CTX->component_table.components[table->types[i]].props; ++prop) {
      size_t prop_size = JEL_CTX->component_table.components[table->types[i]].sizes[prop];
      memcpy(np, op, table->count * prop_size);
      op += table->allocated * prop_size;
      np += count * prop_size;
    }
  }

  free(table->buffer);
  table->buffer = buffer;
  table->allocated = count;

  /* Reset entity table pointers (a new buffer was made) */
  for (unsigned int i = 1; i < table->count; ++i) {
    JEL_CTX->entity_manager.table_ptrs[JEL_entity_index(((JEL_Entity *) table->buffer)[i])] = &((JEL_Entity *) table->buffer)[i];
  }

  return 0;
}

/*
 * JEL_table_add
 *
 * @desc
 *   Adds an entity to a table, mainly
 *   used as a bootstrap function and
 *   also by table switch
 * @param table
 * @param entity
 * @return
 *   The index
 */
unsigned int JEL_table_add(struct JEL_Table *table, JEL_Entity entity)
{
  if (table->allocated <= table->count) {
    if (JEL_table_allocate(table, (unsigned int) (table->count * GROWTH_FACTOR))) {
      JEL_log("Could not allocate table: Out of memory");
      return -1;
    }
  }

  ((JEL_Entity *) table->buffer)[table->count] = entity;
  JEL_CTX->entity_manager.table_ptrs[JEL_entity_index(entity)] = &((JEL_Entity *) table->buffer)[table->count];

  return table->count++;
}

/*
 * JEL_table_set
 *
 * @desc
 *   Sets all values of one
 *   component for an entity
 * @param table
 *   The table the entity is in
 * @param component_index
 *   The index of the component
 * @param data
 *   Pointer to the struct with the data
 */
int JEL_table_set(struct JEL_Table *table, unsigned int idx, JEL_TypeIndex component_index, void *data)
{
  char *p = NULL; /* Beginning of the component buffer */
  for (unsigned int i = 0; i < table->types_num; ++i) {
    if (table->types[i] == component_index) {
      p = table->type_buffers[i];
      break;
    }
  }

  if (!p) {
    JEL_log("Component with index %u not found in the table", component_index);
    return -1;
  }

  /* Set the data */
  for (unsigned int i = 0; i < JEL_CTX->component_table.components[component_index].props; ++i) {
    size_t prop_size = JEL_CTX->component_table.components[component_index].sizes[i];
    memcpy(p + idx * prop_size, (char *) data + JEL_CTX->component_table.components[component_index].offsets[i], prop_size);
    p += table->allocated * prop_size;
  }

  return 0;
}

/*
 * JEL_table_set_member
 */
int JEL_table_set_member(struct JEL_Table *table, JEL_Entity entity, JEL_TypeIndex ti, size_t size, size_t offset, void *data)
{
  unsigned int index = JEL_table_index(table, entity);
  if (!index) {
    JEL_log("Entity %u not found in the table", entity);
    return -1;
  }

  char *p = NULL; /* Beginning of the component buffer */
  for (unsigned int i = 0; i < table->types_num; ++i) {
    if (table->types[i] == ti) {
      p = table->type_buffers[i];
      break;
    }
  }

  if (!p) {
    JEL_log("Component with index %u not found in the table", ti);
    return -1;
  }

  /*
   * offset * table->allocated gets to buffer of that member
   * size * index gets to the right thing to edit
   */
  memcpy(p + offset * table->allocated + size * index, data, size);

  return 0;
}

/*
 * JEL_table_remove
 */
int JEL_table_remove(struct JEL_Table *table, unsigned int idx)
{
  /* Replace the item to remove with the last item, then decrease the count */

  /* No need to swap if just one item (2nd element is actual element, 1st is null) or last item */
  if (--table->count < 2 || idx == table->count) {
    return 0;
  }

  /* Replace data */
  char *p = table->buffer;
  for (unsigned int ci = 0; ci < table->types_num; ++ci) {
    for (unsigned int i = 0; i < JEL_CTX->component_table.components[table->types[ci]].props; ++i) {
      size_t prop_size = JEL_CTX->component_table.components[table->types[ci]].sizes[i];
      memcpy(p + idx * prop_size, p + table->count * prop_size, prop_size);
      p += table->allocated * prop_size;
    }
  }

  /* Update table pointer for the moved entity */
  JEL_CTX->entity_manager.table_ptrs[JEL_entity_index(((JEL_Entity *) table->buffer)[idx])] = &((JEL_Entity *) table->buffer)[idx];

  return 0;
}

/*
 * JEL_table_get
 *
 * @desc
 *   Puts the data into a struct
 */
int JEL_table_get(struct JEL_Table *table, unsigned int idx, JEL_TypeIndex component_index, void *data)
{
  /* This is the same as set except for the memcpy, the parameters are switched */
  char *p = NULL; /* Beginning of the component buffer */
  for (unsigned int i = 0; i < table->types_num; ++i) {
    if (table->types[i] == component_index) {
      p = table->type_buffers[i];
    }
  }

  if (!p) {
    JEL_log("Component with index %u not found in the table", component_index);
    return -1;
  }

  /* Set the data */
  for (unsigned int i = 0; i < JEL_CTX->component_table.components[component_index].props; ++i) {
    size_t prop_size = JEL_CTX->component_table.components[component_index].sizes[i];
    memcpy((char *) data + JEL_CTX->component_table.components[component_index].offsets[i], p + idx * prop_size, prop_size);
    p += table->allocated * prop_size;
  }
  return 0;
}

/*
 * JEL_table_index
 * 
 * @desc
 *   Find the index of an entity
 *   WARNING: The entity must be in the table
 * @param table
 *   The table the entity is in
 * @param entity
 *   The entity to search the index for
 * @return
 *   The index where the entity is in the table
 */
unsigned int JEL_table_index(struct JEL_Table *table, JEL_Entity entity)
{
  return ((JEL_Entity *) JEL_CTX->entity_manager.table_ptrs[JEL_entity_index(entity)] - (JEL_Entity *) table->buffer);
}

/*
 * JEL_table_get_it
 * @desc
 *   TODO (write desc)
 * @param table
 * @param it
 *   The first member of the struct
 * @param ti
 * @return
 *   Error
 */
int JEL_table_get_it(struct JEL_Table *table, void *it, JEL_TypeIndex ti)
{
  int table_index = -1;
  for (unsigned int i = 0; i < table->types_num; ++i) {
    if (ti == table->types[i]) {
      table_index = i;
    }
  }

  if (table_index == -1) {
    char * comp_name = JEL_component_map_get_key(&JEL_CTX->component_map, ti);
    // TODO: Display table name
    JEL_log("CANNOT GET ITERATOR: Table doesn't have type [%s]", comp_name);
    return -1;
  }

  void *bp = table->type_buffers[table_index];
  for (unsigned int i = 0; i < JEL_CTX->component_table.components[ti].props; ++i) {
    *((void **) it) = bp;
    it = (char *) it + sizeof(void *);
    bp = (char *) bp + table->allocated * JEL_CTX->component_table.components[ti].sizes[i];
  }

  return 0;
}

/*
 * JEL_table_component_copy
 * 
 * @desc
 *   Helper function for table_switch
 *   Copies a into b
 *   No error checking for type
 * @param a
 *   Table to copy from
 * @param idxa
 *   Index in table a
 * @param b
 *   Table to paste to
 * @param idxb
 *   Index in table b
 * @param ti
 *   Component to copy
 */
int JEL_table_component_copy(struct JEL_Table *a, unsigned int idxa, struct JEL_Table *b, unsigned int idxb, JEL_TypeIndex ti)
{
  // TODO: There is some problem with this function
  char *oldp;
  char *newp;

  for (unsigned int i = 0; i < a->types_num; ++i) {
    if (a->types[i] == ti) {
      oldp = a->type_buffers[i];
      break;
    }
  }

  for (unsigned int i = 0; i < b->types_num; ++i) {
    if (b->types[i] == ti) {
      newp = b->type_buffers[i];
      break;
    }
  }

  /* Actually copy the data */
  for (unsigned int i = 0; i < JEL_CTX->component_table.components[ti].props; ++i) {
    size_t prop_size = JEL_CTX->component_table.components[ti].sizes[i];
    memcpy(newp + idxb * prop_size, oldp + idxa * prop_size, prop_size);
    oldp += a->allocated * prop_size;
    newp += b->allocated * prop_size;
  }

  return 0;
}

/*
 * JEL_table_switch
 * 
 * @desc
 *   Moves an entity from one table
 *   to another (add a component or remove)
 *   entity must be alive and in the table
 *   for this function to work
 * @param a
 *   The old table
 * @param b
 *   The new table
 * @param entity
 *   The entity to move
 * @return
 *   Success
 */
int JEL_table_switch(struct JEL_Table* a, struct JEL_Table* b, JEL_Entity entity)
{
  unsigned int old_idx = JEL_table_index(a, entity);

  /* Copy new */
  unsigned int new_idx = JEL_table_add(b, entity);

  for (unsigned int i = 1; i < b->types_num; ++i) {
    /* Only copy the type if the new table has the same type */
    if (!JEL_type_index_check(a->type, b->types[i])) {
      continue;
    }
    /* Copy and paste the data */
    JEL_table_component_copy(a, old_idx, b, new_idx, b->types[i]);
  }

  JEL_table_remove(a, old_idx);

  return 0;
}

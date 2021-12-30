#include "table.h"
#include "core.h"
#include "logger/logger.h"
#include <string.h>

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

  return 0;
}

/*
 * JEL_table_add
 *
 * @desc
 * @param table
 * @param entity
 * @return
 */
int JEL_table_add(struct JEL_Table *table, JEL_Entity entity)
{
  if (table->allocated <= table->count) {
    if (JEL_table_allocate(table, (unsigned int) (table->count * 1.618))) {
      JEL_log("Could not allocate table: Out of memory");
      return -1;
    }
  }

  ((JEL_Entity *) table->buffer)[table->count++] = entity;

  return 0;
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
int JEL_table_set(struct JEL_Table *table, JEL_Entity entity, JEL_TypeIndex component_index, void *data)
{
  unsigned int index = JEL_table_index(table, entity);
  if (!index) {
    JEL_log("Entity %u not found in the table", entity);
    return -1;
  }

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
    memcpy(p + index * prop_size, (char *) data + JEL_CTX->component_table.components[component_index].offsets[i], prop_size);
    p += table->allocated * prop_size;
  }

  return 0;
}

/*
 * JEL_table_remove
 */
int JEL_table_remove(struct JEL_Table *table, JEL_Entity entity)
{
  /* Swap the last item(s) with the item(s) to remove, then decrease the count */
  unsigned int index = JEL_table_index(table, entity);
  if (!index) {
    JEL_log("Entity %u not found in the table", entity);
    return -1;
  }

  /* No need to swap if just one item */
  if (table->count == 1) {
    --table->count;
    return 0;
  }

  char *p = table->buffer;
  for (unsigned int ci = 0; ci < table->types_num; ++ci) {
    for (unsigned int i = 0; i < JEL_CTX->component_table.components[table->types[ci]].props; ++i) {
      size_t prop_size = JEL_CTX->component_table.components[table->types[ci]].sizes[i];
      memcpy(p + index * prop_size, p + (table->count - 1) * prop_size, prop_size);
      p += table->allocated * prop_size;
    }
  }

  --table->count;

  return 0;
}

/*
 * JEL_table_get
 *
 * @desc
 *   Puts the data into a struct
 */
int JEL_table_get(struct JEL_Table *table, JEL_Entity entity, JEL_TypeIndex component_index, void *data)
{
  /* This is the same as set except for the memcpy, the parameters are switched */
  unsigned int index = JEL_table_index(table, entity);
  if (!index) {
    JEL_log("Entity %u not found in the table", entity);
    return -1;
  }

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
    memcpy((char *) data + JEL_CTX->component_table.components[component_index].offsets[i], p + index * prop_size, prop_size);
    p += table->allocated * prop_size;
  }
  return 0;
}

/*
 * JEL_table_index
 */
unsigned int JEL_table_index(struct JEL_Table *table, JEL_Entity entity)
{
  for (unsigned int i = 1; i < table->count; ++i) {
    if (((JEL_Entity *) table->buffer)[i] == entity) {
      return i;
    }
  }

  return 0;
}

/*
 * @param it
 *   The first member of the struct
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
    JEL_log("Cannot get iterator: Table doesn't have type %u", ti);
  }

  void *bp = table->type_buffers[table_index];
  for (unsigned int i = 0; i < JEL_CTX->component_table.components[ti].props; ++i) {
    *((void **) it) = bp;
    it = (char *) it + sizeof(void *);
    bp = (char *) bp + table->allocated * JEL_CTX->component_table.components[ti].sizes[i];
  }

  return 0;
}

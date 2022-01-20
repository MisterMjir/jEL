#include "component.h"
#include <stdlib.h>
#include <string.h>
#include "logger/logger.h"

/*
 * JEL_component_table_create
 *
 * @desc
 * @return
 */
int JEL_component_table_create(struct JEL_ComponentTable *table)
{
  const int initial_count = 8;

  /* Initialize generations and types */
  if (!(table->components = malloc(initial_count * sizeof(*table->components)))) {
    JEL_log("Cannot create a component table: Out of memory");
    return -1;
  }
  table->allocated = initial_count;
  table->count = 1; /* 0th is NULL component */

  return 0;
}

/*
 * JEL_component_table_destroy
 *
 * @desc
 * @param table
 */
void JEL_component_table_destroy(struct JEL_ComponentTable *table)
{
  free(table->components);
}

/*
 * JEL_component_table_add
 *
 * @desc
 * @param table
 * @param component
 * @return
 */
int JEL_component_table_add(struct JEL_ComponentTable *table, struct JEL_Component *component)
{
  if (table->allocated <= table->count) {
    if (JEL_component_table_allocate(table, (unsigned int) (table->count * 1.618))) {
      JEL_log("Could not allocate component table: Not enough memory");
      return -1;
    }
  }

  JEL_component_create(&table->components[table->count++], component->props, component->sizes, component->offsets);

  return 0;
}

/*
 * JEL_entity_manager_generations_allocate
 *
 * @desc
 * @param entity_manager
 * @param count
 * @return
 *    0 on success
 *   -1 if there is already enough memory
 *   -2 if malloc failed
 */
int JEL_component_table_allocate(struct JEL_ComponentTable *table, unsigned int count)
{
  if (count <= table->count)
    return -1;

  struct JEL_Component *components;

  if (!(components = malloc(count * sizeof(*components)))) {
    JEL_log("Cannot allocate component table: Out of memory");
    return -2;
  }

  /* Copy, free, and assign */
  memcpy(components, table->components, sizeof(*components) * table->count);
  free(table->components);
  table->components = components;

  table->allocated = count;

  return 0;
}

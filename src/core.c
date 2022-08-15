#include "core.h"
#include <stdlib.h>
#include <string.h>
#include "logger/logger.h"

JEL_GLOBAL_VAR struct JEL_Context *JEL_CTX = NULL;

JEL_GLOBAL_VAR unsigned int JEL_EntityC_props = 1;
JEL_GLOBAL_VAR size_t       JEL_EntityC_sizes[] = { sizeof(JEL_Entity) };
JEL_GLOBAL_VAR size_t       JEL_EntityC_offsets[] = { offsetof(struct JEL_EntityC, entity) };

/*
 * JEL_context_create
 *
 * @desc
 *      Creates a new JEL_Context
 * @return
 *      A pointer to a JEL_Context, NULL on failure
 */
int JEL_init(void)
{
  if (JEL_CTX != NULL) {
    JEL_log("Cannot init JEL: There is already a current context");
    return -2;
  }

  if (!(JEL_CTX = malloc(sizeof(struct JEL_Context)))) {
    JEL_log("Cannot init JEL: Out of memory");
    return -1;
  }

  /* Entity Manager */
  if (JEL_entity_manager_create(&JEL_CTX->entity_manager)) {
    JEL_log("Cannot init JEL: Out of memory");
    return -1;
  }

  /* Component stuff */
  if (JEL_component_table_create(&JEL_CTX->component_table)) {
    JEL_log("Cannot init JEL: Out of memory");
    return -1;
  }
  JEL_component_map_create(&JEL_CTX->component_map);

  /* Table stuff */
  if (JEL_table_stack_create(&JEL_CTX->table_stack)) {
    JEL_log("Cannot init JEL: Out of memory");
    return -1;
  }

  /* Bootstrap */
  { /* Register JEL_EntityC */
    struct JEL_Component c;
    JEL_component_create(&c, JEL_EntityC_props, JEL_EntityC_sizes, JEL_EntityC_offsets);
    JEL_component_table_add(&JEL_CTX->component_table, &c); \
    JEL_component_map_add(&JEL_CTX->component_map, "JEL_EntityC", JEL_CTX->component_table.count - 1); \
  }
  { /* Add a JEL_EntityC table */
    JEL_Type t;
    JEL_type_init(t);
    JEL_table_stack_push(&JEL_CTX->table_stack, t);
  }

  return 0;
}

/*
 * JEL_context_destroy
 *
 * @desc
 *      Destroys JEL_Context
 * @return
 *      Success
 */
void JEL_quit(void)
{
  if (JEL_CTX == NULL) return;

  JEL_table_stack_destroy(&JEL_CTX->table_stack);

  JEL_component_table_destroy(&JEL_CTX->component_table);
  JEL_component_map_destroy(&JEL_CTX->component_map);

  JEL_entity_manager_destroy(&JEL_CTX->entity_manager);
  free(JEL_CTX);

  JEL_CTX = NULL;
}

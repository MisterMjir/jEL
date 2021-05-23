#include "prefab.h"
#include "prefab_utility.h"
#include <stdlib.h>
#include "entity.h"
#include "table/table.h"
#include "core.h"

/*
 * JEL_prefab_create
 *
 * @desc
 *   Creates a prefab node, sets values
 *   to NULL except stuff in parameters
 * @param type
 *   The type to be associated with this node
 * @param data
 *   The data to be associated with this node
 *   This just copies the pointer of the data
 * @return
 *   A pointer to the created node, NULL
 *   on failure
 */
struct JEL_Prefab * JEL_prefab_create(JEL_Type type, void *data)
{
  struct JEL_Prefab *prefab;

  if (!(prefab = malloc(sizeof(struct JEL_Prefab)))) {
    return NULL;
  }

  JEL_type_set(prefab->type, type);
  prefab->data = data;

  prefab->parent = NULL;
  prefab->sibling_next = NULL;
  prefab->child_first = NULL;

  return prefab;
}

/*
 * JEL_prefab_destroy_helper_p
 *
 * @desc
 *   Helper method for destroying a prefab
 * @param prefab
 *   Prefab to free
 */
void JEL_prefab_destroy_helper_p(struct JEL_Prefab *prefab)
{
  free(prefab->data);
  free(prefab);
}

/*
 * JEL_prefab_destroy
 *
 * @desc
 *   Destroys a prefab
 * @param prefab
 *   Topmost prefab in the node to destroy
 * @return
 *   0 on success
 */
int JEL_prefab_destroy(struct JEL_Prefab *prefab)
{
  JEL_prefab_iterate_up_p(prefab, JEL_prefab_destroy_helper_p);

  free(prefab);

  return 0;
}

/*
 * JEL_prefab_add
 *
 * @desc
 *   Adds b to a
 * @param a
 *   Node to add to (parent)
 * @param b
 *   Node to add
 * @return
 *   0 on success
 */
int JEL_prefab_add(struct JEL_Prefab *a, struct JEL_Prefab *b)
{
  if (a->child_first == NULL) {
    a->child_first = b;
  }
  else {
    struct JEL_Prefab *sibling_left = a->child_first;
    while (sibling_left->sibling_next != NULL) {
      sibling_left = sibling_left->sibling_next;
    }
    sibling_left->sibling_next = b;
  }

  b->parent = a;

  return 1;
}

/*
 * JEL_prefab_generate_helper_p
 *
 * @desc
 *   Private helper
 *
 */
struct JEL_Hierarchy * JEL_prefab_generate_helper_p(struct JEL_Prefab *prefab, struct JEL_Hierarchy *parent)
{
  JEL_Entity entity = JEL_entity_create();

  /* Add the entity to a table */

  /* The same as JEL_ENTITY_ADD */
  struct JEL_Table *old_table = JEL_table_get(JEL_context_current->entity_manager->types[JEL_entity_index_get(entity)]);
  JEL_type_set(JEL_context_current->entity_manager->types[JEL_entity_index_get(entity)], prefab->type);
  struct JEL_Table *new_table = JEL_table_get(JEL_context_current->entity_manager->types[JEL_entity_index_get(entity)]);
  if (new_table == NULL) {
    new_table = JEL_table_create_type_p(JEL_context_current->entity_manager->types[JEL_entity_index_get(entity)]);
    JEL_table_stack_push_p(new_table);
  }
  JEL_table_remove_p(old_table, entity);

  *((JEL_Entity *) prefab->data) = entity;

  JEL_table_add_buffer_p(new_table, prefab->data);

  /* Add the entity to a hierarchy */
  struct JEL_Hierarchy *h = NULL;
  if (parent == NULL) {
    h = JEL_hierarchy_create();
  }
  else {

  }

  /* Iterate down */

  return h;
}

/*
 * JEL_prefab_generate
 *
 * @desc
 *   Generates a hierarchy from a prefab
 * @param prefab
 *   The root prefab
 * @return
 *   0 on success
 */
JEL_Entity JEL_prefab_generate(struct JEL_Prefab *prefab)
{
  JEL_Entity entity = JEL_entity_create();

  /* Almost the same as JEL_ENTITY_ADD */
  JEL_Type t = {2, 0, 0, 0};
  struct JEL_Table *old_table = JEL_table_get(t);

  JEL_EntityInt entity_index = JEL_entity_index_get(entity);

  JEL_type_set(JEL_context_current->entity_manager->types[entity_index], prefab->type);
  struct JEL_Table *new_table = JEL_table_get(JEL_context_current->entity_manager->types[entity_index]);
  if (new_table == NULL) {
    new_table = JEL_table_create_type_p(JEL_context_current->entity_manager->types[entity_index]);
    JEL_table_stack_push_p(new_table);
  }
  JEL_table_remove_p(old_table, entity);

  *((JEL_Entity *) prefab->data) = entity;

  JEL_table_add_buffer_p(new_table, prefab->data);
  
  return entity;
}

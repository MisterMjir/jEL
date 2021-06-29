#include "prefab_utility.h"
#include "table/table.h"
#include "core.h"

/*
 * JEL_prefab_iterate_up_p
 *
 * @desc
 *   Iterates a prefab hierarchy bottom up
 * @param prefab
 *   The root prefab
 * @param function
 *   Function to be called on each prefab node
 */
void JEL_prefab_iterate_up_p(struct JEL_Prefab *prefab, void (*function)(struct JEL_Prefab *))
{
  if (prefab->sibling_next != NULL) {
    JEL_prefab_iterate_up_p(prefab->sibling_next, function);
  }

  if (prefab->child_first != NULL) {
    JEL_prefab_iterate_up_p(prefab->child_first, function);
  }

  function(prefab);
}

/*
 * JEL_prefab_generate_iterate_p
 *
 * @desc
 *   Iterates a prefab hierarchy top down
 * @param prefab
 *   The root prefab
 * @param function
 *   Function to be called on each prefab node
 */
struct JEL_Node * JEL_prefab_generate_iterate_p(struct JEL_Prefab *prefab, struct JEL_Node *parent, struct JEL_Node * (*function)(struct JEL_Prefab *, struct JEL_Node *))
{
  struct JEL_Node *node = function(prefab, parent);
  
  if (prefab->sibling_next != NULL) {
    JEL_prefab_generate_iterate_p(prefab->sibling_next, parent, function);
  }

  if (prefab->child_first != NULL) {
    JEL_prefab_generate_iterate_p(prefab->child_first, node, function);
  }

  return node;
}

/*
 *
 */
struct JEL_Node * JEL_prefab_generate_helper_p(struct JEL_Prefab *node, struct JEL_Node *parent)
{
  JEL_Entity entity = JEL_entity_create();

  /* Almost the same as JEL_ENTITY_ADD */
  JEL_Type t = {2, 0, 0, 0};
  struct JEL_Table *old_table = JEL_table_get(t);

  JEL_EntityInt entity_index = JEL_entity_index_get(entity);

  JEL_type_set(JEL_context_current->entity_manager->types[entity_index], node->type);
  struct JEL_Table *new_table = JEL_table_get(JEL_context_current->entity_manager->types[entity_index]);
  if (new_table == NULL) {
    new_table = JEL_table_create_type_p(JEL_context_current->entity_manager->types[entity_index]);
    JEL_table_stack_push_p(new_table);
  }
  JEL_table_remove_p(old_table, entity);

  *((JEL_Entity *) node->data) = entity;

  JEL_table_add_buffer_p(new_table, node->data);

  /* Add to node */
  /* TODO: Error checking */
  struct JEL_Node *n = JEL_node_create(entity);
  if (parent) {
    JEL_hierarchy_add(parent, n);
  }
  return n;
}

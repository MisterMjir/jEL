#include "hierarchy_utility.h"

/*
 * JEL_hierarchy_iterate_up
 *
 * @desc
 *   Iterate through all nodes via recursion,
 *   iterates up so function is called in child
 *   nodes up
 * @param node
 *   The root node of the hierarchy
 * @param function
 *   The funciton to call each iteration
 */
void JEL_hierarchy_iterate_up(struct JEL_Node *node, void (*function)(struct JEL_Node *))
{
  if (node->sibling_next != NULL) {
    JEL_hierarchy_iterate_up(node->sibling_next, function);
  }

  if (node->child_first != NULL) {
    JEL_hierarchy_iterate_up(node->child_first, function);
  } 
  
  function(node);
}

/*
 * JEL_hierarchy_iterate_down
 *
 * @desc
 *   Iterate through all nodes via recursion,
 *   iterates down so function is called on
 *   root node down
 *   nodes up
 * @param node
 *   The root node of the hierarchy
 * @param function
 *   The funciton to call each iteration
 */
void JEL_hierarchy_iterate_down(struct JEL_Node *node, void (*function)(struct JEL_Node *))
{
  function(node);
  
  if (node->sibling_next != NULL) {
    JEL_hierarchy_iterate_down(node->sibling_next, function);
  }

  if (node->child_first != NULL) {
    JEL_hierarchy_iterate_down(node->child_first, function);
  } 
}

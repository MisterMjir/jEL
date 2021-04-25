#include "hierarchy_utility.h"

// ========================================
// JEL_hierarchy_recursion
//
// @desc
//   Iterate through all nodes via recursion
// @param node
//   The root node of the hierarchy
// @param function
//   The funciton to call each iteration
// ========================================
void JEL_hierarchy_recursion(struct JEL_HierarchyNode *node, void (*function)(struct JEL_HierarchyNode *))
{
  if (node->sibling_next != NULL) {
    JEL_hierarchy_recursion(node->sibling_next, function);
  }

  if (node->child_first != NULL) {
    JEL_hierarchy_recursion(node->child_first, function);
  } 
  
  function(node);
}

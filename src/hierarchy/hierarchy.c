#include "hierarchy/hierarchy.h"
#include "hierarchy_utility.h"
#include <stdlib.h>

// =======================================
// JEL_hierarchy_create
//
// @desc
//   Creates a hierarchy and the root node
// @return
//   A pointer to a hierarchy,
//   NULL on failure
// =======================================
struct JEL_Hierarchy * JEL_hierarchy_create(void)
{
  struct JEL_Hierarchy *new_hierarchy;

  if (!(new_hierarchy = malloc(sizeof(struct JEL_Hierarchy)))) {
    return NULL;
  }

  struct JEL_HierarchyNode *root_node;

  if (!(root_node = malloc(sizeof(struct JEL_HierarchyNode)))) {
    return NULL;
  }

  root_node->entity = 0;
  root_node->parent = NULL;
  root_node->child_first = NULL;
  root_node->sibling_next = NULL;

  new_hierarchy->root = root_node;

  return new_hierarchy;
}

// ========================================
// JEL_hierarchy_destroy_helper_p
//
// @desc
//   Private function that the recursion calls
// @param node
//   The node to free
// ========================================
void JEL_hierarchy_destroy_helper_p(struct JEL_HierarchyNode *node)
{
  free(node);
}

// ========================================
// JEL_hierarchy_destroy
//
// @desc
//   Destroys a hierarchy
// @param hierarchy
//   Hierarchy to destroy
// @return
//   0 on success
// ========================================
int JEL_hierarchy_destroy(struct JEL_Hierarchy *hierarchy)
{
  JEL_hierarchy_iterate_up(hierarchy->root, JEL_hierarchy_destroy_helper_p);
  free(hierarchy);
  return 0;
}

// ========================================
// JEL_hierarchy_add
//
// @desc
//   Adds node_b to node_a
// @param node_a
//   Node to add to
// @param node_b
//   Node to add
// @return
//   0 on success
// ========================================
int JEL_hierarchy_add(struct JEL_HierarchyNode *node_a, struct JEL_HierarchyNode *node_b)
{
  if (node_a->child_first == NULL) {
    node_a->child_first = node_b;
  }
  else {
    struct JEL_HierarchyNode *left_sibling = node_a->child_first;
    while (left_sibling->sibling_next != NULL) {
      left_sibling = left_sibling->sibling_next;
    }
    left_sibling->sibling_next = node_b;
  }

  node_b->parent = node_a;

  return 0;
}

// ========================================
// JEL_hierarchy_attach
//
// @desc
//   Attaches a hierarchy to a node, the hierarchy
//   is free'd
// @param node
//   The node to attach to
// @param hierarchy
//   The hierarchy to attach
// @return
//   0 on success
// ========================================
int JEL_hierarchy_attach(struct JEL_HierarchyNode *node, struct JEL_Hierarchy *hierarchy)
{
  if (node->child_first == NULL) {
    node->child_first = hierarchy->root;
  }
  else {
    struct JEL_HierarchyNode *left_sibling = node->sibling_next;
    while (left_sibling->sibling_next != NULL) {
      left_sibling = left_sibling->sibling_next;
    }
    left_sibling->sibling_next = hierarchy->root;
  }

  hierarchy->root->parent = node;

  free(hierarchy);

  return 0;
}

// ========================================
// JEL_hierarchy_detach
//
// @desc
//   Removes a node and all children and turns
//   that into a hierarchy
// @param node
//   The node to detach
// @return
//   A newly made hierarchy
// ========================================
struct JEL_Hierarchy * JEL_hierarchy_detach(struct JEL_HierarchyNode *node)
{
  struct JEL_Hierarchy *new_hierarchy;
  if (!(new_hierarchy = malloc(sizeof(struct JEL_Hierarchy)))) {
    return NULL;
  }

  new_hierarchy->root = node;
  
  // Check if the node is first child or a sibling, handle appropitately
  if (node == node->parent->child_first) {
    node->parent->child_first = node->sibling_next;
  }
  else {
    struct JEL_HierarchyNode *left_sibling = node->parent->child_first;
    while (left_sibling->sibling_next != node) {
      left_sibling = left_sibling->sibling_next;
    }
    left_sibling->sibling_next = node->sibling_next;
  }

  new_hierarchy->root->parent = NULL;

  return new_hierarchy;
}

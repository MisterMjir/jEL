#ifndef JEL_HIERARCHY_h
#define JEL_HIERARCHY_h

#include "../entity.h"

struct JEL_HierarchyNode {
  JEL_Entity                entity;
  struct JEL_HierarchyNode *parent;
  struct JEL_HierarchyNode *child_first;
  struct JEL_HierarchyNode *sibling_next;
};

struct JEL_Hierarchy {
  struct JEL_HierarchyNode *root;
};

// ========================================
// Hierarchy functions
//
// create - Creates a hierarchy
// destroy - Destroyes a hierarchy
// add - Adds a child to a parent node
// attach - Attachs a hierarchy to a node
// detach - Removes a node (and all children) and make it a hierarchy
// ========================================
struct JEL_Hierarchy * JEL_hierarchy_create(void);
int                    JEL_hierarchy_destroy(struct JEL_Hierarchy *);
int                    JEL_hierarchy_add(struct JEL_HierarchyNode *, struct JEL_HierarchyNode *);
int                    JEL_hierarchy_attach(struct JEL_HierarchyNode *, struct JEL_Hierarchy *);
struct JEL_Hierarchy * JEL_hierarchy_detach(struct JEL_HierarchyNode *);

#endif

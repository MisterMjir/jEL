#ifndef JEL_HIERARCHY_UTILITY_H
#define JEL_HIERARCHY_UTILITY_H

#include "hierarchy/hierarchy.h"

void JEL_hierarchy_recursion(struct JEL_HierarchyNode *, void (*)(struct JEL_HierarchyNode *));

#endif

#ifndef JEL_PREFAB_UTILITY_H
#define JEL_PREFAB_UTILITY_H

#include "prefab.h"
#include "hierarchy.h"

void JEL_prefab_iterate_up_p(struct JEL_Prefab *, void (*)(struct JEL_Prefab *));

/*
 * Generate helpers
 *
 * Iterate iterates down, but the signature is different from other iterates
 *
 * It needs a parent node in the callback function, so it can attach the tile node,
 * and the callback needs to return a node, so it can give a new parent on iteration
 *
 * Iterate also returns the node of the root when called out of itself
 */
struct JEL_Node * JEL_prefab_generate_iterate_p(struct JEL_Prefab *, struct JEL_Node *, struct JEL_Node * (*)(struct JEL_Prefab *, struct JEL_Node *));
struct JEL_Node * JEL_prefab_generate_helper_p(struct JEL_Prefab *, struct JEL_Node *);

#endif

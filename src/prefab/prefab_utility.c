#include "prefab_utility.h"

/*
 * JEL_prefab_iterate_up_p
 *
 * @desc
 *   Iterates a prefab hierarchy bottom up
 * @param prefab
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

#ifndef JEL_COMPONENT_STACK_H
#define JEL_COMPONENT_STACK_H

#include "component_types.h"
#include <stddef.h>
#include "table/table_fragment.h"

// ========================================
//
// Component Stack
//
// Stores run-time information needed for
// components
//
// - The amount of components registered
// - The size of fragment structs
//   - Given an id, I need to determine the
//     size of the corresponding struct
// - A pointer to the fragment info
//
// ========================================

struct JEL_ComponentStack {
  JEL_ComponentInt          components_num;
  JEL_ComponentInt          allocated; // Not components_allocated because it's not related to anything

  size_t                   *table_fragments_sizes;
  struct JEL_FragmentInfo **fragments_infos; // Could be pointer to const pointer?
};

#endif

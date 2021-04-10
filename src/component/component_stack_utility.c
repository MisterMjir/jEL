#include "component_stack_utility.h"
#include "core.h"
#include <stdlib.h>
#include <string.h>

// ========================================
// ========================================
struct JEL_ComponentStack * JEL_component_stack_create_p(void)
{
  struct JEL_ComponentStack *new_component_stack;
  const int initial_count = 8;

  if (!(new_component_stack = malloc(sizeof(struct JEL_ComponentStack)))) {
    return NULL;
  }

  if (!(new_component_stack->table_fragments_sizes = malloc(initial_count * sizeof(size_t)))) {
    return NULL;
  }

  if (!(new_component_stack->fragments_infos = malloc(initial_count * sizeof(struct JEL_FragmentInfo *)))) {
    return NULL;
  }

  new_component_stack->components_num = 1; // 0 index is a NULL component
  new_component_stack->allocated = initial_count;

  return new_component_stack;
}

// ========================================
// ========================================
int JEL_component_stack_destroy_p(struct JEL_ComponentStack *cs)
{
  free(cs->table_fragments_sizes);
  free(cs->fragments_infos);
  free(cs);

  return 0;
}

// ========================================
// ========================================
int JEL_component_stack_allocate_p(struct JEL_ComponentStack * cs, JEL_ComponentInt count)
{
  if (count < cs->allocated)
    return -1;

  size_t *new_table_fragment_sizes;

  if (!(new_table_fragment_sizes = malloc(count * (sizeof(size_t)))))
    return -2;

  memcpy(new_table_fragment_sizes, cs->table_fragments_sizes, cs->components_num * sizeof(size_t));
  free(cs->table_fragments_sizes);
  cs->table_fragments_sizes = new_table_fragment_sizes;

  cs->allocated = count;

  return 0;
}

// ========================================
// @desc
//   Increments components_num and pushes
//   a table fragment size to the stack
// ========================================
int JEL_component_stack_push_p(size_t tf_size, struct JEL_FragmentInfo *tf_info)
{
  if (JEL_context_current->component_stack->allocated <= JEL_context_current->component_stack->components_num) {
    if (JEL_component_stack_allocate_p(JEL_context_current->component_stack, JEL_context_current->component_stack->allocated * 1.618)) {
      return -2;
    }
  }

  JEL_context_current->component_stack->table_fragments_sizes[JEL_context_current->component_stack->components_num] = tf_size;
  JEL_context_current->component_stack->fragments_infos[JEL_context_current->component_stack->components_num] = tf_info;

  ++JEL_context_current->component_stack->components_num;

  return 0;
}

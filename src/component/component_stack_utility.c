#include "component_stack_utility.h"
#include "core.h"
#include <stdlib.h>
#include <string.h>
#include "error.h"

/*
 * JEL_component_stack_create_p
 *
 * @desc
 *   Creates a component stack
 * @return
 *   A pointer to a newly made component stack,
 *   NULL on failure
 */
struct JEL_ComponentStack * JEL_component_stack_create_p(void)
{
  struct JEL_ComponentStack *new_component_stack;
  const int initial_count = 8;

  if (!(new_component_stack = malloc(sizeof(struct JEL_ComponentStack)))) {
    struct JEL_Error e = {"Could not malloc a struct JEL_ComponentStack", -1};
    JEL_error_push(e);
    return NULL;
  }

  if (!(new_component_stack->fragments_sizes = malloc(initial_count * sizeof(size_t)))) {
    struct JEL_Error e = {"Could not malloc a struct JEL_ComponentStack's table_fragment_sizes", -1};
    JEL_error_push(e);
    return NULL;
  }

  if (!(new_component_stack->fragments_infos = malloc(initial_count * sizeof(struct JEL_FragmentInfo *)))) {
    struct JEL_Error e = {"Could not malloc a struct JEL_ComponentStack's fragments_infos", -1};
    JEL_error_push(e);
    return NULL;
  }

  new_component_stack->components_num = 1;  /* 0 index is a NULL component */
  new_component_stack->allocated = initial_count;

  return new_component_stack;
}

/*
 * JEL_component_stack_destroy_p
 *
 * @desc
 *   Cleans up a component stack
 * @param cs
 *   The component stack to destroy
 * @return
 *   0 on success
 */
int JEL_component_stack_destroy_p(struct JEL_ComponentStack *cs)
{
  free(cs->fragments_sizes);
  free(cs->fragments_infos);
  free(cs);

  return 0;
}

/*
 * JEL_component_stack_allocate_p
 *
 * @desc
 *   Allocates memory for component stack
 *   members
 * @param cs
 *   Component stack to allocate memory for
 * @param count
 *   How many components to allocate for
 * @return
 *    0 on success
 *   -1 if count is good enough
 *   -2 if malloc fails
 */
 int JEL_component_stack_allocate_p(struct JEL_ComponentStack *cs, JEL_ComponentInt count)
{
  if (count <= cs->allocated) {
    return -1;
  }

  size_t *new_table_fragment_sizes;

  if (!(new_table_fragment_sizes = malloc(count * (sizeof(size_t))))) {
    struct JEL_Error e = {"Could not allocate more components for the struct JEL_ComponentStack", -1};
    JEL_error_push(e);
    return -2;
  }

  memcpy(new_table_fragment_sizes, cs->fragments_sizes, cs->components_num * sizeof(size_t));
  free(cs->fragments_sizes);
  cs->fragments_sizes = new_table_fragment_sizes;

  cs->allocated = count;

  return 0;
}

/*
 * JEL_component_stack_push_p
 *
 * @desc
 *   Increments components_num and pushes
 *   a table fragment size to the stack
 * @param tf_size
 *   Size to push
 * @param tf_info
 *   Info to push
 * @return
 *    0 on success
 *   -1 if allocate fails
 */
int JEL_component_stack_push_p(size_t tf_size, struct JEL_FragmentInfo *tf_info)
{
  if (JEL_context_current->component_stack->allocated <= JEL_context_current->component_stack->components_num) {
    if (JEL_component_stack_allocate_p(JEL_context_current->component_stack, JEL_context_current->component_stack->allocated * 1.618)) {
      struct JEL_Error e = {"Could not allocate when pushing to a JEL_ComponentStack", -1};
      return -1;
    }
  }

  JEL_context_current->component_stack->fragments_sizes[JEL_context_current->component_stack->components_num] = tf_size;
  JEL_context_current->component_stack->fragments_infos[JEL_context_current->component_stack->components_num] = tf_info;

  ++JEL_context_current->component_stack->components_num;

  return 0;
}

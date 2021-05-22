#include "error_utility.h"
#include <stdlib.h>
#include <string.h>

/*
 * JEL_error_stack_create
 *
 * @desc
 *   Creates a JEL error stack
 * @return
 *   A pointer to aJEL_ErrorStack or NULL on failure
 */
struct JEL_ErrorStack * JEL_error_stack_create_p(void)
{
  const int initial_count = 10;

  struct JEL_ErrorStack *new_error_stack;
  if (!(new_error_stack = malloc(sizeof(struct JEL_ErrorStack)))) {
    struct JEL_Error e = {"Cannot allocate an error stack", -1};
    JEL_error_push(e);
    return NULL;
  }

  struct JEL_ErrorStack new_error_stack_values = {0};
  *new_error_stack = new_error_stack_values;

  /* Allocate 10 errors */
  if (!(new_error_stack->errors = malloc(initial_count * sizeof(struct JEL_Error)))) {
    struct JEL_Error e = {"Cannot allocate an error stack'a errors", -1};
    JEL_error_push(e);
    return NULL;
  }
  new_error_stack->errors_allocated = initial_count;

  return new_error_stack;
}

/*
 * JEL_error_stack_destroy
 *
 * @desc
 *   Cleans up a JEL_ErrorStack
 * @param error_stack
 *   Error stack to destroy
 * @return
 *   0 on success
 */
int JEL_error_stack_destroy_p(struct JEL_ErrorStack *error_stack)
{
  free(error_stack->errors);
  free(error_stack);

  return 0;
}

/*
 * JEL_error_stack_errors_allocate
 *
 * @desc
 *   Allocates JEL_ErrorStack errors
 * @param error_stack
 *   Error stack to allocate errors for
 * @param count
 *   How many errors to allocate
 * @return
 *    0 on success
 *   -1 if already allocated
 *   -2 if malloc failed
 */
int JEL_error_stack_errors_allocate_p(struct JEL_ErrorStack *error_stack, uint32_t count)
{
  if (count <= error_stack->errors_allocated) {
    return -1;
  }

  struct JEL_Error *new_errors;

  if (!(new_errors = malloc(count * sizeof(struct JEL_Error)))) {
    struct JEL_Error e = {"Cannot malloc new errors", JEL_ERROR_MALLOC};
    JEL_error_push(e);
    return JEL_ERROR_MALLOC;
  }

  /* Copy, free and assign */
  memcpy(new_errors, error_stack->errors, error_stack->errors_num * sizeof(struct JEL_Error));
  free(error_stack->errors);
  error_stack->errors = new_errors;

  error_stack->errors_allocated = count;

  return 0;
}

#include "core.h"
#include "error.h"
#include "error_util.h"

// ========================================
// JEL_push_error
//
// @desc
//   Push an error to the stack
// @param error
//   The error
// @return
//    0 if succes
//   -1 if stack is at max
//   -2 if allocation failed
// ========================================
int JEL_error_push(struct JEL_Error error)
{
  if (JEL_context_current->error_stack->errors_num < JEL_ERROR_STACK_ERRORS_MAX) {
    if (JEL_context_current->error_stack->errors_allocated <= JEL_context_current->error_stack->errors_num) {
      if (JEL_error_stack_errors_allocate(JEL_context_current->error_stack, JEL_context_current->error_stack->errors_allocated * 1.618)) {
        return -2;
      }
    }
   
    JEL_context_current->error_stack->errors[JEL_context_current->error_stack->errors_num++] = error;

    return 0;
  }

  return -1;
}

// ========================================
// JEL_pop_error
//
// @desc
//   Pops the latest error from the stack
// @return
//   Popped error
// ========================================
struct JEL_Error JEL_error_pop(void)
{
  if (JEL_context_current->error_stack->errors_num == 0) {
    struct JEL_Error e = { "No errors", 0 };
    return e;
  }

  return JEL_context_current->error_stack->errors[--JEL_context_current->error_stack->errors_num];
}

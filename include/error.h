#ifndef JEL_ERROR_H
#define JEL_ERROR_H

#include <stdint.h>

/*
 * JEL_Error
 *
 * Internal error management
 * Uses a stack to track all the errors
 *
 * I'm hoping one does not reach 128 errors
 */

struct JEL_Error {
  char const *message;
  int         status;
};

#define JEL_ERROR_STACK_ERRORS_MAX 128

struct JEL_ErrorStack {
  struct JEL_Error *errors;
  uint32_t          errors_num;
  uint32_t          errors_allocated;
};

int              JEL_error_push(struct JEL_Error);
struct JEL_Error JEL_error_pop(void);

#endif

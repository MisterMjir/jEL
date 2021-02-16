#ifndef ERROR_UTIL_H
#define ERROR_UTIL_H

#include "error.h"

struct JEL_ErrorStack * JEL_error_stack_create(void);
int                     JEL_error_stack_destroy(struct JEL_ErrorStack *);

int                     JEL_error_stack_errors_allocate(struct JEL_ErrorStack *, uint32_t);

#endif

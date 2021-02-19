#ifndef JEL_COMPONENT_STACK_UTILITY_H
#define JEL_COMPONENT_STACK_UTILITY_H

#include "component/component_stack.h"
#include "component_types.h"

// Component Stack
struct JEL_ComponentStack * JEL_component_stack_create(void);
int                         JEL_component_stack_destroy(struct JEL_ComponentStack *);

int                         JEL_component_stack_tables_push(struct JEL_ComponentStack *, void *);
int                         JEL_component_stack_tables_allocate(struct JEL_ComponentStack *, JEL_ComponentInt);

#endif

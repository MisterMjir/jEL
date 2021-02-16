#ifndef COMPONENT_STACK_UTILITY_H
#define COMPONENT_STACK_UTILITY_H

#include "component_stack.h"

struct JEL_ComponentStack * JEL_component_stack_create(void);
int                         JEL_component_stack_destroy(struct JEL_ComponentStack *);

int                         JEL_component_stack_infos_push(struct JEL_ComponentStack *, struct JEL_ComponentInfo);
int                         JEL_component_stack_infos_allocate(struct JEL_ComponentStack *, JEL_ComponentInt);

int                         JEL_component_stack_tables_push(struct JEL_ComponentStack *, void *);
int                         JEL_component_stack_tables_allocate(struct JEL_ComponentStack *, JEL_ComponentInt);

#endif

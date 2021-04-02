#ifndef JEL_COMPONENT_STACK_UTILITY_H
#define JEL_COMPONENT_STACK_UTILITY_H

#include "component/component_stack.h"

struct JEL_ComponentStack * JEL_component_stack_create_p(void);
int                         JEL_component_stack_destroy_p(struct JEL_ComponentStack *);

int                         JEL_component_stack_allocate_p(struct JEL_ComponentStack *, JEL_ComponentInt);

int                         JEL_component_stack_push_p(size_t, struct JEL_FragmentInfo *);

#endif

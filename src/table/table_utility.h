#include "table/table.h"

struct JEL_TableStack * JEL_table_stack_create_p(void);
int                     JEL_table_stack_destroy_p(struct JEL_TableStack *);

int                     JEL_table_stack_allocate_p(struct JEL_TableStack *, JEL_ComponentInt);

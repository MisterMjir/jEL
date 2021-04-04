#include "table/table.h"

struct JEL_Table *      JEL_table_create_p(JEL_ComponentInt, ...);
int                     JEL_table_destroy_p(struct JEL_Table *);

int                     JEL_table_add_p(struct JEL_Table *, ...);
int                     JEL_table_remove_p(struct JEL_Table *, JEL_Entity);

int                     JEL_table_allocate_p(struct JEL_Table *, JEL_EntityInt);

struct JEL_TableStack * JEL_table_stack_create_p(void);
int                     JEL_table_stack_destroy_p(struct JEL_TableStack *);

int                     JEL_table_stack_push_p(struct JEL_Table *);

int                     JEL_table_stack_allocate_p(struct JEL_TableStack *, JEL_ComponentInt);

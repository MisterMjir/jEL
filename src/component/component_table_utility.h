#include "component/component_table.h"


struct JEL_ComponentTables * JEL_component_tables_create_p(void);
int                          JEL_component_tables_destroy_p(struct JEL_ComponentTables *);

int                          JEL_component_tables_allocate_p(struct JEL_ComponentTables *, JEL_ComponentInt);

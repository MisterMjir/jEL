#include "table/table.h"
#include "core.h"
#include <stdlib.h>

// ========================================
// TODO: Could use hash map or sparse set
// ========================================
struct JEL_Table * JEL_table_get(JEL_Type id)
{
  for (int i = 0; i < JEL_context_current->table_stack->tables_num; ++i) {
    for (int j = 0; j < JEL_TYPE_INTS; ++j) {
      if (id[j] != JEL_context_current->table_stack->tables_types[i][j]) {
        continue;
      }
    }

    return JEL_context_current->table_stack->tables[i];
  }

  return NULL;
}

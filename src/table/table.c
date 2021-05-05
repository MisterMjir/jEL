#include "table/table.h"
#include "core.h"
#include <stdlib.h>

/*
 * JEL_table_get
 *
 * TODO: Could use hash map or sparse set
 *
 * @desc
 *   Gets a table with the matching id
 * @param id
 *   Id of table to get
 * @return
 *   Matched table, NULL if there are no matches
 */
struct JEL_Table * JEL_table_get(JEL_Type id)
{
  for (int i = 0; i < JEL_context_current->table_stack->tables_num; ++i) {
    for (int j = 0; j < JEL_TYPE_INTS; ++j) {
      if (id[j] != JEL_context_current->table_stack->tables_types[i][j]) {
        break;
      }
      return JEL_context_current->table_stack->tables[i];
    }
  }

  return NULL;
}

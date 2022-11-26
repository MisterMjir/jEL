#include "query.h"
#include <stdlib.h>
#include "core.h"
#include "logger/logger.h"

/*
 * JEL_query_create
 *
 * @desc
 *   Creates a query based on a type
 * @param type
 *   Type of the query to match
 * @return
 */
int JEL_query_create(struct JEL_Query *q, JEL_Type type)
{
  q->count = 0;

  for (unsigned int i = 0; i < JEL_CTX->table_stack.count; ++i) {
    int matched = 0;
    for (int j = 0; j < JEL_TYPE_INTS; ++j) {
      if ((JEL_CTX->table_stack.tables[i]->type[j] & type[j]) != type[j]) {
        break;
      }
      else {
        ++matched;
      }
    }
    if (matched == JEL_TYPE_INTS) {
      ++q->count;
    }
  }

  if (!q->count) {
    q->tables = NULL;
    return 0;
  }

  if (!(q->tables = malloc(q->count * sizeof(struct JEL_Table *)))) {
    JEL_log("Query failed: Out of memory");
    return -1;
  }

  int temp = 0;
  for (unsigned int i = 0; i < JEL_CTX->table_stack.count; ++i) {
    int matched = 0;
    for (int j = 0; j < JEL_TYPE_INTS; ++j) {
      if ((JEL_CTX->table_stack.tables[i]->type[j] & type[j]) != type[j]) {
        break;
      }
      else {
        ++matched;
      }
    }
    if (matched == JEL_TYPE_INTS) {
      q->tables[temp++] = JEL_CTX->table_stack.tables[i];
    }
  }

  return 0;
}

/*
 * JEL_query_destroy
 *
 * @desc
 *   Cleans up a query
 * @param query
 *   Query to destroy
 * @return
 *   0 on success
 */
int JEL_query_destroy(struct JEL_Query *query)
{
  free(query->tables);

  return 0;
}

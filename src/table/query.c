#include "table/query.h"
#include <stdlib.h>
#include "core.h"

// ========================================
// JEL_query_create
//
// @desc
//   Creates query given type indices
// @param num
//   How many types in query
// @param ...
//   Type indicies
// @return
//   // TODO: Doesn't work
// ========================================
struct JEL_Query * JEL_query_create(JEL_ComponentInt num, ...)
{
  return NULL;
}

// ========================================
// JEL_query_create_type
//
// @desc
//   Creates a query based on a type
// @param type
//   Type of the query to match
// @return
//   A pointer to a query, NULL on failure
// ========================================
struct JEL_Query * JEL_query_create_type(JEL_Type type)
{
  struct JEL_Query *new_query;

  if (!(new_query = malloc(sizeof(struct JEL_Query)))) {
    return NULL;
  }

  new_query->tables_num = 0;

  for (JEL_ComponentInt i = 0; i < JEL_context_current->table_stack->tables_num; ++i) {
    int matched = 0;
    for (int j = 0; j < JEL_TYPE_INTS; ++j) {
      if ((JEL_context_current->table_stack->tables_types[i][j] & type[j]) != type[j]) {
        break;
      }
      else {
        ++matched;
      }
    }
    if (matched == JEL_TYPE_INTS) {
      ++new_query->tables_num;
    }
  }

  if (!(new_query->tables = malloc(new_query->tables_num * sizeof(struct JEL_Table *)))) {
    return NULL;
  }

  int temp = 0;
  for (JEL_ComponentInt i = 0; i < JEL_context_current->table_stack->tables_num; ++i) {
    int matched = 0;
    for (int j = 0; j < JEL_TYPE_INTS; ++j) {
      if ((JEL_context_current->table_stack->tables_types[i][j] & type[j]) != type[j]) {
        break;
      }
      else {
        ++matched;
      }
    }
    if (matched == JEL_TYPE_INTS) {
      new_query->tables[temp++] = JEL_context_current->table_stack->tables[i];
    }
  }

  return new_query;
}

// ========================================
// JEL_query_destroy
//
// @desc
//   Cleans up a query
// @param query
//   Query to destroy
// @return
//   0 on success
// ========================================
int JEL_query_destroy(struct JEL_Query *query)
{
  free(query->tables);
  free(query);

  return 0;
}
#include "table.h"
#include <stdlib.h>
#include <string.h>
#include "logger/logger.h"

#define INITIAL_COUNT 8

/*
 *
 */
int JEL_table_stack_create(struct JEL_TableStack *stack)
{
  if (!(stack->tables = malloc(INITIAL_COUNT * sizeof(*stack->tables)))) {
    JEL_log("Could not create table stack: Out of memory");
    return -1; 
  }

  stack->count = 0;
  stack->allocated = INITIAL_COUNT;

  return 0;
}

/*
 *
 */
void JEL_table_stack_destroy(struct JEL_TableStack *stack)
{
  for (unsigned int i = 0; i < stack->count; ++i) {
    JEL_table_destroy(stack->tables[i]);
    free(stack->tables[i]);
  }
  free(stack->tables);
}

/*
 *
 */
struct JEL_Table * JEL_table_stack_push(struct JEL_TableStack *stack, JEL_Type type)
{
  if (stack->allocated <= stack->count) {
    if (JEL_table_stack_allocate(stack, (unsigned int) (stack->count * 1.618))) {
      JEL_log("Could not allocate table stack: Out of memory");
      return NULL;
    }
  }

  if (!(stack->tables[stack->count] = malloc(sizeof(*stack->tables[stack->count])))) {
    JEL_log("Could not push to table stack: Out of memory");
    return NULL;
  }
  JEL_table_create(stack->tables[stack->count], type);

  return stack->tables[stack->count++];
}

/*
 *
 */
int JEL_table_stack_allocate(struct JEL_TableStack *stack, unsigned int count)
{
  if (count <= stack->allocated) {
    JEL_log("Could not allocate table stack: Already have enough memory");
    return -1;
  }

  struct JEL_Table **tables;

  if (!(tables = malloc(count * sizeof(*tables)))) {
    JEL_log("Could not allocate table stack: Out of memory");
    return -1;
  }

  memcpy(tables, stack->tables, stack->count * sizeof(*tables));
  free(stack->tables);
  stack->tables = tables;

  return 0;
}

/*
 *
 */
struct JEL_Table * JEL_table_stack_get(struct JEL_TableStack *stack, JEL_Type type)
{
  for (unsigned int i = 0; i < stack->count; ++i) {
    if (JEL_type_cmp(type, stack->tables[i]->type)) {
      return stack->tables[i];
    }
  }

  return NULL;
}

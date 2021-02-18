#include "component/component_stack_utility.h"
#include "error.h"
#include <stdlib.h>
#include <string.h>
#include "component/component_table_utility.h"
#include "component/component.h"

// ========================================
// JEL_component_stack_create
//
// @desc
//   Creates a component stack
// @return
//   Pointer to the newly created component
//   stack, NULL on failure
// ========================================
struct JEL_ComponentStack * JEL_component_stack_create(void)
{
  const int initial_count = 8;

  struct JEL_ComponentStack *new_component_stack;

  // Malloc structure
  if (!(new_component_stack = malloc(sizeof(struct JEL_ComponentStack)))) {
    struct JEL_Error e = {"Could not malloc a struct JEL_ComponentStack", -1}; 
    JEL_error_push(e);
    return NULL;
  }

  // Malloc and set members
  if (!(new_component_stack->tables = malloc(initial_count * sizeof(void *)))) {
    struct JEL_Error e = {"Could not malloc a struct JEL_ComponentStack's tables", -1}; 
    JEL_error_push(e);
    return NULL;
  }
  new_component_stack->tables_allocated = initial_count;
  new_component_stack->tables_num = 1; // 0 will be a unregistered/NULL component

  return new_component_stack;
}

// ========================================
// JEL_component_stack_destroy
//
// @desc
//   Cleans up a component stack
// @param component_stack
//   Component stack to destroy
// @return
//   0 on success
// ========================================
int JEL_component_stack_destroy(struct JEL_ComponentStack *component_stack)
{
  for (JEL_ComponentInt i = 0; i < component_stack->tables_num; ++i) {
    JEL_component_table_destroy(component_stack->tables[i]);
  }
  free(component_stack->tables);

  free(component_stack);

  return 0;
}

// ========================================
// JEL_component_stack_tables_push
//
// @desc
//   Pushes a table onto the stack
// @param component_stack
//   Component stack to modify
// @param table
//   Table to add
// @return
//    0 on success
//   -1 if stack is at max
//   -2 if malloc failed
// ========================================
int JEL_component_stack_tables_push(struct JEL_ComponentStack *component_stack, void *table)
{
  if (component_stack->tables_num < JEL_COMPONENT_MAX) {
    if (component_stack->tables_allocated <= component_stack->tables_num) {
      if (JEL_component_stack_tables_allocate(component_stack, component_stack->tables_allocated * 1.618)) {
        struct JEL_Error e = {"Could not allocate JEL_ComponentStack tables", -1};
        JEL_error_push(e);
        return -2;
      }
    }

    component_stack->tables[component_stack->tables_num++] = table;

    return 0;
  }

  struct JEL_Error e = {"JEL_ComponentStack is at max capacity", -1};
  JEL_error_push(e);
  return -1;
}

// ========================================
// JEL_component_stack_tables_allocate
//
// @desc
//   Allocates memoery for a component stack's tables
// @param component_stack
//   Component stack to allocate tables for
// @param count
//   How many tables to allocate
// @return
//    0 on success
//   -1 if already allocated
//   -2 if malloc failed
// ========================================
int JEL_component_stack_tables_allocate(struct JEL_ComponentStack *component_stack, JEL_ComponentInt count)
{
  if (count <= component_stack->tables_allocated)
    return -1;

  void **new_component_tables;

  if (!(new_component_tables = malloc(count * sizeof(void *)))) {
    struct JEL_Error e = {"Could not allocate JEL_ComponentStack tables", -1};
    JEL_error_push(e);
    return -2;
  }

  // Copy, free, and assign
  memcpy(new_component_tables, component_stack->tables, component_stack->tables_num * sizeof(void *));
  free(component_stack->tables);
  component_stack->tables = new_component_tables;

  component_stack->tables_allocated = count;

  return 0;
}


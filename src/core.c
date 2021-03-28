#include "core.h"
#include <stdlib.h>
#include "entity/entity_utility.h"
#include "error/error_utility.h"
#include "table/table_utility.h"
#include "table/table_fragment.h"
#include <string.h>

struct JEL_Context *JEL_context_current = NULL;

JEL_COMPONENT_CREATE(JEL_EntityC, JEL_EntityInt, entity)

// ========================================
// JEL_context_create
//
// @desc
//      Creates a new JEL_Context
// @return
//      A pointer to a JEL_Context, NULL on failure
// ========================================
int JEL_init(void)
{
  if (JEL_context_current != NULL)
    return -2;

  if (!(JEL_context_current = malloc(sizeof(struct JEL_Context)))) {
    // Can't set error because ctx failed to create :(
    return -1;
  }

  // Error Stack
  if (!(JEL_context_current->error_stack = JEL_error_stack_create_p())) {
    return -1;
  }

  // Entity Manager
  if (!(JEL_context_current->entity_manager = JEL_entity_manager_create_p())) {
    struct JEL_Error e = {"Could not create JEL_EntityManager", -1};
    JEL_error_push(e);
    return -1;
  }

  // Component Tables
  if (!(JEL_context_current->table_stack = JEL_table_stack_create_p())) {
    struct JEL_Error e = {"Could not create JEL_ComponentStack", -1};
    JEL_error_push(e);
    return -1;
  }

  JEL_context_current->components_registered = 0;

  // Set up the default table for plain entities (no components)
  JEL_COMPONENT_REGISTER(JEL_EntityC);

  // Create the fragment
  struct JEL_EntityCFragment entity_fragment = {
    .head = (struct JEL_TableFragmentHead_P){
      .info = &JEL_EntityC_info,
      .buffer_start = NULL
    },
    .entity = NULL
  };

  struct JEL_EntityCFragment *efp = malloc(sizeof(struct JEL_EntityCFragment));
  memcpy(efp, &entity_fragment, sizeof(struct JEL_EntityCFragment));

  // Create the table
  JEL_table_stack_push_p(JEL_table_create_p(1, JEL_EntityC_id, efp));

  return 0;
}

// ========================================
// JEL_context_destroy
//
// @desc
//      Destroys JEL_Context
// @return
//      Success
// ========================================
int JEL_quit(void)
{
  if (JEL_context_current == NULL)
    return -1;

  JEL_table_stack_destroy_p(JEL_context_current->table_stack);
  JEL_entity_manager_destroy_p(JEL_context_current->entity_manager);
  JEL_error_stack_destroy_p(JEL_context_current->error_stack);
  free(JEL_context_current);

  JEL_context_current = NULL;

  return 0;
}

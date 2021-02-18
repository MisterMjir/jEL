#include "core.h"
#include <stdlib.h>
#include "entity/entity_util.h"
#include "error/error_util.h"
#include "component/component_stack_utility.h"

struct JEL_Context *JEL_context_current = NULL;

// ========================================
// JEL_context_create
//
// @desc
//      Creates a new JEL_Context
// @return
//      A pointer to a JEL_Context, NULL on failure
// ========================================
struct JEL_Context * JEL_context_create(void)
{
  struct JEL_Context *new_ctx;
  if (!(new_ctx = malloc(sizeof(struct JEL_Context)))) {
    // Can't set error because ctx failed to create :(
    return NULL;
  }

  // Error Stack
  if (!(new_ctx->error_stack = JEL_error_stack_create())) {
    return NULL;
  }

  // Entity Manager
  if (!(new_ctx->entity_manager = JEL_entity_manager_create())) {
    struct JEL_Error e = {"Could not create JEL_EntityManager", -1};
    JEL_error_push(e);
    return NULL;
  }

  // Component Stack
  if (!(new_ctx->component_stack = JEL_component_stack_create())) {
    struct JEL_Error e = {"Could not create JEL_ComponentStack", -1};
    JEL_error_push(e);
    return NULL;
  }

  return new_ctx;
}

// ========================================
// JEL_context_destroy
//
// @desc
//      Destroys JEL_Context
// @return
//      Success
// ========================================
int JEL_context_destroy(struct JEL_Context *ctx)
{
  JEL_component_stack_destroy(ctx->component_stack);
  JEL_entity_manager_destroy(ctx->entity_manager);
  JEL_error_stack_destroy(ctx->error_stack);
  free(ctx);

  return 0;
}

// ========================================
// JEL_context_set_current
//
// @desc
//      Sets a JEL_Context to the current one
// @return
//      Success
// ========================================
int JEL_context_set_current(struct JEL_Context *ctx)
{
  JEL_context_current = ctx;

  return 0;
}

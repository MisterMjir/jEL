#ifndef JEL_CONTEXT_H
#define JEL_CONTEXT_H

#include "entity.h"
#include "error.h"
#include "component/component_table.h"

// ========================================
//
// JEL_Context
//
// The ECS library needs to have certain
// 'global' variables, but these are implemented
// as contexes. Whenever functions are called,
// they will be referencing a current context
//
// For example, a context will have an
// JEL_EntityManager, creating an entity creates
// affects the EntityManager of the current context,
// but in theory you can have multiple contexes
// (not sure when this is useful, perhaps your game
//  has two 'games' inside it which need switching)
//
// ========================================

struct JEL_Context {
  struct JEL_ErrorStack      *error_stack;
  struct JEL_EntityManager   *entity_manager;
  struct JEL_ComponentTables *component_tables;
  JEL_ComponentInt            components_registered;
};

#endif

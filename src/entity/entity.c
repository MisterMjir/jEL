#include "entity.h"
#include "entity_utility.h"
#include "core.h"
#include "component/component.h"
#include "table/table_utility.h"

// ========================================
// JEL_entity_create
//
// @desc
//   Creates an entity
//   TODO: Return a null entity if there
//   are too many entities
// @return
//   The newly created entity (0 if failed)
// ========================================
JEL_Entity JEL_entity_create(void)
{
  struct JEL_EntityManager *e_m = JEL_context_current->entity_manager;
  
  JEL_Entity new_entity = 0;

  // Try to reuse an index before creating new generations
  if (e_m->free_indices_num > 0) {
    // Use indices from the end to the front (basically it's a stack)
    
    JEL_EntityInt generation = e_m->generations[e_m->free_indices[--e_m->free_indices_num]];

    new_entity = (generation << JEL_ENTITY_INDEX_BITS) | e_m->free_indices[e_m->free_indices_num];
  }
  else {
    if (e_m->entities_num == e_m->entities_allocated) {
      if (JEL_entity_manager_allocate_p(e_m, e_m->entities_allocated * 1.618)) {
        struct JEL_Error e = {"Could not allocate JEL_EntityManager generations when creating entity", -1};
        JEL_error_push(e);
        return 0;
      }
    }

    // Generation allocation uses calloc, so it will already be 0
    new_entity = e_m->entities_num++; // Pre-increment skips index 1
  }

  // Add the entity to a table of entities with no components by default
  // Doesn't use the macro because the macro moves the entitiy out of a table,
  // there is not table yet
  // TODO: This bit of code isn't clean
  
  // Reset the id to ...010
  for (int i = 0; i < JEL_TYPE_INTS; ++i)
    e_m->types[JEL_entity_index_get(new_entity)][i] = 0;
  e_m->types[JEL_entity_index_get(new_entity)][0] = 2; // 2nd bit on, 1st bit could be any unregistered component

  // The first table will always be the plain entity table
  JEL_table_add_p(JEL_context_current->table_stack->tables[0], new_entity);

  return new_entity;
}

// ========================================
// JEL_entity_destroy
//
// @desc
//      Destroys an entity
//      Internally this just marks the index
//      as free and increases the generation
//      of that index
// @param entity
//      The entity to destory
// @return
//       0 for success
//      -1 if failed to allocate free indices
// ========================================
int JEL_entity_destroy(JEL_Entity entity)
{
  struct JEL_EntityManager *e_m = JEL_context_current->entity_manager;
  
  if (e_m->free_indices_num == e_m->free_indices_allocated) {
    if (!JEL_entity_manager_free_indices_allocate_p(e_m, e_m->free_indices_allocated * 1.618)) {
      struct JEL_Error e = {"Could not allocate JEL_EntityManager free_indices when destroying entity", -1};
      JEL_error_push(e);
      return -1;
    }
  }

  ++e_m->generations[JEL_entity_index_get(entity)];
  e_m->free_indices[e_m->free_indices_num++] = JEL_entity_index_get(entity);

  return 0;
}

// ========================================
// JEL_entity_get_index
//
// @desc
//      Gets an entity's index
// @param entity
//      The entity you want to get the index for
// @return
//      The entity's index
// ========================================
JEL_EntityInt JEL_entity_index_get(JEL_Entity entity)
{
  // Example of 8 bit entites, half and half index and generation
  // 0000 (Start)
  // 0100 (<<)
  // 0011 (-1)
  //
  // 1110 & 0011 = 0010

  return entity & ((1 << JEL_ENTITY_INDEX_BITS) - 1);
}

// ========================================
// JEL_entity_get_generation
//
// @desc
//      Gets an entity's generation
// @param entity
//      The entity you want to get the generation for
// @return
//      The entity's generation
// ========================================
JEL_EntityInt JEL_entity_generation_get(JEL_Entity entity)
{
  // Logic is pretty much the same as get index
  // There is an extra step, which is shift the
  // generation to the beginning

  return (entity >> JEL_ENTITY_INDEX_BITS) & ((1 << JEL_ENTITY_GENERATION_BITS) - 1);
}

// ========================================
// JEL_entity_is_alive
//
// @desc
//      Checks if an Entity is alive or not
// @param entity
//      Entity to check if it's alive or not
// @return
//       -1 if the entity is invalid
//        0 if the entity is alive
//      > 0 if the entity isn't alive
// ========================================

int JEL_entity_is_alive(JEL_Entity entity)
{
  if (JEL_entity_index_get(entity) >= JEL_context_current->entity_manager->entities_num) {
    return -1;
  }

  // Subtract generations at the same index to see if the entity is alive
  return JEL_entity_generation_get(entity) - JEL_context_current->entity_manager->generations[JEL_entity_index_get(entity)];
}

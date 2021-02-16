#include "entity.h"
#include "entity_util.h"
#include "core.h"

// ========================================
// JEL_entity_create
//
// @desc
//      Creates an entity
// @return
//      The newly created entity (0 if failed)
// ========================================
JEL_Entity JEL_entity_create(void)
{
  struct JEL_EntityManager *e_m = JEL_context_current->entity_manager;

  // Try to reuse an index before creating new generations
  if (e_m->free_indices_num > 0) {
    // Use indices from the end to the front (basically it's a stack)
    JEL_EntityInt generation = e_m->generations[e_m->free_indices[--e_m->free_indices_num]];

    return (generation << JEL_ENTITY_INDEX_BITS) | e_m->free_indices[e_m->free_indices_num];
  }
  else {
    if (e_m->generations_num == e_m->generations_allocated) {
      if (JEL_entity_manager_generations_allocate(e_m, e_m->generations_allocated * 1.618))
        return 0;
    }

    // Generation allocation uses calloc, so it will already be 0
    return ++e_m->generations_num;
  }

  return 0;
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
//      !0 for fail
// ========================================
int JEL_entity_destroy(JEL_Entity entity)
{
  struct JEL_EntityManager *e_m = JEL_context_current->entity_manager;
  
  if (e_m->free_indices_num == e_m->free_indices_allocated) {
    if (!JEL_entity_manager_free_indices_allocate(e_m, e_m->free_indices_allocated * 1.618)) {
      return -1;
    }
  }

  ++e_m->generations[JEL_entity_get_index(entity)];
  e_m->free_indices[e_m->free_indices_num++] = JEL_entity_get_index(entity);

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
JEL_EntityInt JEL_entity_get_index(JEL_Entity entity)
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
JEL_EntityInt JEL_entity_get_generation(JEL_Entity entity)
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
  if (JEL_entity_get_index(entity) >= JEL_context_current->entity_manager->generations_num) {
    return -1;
  }

  // Subtract generations at the same index to see if the entity is alive
  return JEL_entity_get_generation(entity) - JEL_context_current->entity_manager->generations[JEL_entity_get_index(entity)];
}

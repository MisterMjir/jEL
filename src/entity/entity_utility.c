#include "entity_utility.h"
#include "error.h"
#include <stdlib.h>
#include <string.h>

// ========================================
// JEL_entity_manager_create
//
// @desc
//   Creates a JEL_EntityManager
//   A macro for the malloc checking could be made,
//   it's repeated in many places
// @return
//   A pointer to a JEL_EntityManager, null
//   on failure
// ========================================
struct JEL_EntityManager * JEL_entity_manager_create_p(void)
{
  const int initial_count = 8;

  struct JEL_EntityManager *new_entity_manager;
  if (!(new_entity_manager = malloc(sizeof(struct JEL_EntityManager)))) {
    struct JEL_Error e = {"Could not allocate JEL_EntityManager", -1};
    JEL_error_push(e);
    return NULL;
  }

  // Initialize generations and types
  if (!(new_entity_manager->generations = calloc(initial_count, sizeof(JEL_EntityInt)))) {
    struct JEL_Error e = {"Could not allocate JEL_EntityManager generations", -1};
    JEL_error_push(e);
    return NULL;
  }
  if (!(new_entity_manager->types = malloc(initial_count * sizeof(JEL_Type)))) {
    struct JEL_Error e = {"Could not allocate JEL_EntityManager types", -1};
    JEL_error_push(e);
    return NULL;
  }
  new_entity_manager->entities_allocated = initial_count;
  new_entity_manager->entities_num = 1;

  // Initialize free_indices
  if (!(new_entity_manager->free_indices = malloc(initial_count * sizeof(JEL_EntityInt)))) {
    struct JEL_Error e = {"Could not allocate JEL_EntityManager free_indices", -1};
    JEL_error_push(e);
    return NULL;
  }
  new_entity_manager->free_indices_allocated = initial_count;
  new_entity_manager->free_indices_num = 0;

  return new_entity_manager;
}

// ========================================
// JEL_entity_manager_destroy
//
// @desc
//   Destroyes a JEL_EntityManager
// @param entity_manager
//   Entity manager to destroy
// @return
//   Success code
// ========================================
int JEL_entity_manager_destroy_p(struct JEL_EntityManager* entity_manager)
{
  free(entity_manager->generations);
  free(entity_manager->free_indices);
  free(entity_manager->types);
  free(entity_manager);

  return 0;
}

// ========================================
// JEL_entity_manager_generations_allocate
//
// @desc
//   Allocates memory for more generations
//   for a JEL_EntityManager
// @param entity_manager
//   Entity manager to allocate
// @param count
//   How many indices to allocate
// @return
//    0 on success
//   -1 if there is already enough memory
//   -2 if calloc failed
// ========================================
int JEL_entity_manager_allocate_p(struct JEL_EntityManager* entity_manager, JEL_EntityInt count)
{
  if (count <= entity_manager->entities_allocated)
    return -1;

  JEL_EntityInt *new_generations;
  JEL_Type      *new_types;

  if (!(new_generations = calloc(count, sizeof(JEL_EntityInt)))) {
    struct JEL_Error e = {"Could not allocate JEL_EntityManager generations", -1};
    JEL_error_push(e);
    return -2;
  }

  if (!(new_types = malloc(count * sizeof(JEL_Type)))) {
    struct JEL_Error e = {"Could not allocate JEL_EntityManager types", -1};
    JEL_error_push(e);
    return -2;
  }

  // Copy, free, and assign
  // TODO: There is probably a more efficient way to do this
  memcpy(new_generations, entity_manager->generations, sizeof(JEL_EntityInt) * entity_manager->entities_num);
  free(entity_manager->generations);
  entity_manager->generations = new_generations;

  memcpy(new_types, entity_manager->types, sizeof(JEL_Type) * entity_manager->entities_num);
  free(entity_manager->types);
  entity_manager->types = new_types;

  entity_manager->entities_allocated = count;

  return 0;
}

// ========================================
// JEL_entity_manager_free_indices_allocate
//
// @desc
//   Allocates memory for more free indicies
//   for a JEL_EntityManager
// @param entity_manager
//   Entity manager to allocate
// @param count
//   How many indices to allocate
// @return
//    0 on success
//   -1 if there is already enough memory
//   -2 if malloc failed
// ========================================
int JEL_entity_manager_free_indices_allocate_p(struct JEL_EntityManager* entity_manager, JEL_EntityInt count)
{
  if (count <= entity_manager->free_indices_allocated)
    return -1;

  JEL_EntityInt *new_free_indices;

  if (!(new_free_indices = malloc(sizeof(JEL_EntityInt) * count))) {
    struct JEL_Error e = {"Could not allocate JEL_EntityManager free_indices", -1};
    JEL_error_push(e);
    return -2;
  }

  // Copy, free, and assign
  // TODO: There is probably a more efficient way to do this
  memcpy(new_free_indices, entity_manager->free_indices, sizeof(JEL_EntityInt) * entity_manager->free_indices_num);
  free(entity_manager->free_indices);
  entity_manager->free_indices = new_free_indices;

  entity_manager->free_indices_allocated = count;

  return 0;
}

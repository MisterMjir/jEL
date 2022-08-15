#include "entity.h"
#include <stdlib.h>
#include <string.h>
#include "logger/logger.h"

#define INITIAL_COUNT 8

/*
* MALLOC
* 
* @desc
*   Malloc
* @param var
*   Member to allocate
* @param count
*   How much to allocate
*/
#define MALLOC(var, count) \
  if (!(em->var = malloc(count * sizeof(*em->var)))) { \
    JEL_log("Out of memory"); \
    return -1; \
  }

/*
 * CALLOC
 * 
 * @desc
 *   Calloc
 * @param var
 *   Member to allocate
 * @param count
 *   How much to allocate
 */
#define CALLOC(var, count) \
  if (!(em->var = calloc(count, sizeof(*em->var)))) { \
    JEL_log("Out of memory"); \
    return -1; \
  }

/*
 * MOVE
 *
 * @desc
 *   Replaces the dst buffer with the src buffer
 * @param src
 *   The new data
 * @param dst
 *   Where the data is going to end up
 * @param count
 *   How much of the src buffer to copy over
 */
#define MOVE(src, dst, count) \
  memcpy(src, dst, sizeof(*dst) * count); \
  free(dst); \
  dst = src;

 /*
  * COPYM
  * 
  * @desc
  *   Copies with malloc
  * @param var
  *   Member to copy
  * @param count
  *   How many items to allocate
  * @param num
  *   entities_num or free_indices_num
  */
#define COPYM(var, count, num) \
  void *JEL_new_##var; \
  if (!(JEL_new_##var = malloc(count * sizeof(*em->var)))) { \
    JEL_log("Cannot allocate entity manager: Out of memory"); \
    return -2; \
  } \
  MOVE(JEL_new_##var, em->var, em->num);

/*
 * COPYC
 * 
 * @desc
 *   Copies will calloc
 * @param var
 *   Member to copy
 * @param count
 *   How many items to allocate
 * @param num
 *   entities_num or free_indices_num
 */
#define COPYC(var, count, num) \
  void *JEL_new_##var; \
  if (!(JEL_new_##var = calloc(count, sizeof(*em->var)))) { \
    JEL_log("Cannot allocate entity manager: Out of memory"); \
    return -2; \
  } \
  MOVE(JEL_new_##var, em->var, em->num);

/*
 * JEL_entity_manager_create
 *
 * @desc
 *   Creates a JEL_EntityManager
 * @param em
 *   Reference to the entity manager to create
 * @return
 *   Error
 */
int JEL_entity_manager_create(struct JEL_EntityManager *em)
{
  /* Initialize generations, types, and table pointers */
  CALLOC(generations, INITIAL_COUNT);
  MALLOC(types, INITIAL_COUNT);
  MALLOC(table_ptrs, INITIAL_COUNT);

  em->entities_allocated = INITIAL_COUNT;
  em->entities_num = 1;

  /* Initialize free_indices */
  MALLOC(free_indices, INITIAL_COUNT);
  em->free_indices_allocated = INITIAL_COUNT;
  em->free_indices_num = 0;

  return 0;
}

/*
 * JEL_entity_manager_destroy
 *
 * @desc
 *   Destroyes a JEL_EntityManager
 * @param em
 *   Entity manager to destroy
 */
void JEL_entity_manager_destroy(struct JEL_EntityManager* em)
{
  free(em->generations);
  free(em->free_indices);
  free(em->types);
  free(em->table_ptrs);
}

/*
 * JEL_entity_manager_generations_allocate
 *
 * @desc
 *   Allocates memory for more generations
 *   for a JEL_EntityManager
 * @param em
 *   Entity manager to allocate
 * @param count
 *   How many indices to allocate
 * @return
 *    Error
 */
int JEL_entity_manager_allocate(struct JEL_EntityManager* em, JEL_EntityInt count)
{
  if (count <= em->entities_allocated) return -1;

  COPYC(generations, count, entities_num);
  COPYM(types, count, entities_num);
  COPYM(table_ptrs, count, entities_num);

  em->entities_allocated = count;

  return 0;
}

/*
 * JEL_entity_manager_free_indices_allocate
 *
 * @desc
 *   Allocates memory for more free indicies
 *   for a JEL_EntityManager
 * @param em
 *   Entity manager to allocate
 * @param count
 *   How many indices to allocate
 * @return
 *    Error
 */
int JEL_entity_manager_free_indices_allocate(struct JEL_EntityManager* em, JEL_EntityInt count)
{
  if (count <= em->free_indices_allocated) return -1;

  COPYM(free_indices, count, free_indices_num);

  em->free_indices_allocated = count;

  return 0;
}

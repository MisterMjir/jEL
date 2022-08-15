#include "entity.h"
#include "core.h"
#include "logger/logger.h"
#include "table.h"

#define GROWTH_FACTOR 2

/*
 * JEL_entity_create
 *
 * @desc
 *   Creates an entity
 * @return
 *   The newly created entity (0 if failed)
 */
JEL_Entity JEL_entity_create(void)
{
  struct JEL_EntityManager *e_m = &JEL_CTX->entity_manager;
 
  /* Check if an entity can be made */
  JEL_Entity new_entity = 0;
  if (e_m->entities_num == (1 << JEL_ENTITY_INDEX_BITS) - 1) {
    JEL_log("Cannot create new entity: Max entities are alive");
    return 0;
  }

  /* Try to reuse an index before creating new generations */
  if (e_m->free_indices_num > 0) {
    /* Use indices from the end to the front (basically it's a stack) */
    JEL_EntityInt generation = e_m->generations[e_m->free_indices[--e_m->free_indices_num]];

    new_entity = (generation << JEL_ENTITY_INDEX_BITS) | e_m->free_indices[e_m->free_indices_num];
  }
  else {
    if (e_m->entities_num == e_m->entities_allocated) {
      if (JEL_entity_manager_allocate(e_m, (JEL_EntityInt) (e_m->entities_allocated * GROWTH_FACTOR))) {
        JEL_log("Cannot allocate entity manager: Out of memory");
        return 0;
      }
    }

    /* Generation allocation uses calloc, so it will already be 0 */
    new_entity = e_m->entities_num++; /* Pre-increment skips index 1 */
  }

  /* Reset the id to ...010 */
  JEL_type_init(e_m->types[JEL_entity_index(new_entity)]);

  /* Add to a table */
  JEL_table_add(JEL_CTX->table_stack.tables[0], new_entity); /* 1st table is always the plain entity one */

  return new_entity;
}

/*
 * JEL_entity_destroy
 *
 * @desc
 *   Destroys an entity
 *   Internally this just marks the index
 *   as free and increases the generation
 *   of that index
 * @param entity
 *   The entity to destory
 * @return
 *    0 for success
 *   -1 if failed to allocate free indices
 */
int JEL_entity_destroy(JEL_Entity entity)
{
  if (!JEL_entity_alive(entity)) return 0;

  struct JEL_EntityManager *e_m = &JEL_CTX->entity_manager;
  
  if (e_m->free_indices_num == e_m->free_indices_allocated) {
    if (JEL_entity_manager_free_indices_allocate(e_m, (JEL_EntityInt) (e_m->free_indices_allocated * GROWTH_FACTOR))) {
      JEL_log("Could not allocated entity manager: Out of memory");
      return -1;
    }
  }

  /* Remove entity from the table it's in */
  struct JEL_Table *table = JEL_table_stack_get(&JEL_CTX->table_stack, JEL_CTX->entity_manager.types[JEL_entity_index(entity)]);
  JEL_table_remove(table, JEL_table_index(table, entity));

  /* Increase generations */
  ++e_m->generations[JEL_entity_index(entity)];
  e_m->free_indices[e_m->free_indices_num++] = JEL_entity_index(entity);

  return 0;
}

/*
 * JEL_entity_index
 *
 * @desc
 *   Gets an entity's index
 * @param entity
 *   The entity you want to get the index for
 * @return
 *   The entity's index
 */
JEL_EntityInt JEL_entity_index(JEL_Entity entity)
{
  /* 
   * Example of 8 bit entites, half and half index and generation
   * 0000 (Start)
   * 0100 (<<)
   * 0011 (-1)
   *
   * 1110 & 0011 = 0010
   */

  return entity & ((1 << JEL_ENTITY_INDEX_BITS) - 1);
}

/*
 * JEL_entity_gen
 *
 * @desc
 *   Gets an entity's generation
 * @param entity
 *   The entity you want to get the generation for
 * @return
 *   The entity's generation
 */
JEL_EntityInt JEL_entity_gen(JEL_Entity entity)
{
  /*
   * Logic is pretty much the same as get index
   * There is an extra step, which is shift the
   * generation to the beginning
   */

  return (entity >> JEL_ENTITY_INDEX_BITS) & ((1 << JEL_ENTITY_GENERATION_BITS) - 1);
}

/*
 * JEL_entity_is_alive
 *
 * @desc
 *   Checks if an Entity is alive or not
 * @param entity
 *   Entity to check if it's alive or not
 * @return
 *    0 if not alive
 *   !0 if alive
 */
int JEL_entity_alive(JEL_Entity entity)
{
  if (JEL_entity_index(entity) >= JEL_CTX->entity_manager.entities_num) {
    return 0;
  }

  /* Subtract generations at the same index to see if the entity is alive */
  return !(JEL_entity_gen(entity) - JEL_CTX->entity_manager.generations[JEL_entity_index(entity)]);
}

#ifndef JEL_ENTITY_H
#define JEL_ENTITY_H

#include <stdint.h>

// ========================================
//
// JEL_Entity
//
// Entities are simply numbers
// They are weak references, which is why some bits will go
// to their index, and some for their generation
//
// A generation is when an index has to be re-used
//
// All the entities will be stored in an array,
// and will be managed through JEL_EntityManager
//
// The reason for two typdefs is to distinguish
// what is an integer the same size as an entity,
// and what is an entity itself.
//
// It is typedef-ed because you don't need to
// use a uint32_t, you could do a uint64_t or
// uint16_t
//
// ========================================

#define JEL_ENTITY_INDEX_BITS      24
#define JEL_ENTITY_GENERATION_BITS  8

typedef uint32_t JEL_EntityInt;

typedef JEL_EntityInt JEL_Entity;

// ========================================
//
// JEL_EntityManager
//
//
// ========================================

struct JEL_EntityManager {
  JEL_EntityInt *generations;
  JEL_EntityInt  generations_num;
  JEL_EntityInt  generations_allocated;
  JEL_EntityInt *free_indices;
  JEL_EntityInt  free_indices_num;
  JEL_EntityInt  free_indices_allocated;
};

JEL_Entity    JEL_entity_create(void);
int           JEL_entity_destroy(JEL_Entity);
JEL_EntityInt JEL_entity_get_index(JEL_Entity);
JEL_EntityInt JEL_entity_get_generation(JEL_Entity);
int           JEL_entity_is_alive(JEL_Entity);

#endif

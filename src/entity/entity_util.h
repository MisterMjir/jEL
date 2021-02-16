#ifndef ENTITY_UTIL_H
#define ENTITY_UTIL_H

#include "entity.h"

struct JEL_EntityManager * JEL_entity_manager_create(void);
int                        JEL_entity_manager_destroy(struct JEL_EntityManager *);
int                        JEL_entity_manager_generations_allocate(struct JEL_EntityManager *, JEL_EntityInt);
int                        JEL_entity_manager_free_indices_allocate(struct JEL_EntityManager *, JEL_EntityInt);

#endif

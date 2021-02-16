#ifndef ENTITY_TEST_HPP
#define ENTITY_TEST_HPP

#include "../test.hpp"
#include "jel.h"
#include <math.h>
#include <time.h>

namespace Tests { namespace Basic {
  
class Entity : public Test
{
public:
  Entity()
  {
    name = "Basic::Entity";
  }

  int function()
  {
    // Timing stuff
    clock_t start, end;

    // Context initialization
    struct JEL_Context* ctx;

    if (!(ctx = JEL_context_create())) {
      printf("Could not create a context\n");
      return -1;
    }

    if (JEL_context_set_current(ctx)) {
      printf("Could not switch the current context\n");
      return -1;
    }

    // Entity creation
    JEL_Entity first_entity  = JEL_entity_create();

    for (int exp = 1; exp <= 6; ++exp)
    {
      // Create entities
      start = clock();
      for (int i = 0; i < pow(10, exp); ++i) {
        int entity = JEL_entity_create();
      }
      end = clock();
      printf("Took %f seconds to create %f entities\n", (double) (end - start) / CLOCKS_PER_SEC, pow(10, exp));

      // Print all entities
      // printf("Printing entities\n");
      // for (JEL_EntityInt i = 1; i < ctx->entity_manager->generations_num; ++i) {
      //   printf("Index: %d Generation: %d\n", i, ctx->entity_manager->generations[i]); 
      // }

      // Destroy all the entities
      start = clock();
      for (int i = 1; i < pow(10, exp); ++i) {
        JEL_entity_destroy((ctx->entity_manager->generations[i] << JEL_ENTITY_INDEX_BITS) | i);
      }
      end = clock();
      printf("Took %f seconds to destroy %f entities\n", (double) (end - start) / CLOCKS_PER_SEC, pow(10, exp));

      // printf("Free indices:\n");
      // for (JEL_EntityInt i = 0; i < ctx->entity_manager->free_indices_num; ++i) {
      //   printf("%d ", ctx->entity_manager->free_indices[i]);
      // }
      // printf("\n");
    }

    printf("Is first entity alive? (!0 is false) %d\n", JEL_entity_is_alive(first_entity));

    // Context clean up
    if (JEL_context_destroy(ctx)) {
      printf("Could not destroy the context\n");
      return -1;
    }

    return 0;
  }
};

}; };

namespace Tests { namespace Registrations {

Manager::Register<Basic::Entity> entity_test;

}; };

#endif

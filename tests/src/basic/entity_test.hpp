#ifndef ENTITY_TEST_HPP
#define ENTITY_TEST_HPP

#include "../test.hpp"
#include "jel.h"
#include <math.h>
#include <time.h>
#include <stdio.h>

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

    // Entity creation
    FILE *file_stats_creation = fopen("results/entity_creation_time_data.py", "w+");

    fprintf(file_stats_creation, "entity_creation_times = [");

    const JEL_EntityInt iterations = 1'000;
    const int increment_amount = 10;

    for (int i = 0; i < iterations; i += increment_amount)
    {
      // Create context
      if (!(ctx = JEL_context_create())) {
        printf("Could not create a context\n");
        return -1;
      }

      if (JEL_context_set_current(ctx)) {
        printf("Could not switch the current context\n");
        return -1;
      }

      // Create entities
      start = clock();
      for (int j = 0; j <= i; ++j) {
        int entity = JEL_entity_create();
      }
      end = clock();
      fprintf(file_stats_creation, "%f, ", (double) (end - start) / CLOCKS_PER_SEC);

      // Destroy all the entities
      start = clock();
      for (int j = 1; j <= i; ++j) {
        JEL_entity_destroy((ctx->entity_manager->generations[i] << JEL_ENTITY_INDEX_BITS) | i);
      }
      end = clock();
      //printf("Took %f seconds to destroy %f entities\n", (double) (end - start) / CLOCKS_PER_SEC, pow(10, exp));

      // printf("Free indices:\n");
      // for (JEL_EntityInt i = 0; i < ctx->entity_manager->free_indices_num; ++i) {
      //   printf("%d ", ctx->entity_manager->free_indices[i]);
      // }
      // printf("\n");
      
      // Destroy context
      if (JEL_context_destroy(ctx)) {
        printf("Could not destroy the context\n");
        return -1;
      }
    }

    fprintf(file_stats_creation, "]");
    fclose(file_stats_creation);

    return 0;
  }
};

}; };

namespace Tests { namespace Registrations {

Manager::Register<Basic::Entity> entity_test;

}; };

#endif

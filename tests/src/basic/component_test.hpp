#ifndef COMPONENT_TEST_HPP
#define COMPONENT_TEST_HPP

#include "../test.hpp"
#include "jel.h"

/*JEL_COMPONENT_CREATE(OneMember, int, _1)
JEL_COMPONENT_CREATE(MaxMembers,
  int, _01, int, _02, int, _03, int, _04,
  int, _05, int, _06, int, _07, int, _08,
  int, _09, int, _10, int, _11, int, _12,
  int, _13, int, _14, int, _15, int, _16,
  int, _17, int, _18, int, _19, int, _20,
  int, _21, int, _22, int, _23, int, _24,
  int, _25, int, _26, int, _27, int, _28,
  int, _29, int, _30, int, _31, int, _32
) */

JEL_COMPONENT_DEFINE(Position, int, x, int, y)
JEL_COMPONENT_CREATE(Position, int, x, int, y)

namespace Tests { namespace Basic {
  
class Component : public Test
{
public:
  Component()
  {
    name = "Basic::Component";
  }

  int function()
  {
    struct JEL_Context* ctx;

    if (JEL_init()) {
      printf("Could not create a context\n");
      return -1;
    }

    /*
     * This portion confirms registering works
     *
    for (int i = 0; i < 127; ++i) {
      JEL_COMPONENT_REGISTER(OneMember);
    }

    JEL_COMPONENT_REGISTER(Position);

    printf("Registered components: %d\n", ctx->components_registered);

    for (int i = 0; i < JEL_COMPONENT_ID_INTS; ++i) {
      printf("%u, ", OneMember_id[i]);
    }
    printf("\n");

    for (int i = 0; i < JEL_COMPONENT_ID_INTS; ++i) {
      printf("%u, ", Position_id[i]);
    }
    printf("\n");
    */

    /* Test if table pointers are correct
     *
    printf("Entity Table Pointer tests:\n");
    printf("Table buffer begin: %p\n", JEL_context_current->table_stack->tables[0]->buffer);
    printf("Table fragment buffer begin: %p\n", JEL_context_current->table_stack->tables[0]->fragments[0]->head.buffer_start);
    printf("Table fragment first pointer: %p\n", ((struct JEL_EntityCFragment *) JEL_context_current->table_stack->tables[0]->fragments[0])->entity);
     */

    if (JEL_quit()) {
      printf("Could not destroy the context\n");
      return -1;
    }

    return 0;
  }
};

}; };

namespace Tests { namespace Registrations {

Manager::Register<Basic::Component> component_test;

}; };

#endif


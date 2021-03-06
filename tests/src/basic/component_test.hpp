#ifndef COMPONENT_TEST_HPP
#define COMPONENT_TEST_HPP

#include "../test.hpp"
#include "jel.h"

JEL_COMPONENT_CREATE(OneMember, 1, int, _1)
JEL_COMPONENT_CREATE(MaxMembers, 32,
  int, _01, int, _02, int, _03, int, _04,
  int, _05, int, _06, int, _07, int, _08,
  int, _09, int, _10, int, _11, int, _12,
  int, _13, int, _14, int, _15, int, _16,
  int, _17, int, _18, int, _19, int, _20,
  int, _21, int, _22, int, _23, int, _24,
  int, _25, int, _26, int, _27, int, _28,
  int, _29, int, _30, int, _31, int, _32
)
JEL_COMPONENT_CREATE(Position, 2, int, x, int, y)

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

    if (!(ctx = JEL_context_create())) {
      printf("Could not create a context\n");
      return -1;
    }

    if (JEL_context_set_current(ctx)) {
      printf("Could not switch the current context\n");
      return -1;
    }

    JEL_COMPONENT_REGISTER(OneMember)

    JEL_COMPONENT_REGISTER(Position)
    printf("Position_id: %d\n", Position_id);
    printf("Allocated: %d\n", JEL_COMPONENT_TABLE_GET(Position)->head.allocated);
    printf("Size of int %zu\n", sizeof(int));
    printf("Member pointers: %p | %p\n", JEL_COMPONENT_TABLE_GET(Position)->x, JEL_COMPONENT_TABLE_GET(Position)->y);

    struct Position test_pos = {69, 420};
    JEL_COMPONENT_TABLE_DATA_ADD(Position, test_pos);

    printf("\nPosition x (index 1): %d\n", JEL_COMPONENT_TABLE_MEMBER_DATA_GET(Position, x, 1));
    printf("\nPosition y (index 1): %d\n", JEL_COMPONENT_TABLE_MEMBER_DATA_GET(Position, y, 1));

    JEL_component_table_allocate(JEL_COMPONENT_TABLE_GET(Position), 16);
    printf("\nAllocated to 16\n");

    printf("Allocated: %d\n", JEL_COMPONENT_TABLE_GET(Position)->head.allocated);
    printf("Size of int %zu\n", sizeof(int));
    printf("Member pointers: %p | %p\n", JEL_COMPONENT_TABLE_GET(Position)->x, JEL_COMPONENT_TABLE_GET(Position)->y);

    if (JEL_context_destroy(ctx)) {
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


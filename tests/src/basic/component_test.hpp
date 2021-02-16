#ifndef COMPONENT_TEST_HPP
#define COMPONENT_TEST_HPP

#include "../test.hpp"
#include "jel.h"

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


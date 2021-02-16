#ifndef CONTEXT_TEST_HPP
#define CONTEXT_TEST_HPP

#include "../test.hpp"
#include "jel.h"

namespace Tests { namespace Basic {
  
class Context : public Test
{
public:
  Context()
  {
    name = "Basic::Context";
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

    if (JEL_context_destroy(ctx)) {
      printf("Could not destroy the context\n");
      return -1;
    }

    return 0;
  }
};

}; };

namespace Tests { namespace Registrations {

Manager::Register<Basic::Context> context_test;

}; };

#endif

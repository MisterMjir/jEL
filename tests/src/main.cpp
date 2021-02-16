#include "tests.hpp"

/*
int entity_test(void)
{
  return 0;
}

struct Position {
  int x, y;
};

int component_test(void)
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

  JEL_COMPONENT_CREATE(Position);
  printf("Id of position component: %d\n", JEL_COMPONENT_GET_ID(Position));

  return 0;
}
*/

int main(int argc, char* args[])
{
  /*
  printf("Running context test\n");
  if (context_test()) {
    printf("Context test failed\n");
    return -1;
  }
  printf("Context test passed\n");

  printf("Running entity test\n");
  if (entity_test()) {
    printf("Entity test failed\n");
    return -1;
  }
  printf("Entity test passed\n");

  printf("Running component test\n");
  if (component_test()) {
    printf("Component test failed\n");
    return -1;
  }
  printf("Component test passed\n");
  */
  Tests::Manager::get_instance().run_tests();

  return 0;
}

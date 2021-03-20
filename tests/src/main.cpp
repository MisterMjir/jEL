#include "tests.hpp"

int main(int argc, char* args[])
{
  //Tests::Manager::get_instance().run_test<Tests::Basic::Context>();
  Tests::Manager::get_instance().run_tests();

  return 0;
}

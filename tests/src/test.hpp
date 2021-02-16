#ifndef TEST_HPP
#define TEST_HPP

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

namespace Tests {

class Test
{
public:
  virtual ~Test() {}
  virtual int function() = 0;
  std::string get_name() { return name; }
protected:
  std::string name;
};

class Manager
{
public:
  static Manager& get_instance()
  {
    static Manager instance;
    return instance;
  }

  template <typename T> class Register
  {
  public:
    Register()
    {
      static_assert(std::is_base_of<Test, T>::value, "Test does not derive from Test class");
      Manager::get_instance().tests.push_back(new T()); 
    }
  };

  int run_tests()
  {
    for (std::vector<Test*>::iterator i = tests.begin(); i < tests.end(); ++i)
    {
      std::cout << "========================================" << std::endl;
      std::cout << "Test: " << (*i)->get_name() << "\n" << std::endl;
      int result = (*i)->function();
      if (result)
      {
        std::cout << "\nTest failed with code " << result << "\nEnding tests." << std::endl;
        return result;
      }

      std::cout << "Test passed" << std::endl;
      std::cout << "========================================" << std::endl;
    }

    std::cout << "\nAll tests passed" << std::endl;
    return 0;
  }

  template <typename T> int run_test()
  {
    return get_test<T>()->function();
  }
private:
  Manager() {}
  ~Manager()
  {
    for (Test* t : tests)
      delete t;
  }

  std::vector<Test*> tests;
  std::size_t index = 0;

  template <typename T> T* get_test()
  {
    static std::size_t i = index == tests.size() - 1 ? index++ : throw std::logic_error("Unregistered test");
    return dynamic_cast<T*>(tests[i]);
  }
};

};

#endif

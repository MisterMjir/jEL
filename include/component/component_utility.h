#ifndef JEL_COMPONENT_UTILITY_H
#define JEL_COMPONENT_UTILITY_H

// These should be private macros
//
// ========================================
// Component Member stuff
//
// Since I need the types of the members
// to get the components in nice tables,
// I need a macro for creating components
//
// These macros iterate through all a component's
// members
//
// JEL_COMPONENT_MEMBERS_ITERATE iterates through all
// component members and sends them through a function
//
// The JEL_COMPONENT_MEMBERS_FUNCTION_GET gets which
// JEL_COMPONENT_MEMBERS_FUNCTION macro is needed
//
// The function should be a macro that takes a type and a
// name
//
// JEL_COMPONENT_MEMBERS_WITH_COMPONENT_ITERATE adds the
// component through the first parameter of the function
//
// You'll never need more than 16 members really but just in
// case I made it support the next power of 2, 32
//
// Variadic macro trick obtained from
// https://codecraft.co/2014/11/25/variadic-macro-tricks/
//
// A bash/python script to automate this would be nice...
// ========================================

#define JEL_COMPONENT_MEMBERS_MAX 32

#define JEL_COMPONENT_MEMBERS_FUNCTION_GET_P( \
    _01, _01a, _02, _02a, _03, _03a, _04, _04a, \
    _05, _05a, _06, _06a, _07, _07a, _08, _08a, \
    _09, _09a, _10, _10a, _11, _11a, _12, _12a, \
    _13, _13a, _14, _14a, _15, _15a, _16, _16a, \
    _17, _17a, _18, _18a, _19, _19a, _20, _20a, \
    _21, _21a, _22, _22a, _23, _23a, _24, _24a, \
    _25, _25a, _26, _26a, _27, _27a, _28, _28a, \
    _29, _29a, _30, _30a, _31, _31a, _32, _32a, \
    dummy, N, ...) N

#define JEL_COMPONENT_MEMBERS_FUNCTION_1_P(function, type, name) \
  function(type, name)

#define JEL_COMPONENT_MEMBERS_FUNCTION_2_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_1_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_3_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_2_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_4_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_3_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_5_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_4_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_6_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_5_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_7_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_6_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_8_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_7_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_9_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_8_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_10_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_9_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_11_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_10_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_12_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_11_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_13_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_12_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_14_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_13_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_15_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_14_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_16_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_15_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_17_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_16_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_18_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_17_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_19_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_18_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_20_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_19_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_21_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_20_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_22_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_21_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_23_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_22_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_24_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_23_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_25_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_24_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_26_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_25_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_27_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_26_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_28_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_27_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_29_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_28_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_30_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_29_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_31_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_30_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_32_P(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_31_P(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_ITERATE_P(function, ...) \
  JEL_COMPONENT_MEMBERS_FUNCTION_GET_P(__VA_ARGS__, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_32_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_31_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_30_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_29_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_28_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_27_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_26_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_25_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_24_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_23_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_22_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_21_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_20_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_19_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_18_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_17_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_16_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_15_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_14_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_13_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_12_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_11_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_10_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_9_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_8_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_7_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_6_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_5_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_4_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_3_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_2_P, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_1_P)(function, __VA_ARGS__)

// With component macros
#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_1_P(function, component, type, name) \
  function(component, type, name)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_2_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_1_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_3_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_2_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_4_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_3_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_5_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_4_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_6_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_5_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_7_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_6_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_8_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_7_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_9_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_8_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_10_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_9_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_11_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_10_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_12_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_11_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_13_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_12_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_14_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_13_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_15_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_14_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_16_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_15_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_17_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_16_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_18_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_17_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_19_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_18_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_20_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_19_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_21_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_20_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_22_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_21_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_23_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_22_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_24_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_23_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_25_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_24_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_26_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_25_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_27_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_26_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_28_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_27_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_29_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_28_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_30_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_29_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_31_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_30_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_32_P(function, component, type, name, ...) \
  function(component, type, name) \
  JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_31_P(function, component, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_WITH_COMPONENT_ITERATE_P(function, component, ...) \
  JEL_COMPONENT_MEMBERS_FUNCTION_GET_P(__VA_ARGS__, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_32_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_31_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_30_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_29_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_28_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_27_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_26_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_25_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_24_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_23_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_22_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_21_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_20_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_19_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_18_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_17_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_16_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_15_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_14_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_13_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_12_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_11_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_10_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_9_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_8_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_7_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_6_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_5_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_4_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_3_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_2_P, \
  dummy, JEL_COMPONENT_MEMBERS_WITH_COMPONENT_FUNCTION_1_P)(function, component, __VA_ARGS__)

// Count
#define JEL_COMPONENT_MEMBERS_COUNT_HELPER_P(...) \
  JEL_COMPONENT_MEMBERS_FUNCTION_GET_P(__VA_ARGS__, \
      dummy, 32, \
      dummy, 31, \
      dummy, 30, \
      dummy, 29, \
      dummy, 28, \
      dummy, 27, \
      dummy, 26, \
      dummy, 25, \
      dummy, 24, \
      dummy, 23, \
      dummy, 22, \
      dummy, 21, \
      dummy, 20, \
      dummy, 19, \
      dummy, 18, \
      dummy, 17, \
      dummy, 16, \
      dummy, 15, \
      dummy, 14, \
      dummy, 13, \
      dummy, 12, \
      dummy, 11, \
      dummy, 10, \
      dummy, 9, \
      dummy, 8, \
      dummy, 7, \
      dummy, 6, \
      dummy, 5, \
      dummy, 4, \
      dummy, 3, \
      dummy, 2, \
      dummy, 1 \
  )

#define JEL_COMPONENT_MEMBERS_COUNT_P(...) \
  JEL_COMPONENT_MEMBERS_COUNT_HELPER_P(__VA_ARGS__)

#endif

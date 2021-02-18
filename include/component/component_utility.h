#ifndef COMPONENT_UTILITY_H
#define COMPONENT_UTILITY_H

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
// You'll never need more than 16 members really but just in
// case I made it support the next power of 2, 32
//
// Variadic macro trick obtained from
// https://codecraft.co/2014/11/25/variadic-macro-tricks/
//
// A bash/python script to automate this would be nice...
// ========================================

#define JEL_COMPONENT_MEMBERS_MAX 32

#define JEL_COMPONENT_MEMBERS_FUNCTION_GET( \
    _01, _01a, _02, _02a, _03, _03a, _04, _04a, \
    _05, _05a, _06, _06a, _07, _07a, _08, _08a, \
    _09, _09a, _10, _10a, _11, _11a, _12, _12a, \
    _13, _13a, _14, _14a, _15, _15a, _16, _16a, \
    _17, _17a, _18, _18a, _19, _19a, _20, _20a, \
    _21, _21a, _22, _22a, _23, _23a, _24, _24a, \
    _25, _25a, _26, _26a, _27, _27a, _28, _28a, \
    _29, _29a, _30, _30a, _31, _31a, _32, _32a, \
    dummy, N, ...) N

#define JEL_COMPONENT_MEMBERS_FUNCTION_1(function, type, name) \
  function(type, name)

#define JEL_COMPONENT_MEMBERS_FUNCTION_2(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_1(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_3(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_2(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_4(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_3(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_5(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_4(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_6(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_5(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_7(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_6(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_8(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_7(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_9(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_8(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_10(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_9(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_11(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_10(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_12(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_11(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_13(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_12(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_14(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_13(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_15(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_14(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_16(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_15(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_17(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_16(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_18(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_17(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_19(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_18(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_20(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_19(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_21(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_20(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_22(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_21(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_23(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_22(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_24(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_23(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_25(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_24(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_26(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_25(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_27(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_26(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_28(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_27(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_29(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_28(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_30(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_29(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_31(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_30(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_FUNCTION_32(function, type, name, ...) \
  function(type, name) \
  JEL_COMPONENT_MEMBERS_FUNCTION_31(function, __VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_ITERATE(function, ...) \
  JEL_COMPONENT_MEMBERS_FUNCTION_GET(__VA_ARGS__, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_32, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_31, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_30, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_29, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_28, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_27, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_26, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_25, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_24, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_23, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_22, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_21, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_20, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_19, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_18, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_17, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_16, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_15, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_14, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_13, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_12, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_11, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_10, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_9, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_8, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_7, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_6, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_5, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_4, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_3, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_2, \
  dummy, JEL_COMPONENT_MEMBERS_FUNCTION_1)(function, __VA_ARGS__)

#endif

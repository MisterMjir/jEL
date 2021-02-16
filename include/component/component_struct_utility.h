#ifndef COMPONENT_STRUCT_UTILITY_H
#define COMPONENT_STRUCT_UTILITY_H

// These should be private macros
//
// ========================================
// Component Struct stuff
//
// Since I need the types of the members
// to get the components in nice tables,
// I need a macro for creating components
//
// These macros set component's members
//
// The JEL_COMPONENT_MEMBERS_SET_GET gets which
// JEL_COMPONENT_MEMBETS_SET macro is needed
//
// You'll never need more than 16 really but just in
// case I made it support the next power of 2, 32
//
// Variadic macro trick obtained from
// https://codecraft.co/2014/11/25/variadic-macro-tricks/
//
// A bash/python script to automate this would be nice...
// ========================================

#define JEL_COMPONENT_MEMBERS_MAX 32

#define JEL_COMPONENT_MEMBERS_SET_GET( \
    _01, _01a, _02, _02a, _03, _03a, _04, _04a, \
    _05, _05a, _06, _06a, _07, _07a, _08, _08a, \
    _09, _09a, _10, _10a, _11, _11a, _12, _12a, \
    _13, _13a, _14, _14a, _15, _15a, _16, _16a, \
    _17, _17a, _18, _18a, _19, _19a, _20, _20a, \
    _21, _21a, _22, _22a, _23, _23a, _24, _24a, \
    _25, _25a, _26, _26a, _27, _27a, _28, _28a, \
    _29, _29a, _30, _30a, _31, _31a, _32, _32a, \
    dummy, N, ...) N

#define JEL_COMPONENT_MEMBERS_SET_1(type, name) \
  type name;

#define JEL_COMPONENT_MEMBERS_SET_2(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_1(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_3(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_2(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_4(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_3(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_5(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_4(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_6(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_5(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_7(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_6(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_8(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_7(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_9(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_8(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_10(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_9(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_11(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_10(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_12(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_11(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_13(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_12(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_14(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_13(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_15(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_14(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_16(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_15(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_17(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_16(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_18(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_17(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_19(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_18(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_20(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_19(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_21(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_20(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_22(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_21(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_23(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_22(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_24(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_23(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_25(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_24(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_26(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_25(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_27(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_26(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_28(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_27(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_29(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_28(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_30(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_29(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_31(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_30(__VA_ARGS__)

#define JEL_COMPONENT_MEMBERS_SET_32(type, name, ...) \
  type name; \
  JEL_COMPONENT_MEMBERS_SET_31(__VA_ARGS__)

#define JEL_COMPONENT_CREATE_STRUCT(component, ...) \
  struct component { \
    JEL_COMPONENT_MEMBERS_SET_GET(__VA_ARGS__, \
    dummy, JEL_COMPONENT_MEMBERS_SET_32, \
    dummy, JEL_COMPONENT_MEMBERS_SET_31, \
    dummy, JEL_COMPONENT_MEMBERS_SET_30, \
    dummy, JEL_COMPONENT_MEMBERS_SET_29, \
    dummy, JEL_COMPONENT_MEMBERS_SET_28, \
    dummy, JEL_COMPONENT_MEMBERS_SET_27, \
    dummy, JEL_COMPONENT_MEMBERS_SET_26, \
    dummy, JEL_COMPONENT_MEMBERS_SET_25, \
    dummy, JEL_COMPONENT_MEMBERS_SET_24, \
    dummy, JEL_COMPONENT_MEMBERS_SET_23, \
    dummy, JEL_COMPONENT_MEMBERS_SET_22, \
    dummy, JEL_COMPONENT_MEMBERS_SET_21, \
    dummy, JEL_COMPONENT_MEMBERS_SET_20, \
    dummy, JEL_COMPONENT_MEMBERS_SET_19, \
    dummy, JEL_COMPONENT_MEMBERS_SET_18, \
    dummy, JEL_COMPONENT_MEMBERS_SET_17, \
    dummy, JEL_COMPONENT_MEMBERS_SET_16, \
    dummy, JEL_COMPONENT_MEMBERS_SET_15, \
    dummy, JEL_COMPONENT_MEMBERS_SET_14, \
    dummy, JEL_COMPONENT_MEMBERS_SET_13, \
    dummy, JEL_COMPONENT_MEMBERS_SET_12, \
    dummy, JEL_COMPONENT_MEMBERS_SET_11, \
    dummy, JEL_COMPONENT_MEMBERS_SET_10, \
    dummy, JEL_COMPONENT_MEMBERS_SET_9, \
    dummy, JEL_COMPONENT_MEMBERS_SET_8, \
    dummy, JEL_COMPONENT_MEMBERS_SET_7, \
    dummy, JEL_COMPONENT_MEMBERS_SET_6, \
    dummy, JEL_COMPONENT_MEMBERS_SET_5, \
    dummy, JEL_COMPONENT_MEMBERS_SET_4, \
    dummy, JEL_COMPONENT_MEMBERS_SET_3, \
    dummy, JEL_COMPONENT_MEMBERS_SET_2, \
    dummy, JEL_COMPONENT_MEMBERS_SET_1)(__VA_ARGS__)  \
  };

#endif

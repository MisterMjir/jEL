#ifndef JEL_COMPONENT_TABLE_UTILITY_H
#define JEL_COMPONENT_TABLE_UTILITY_H

#include <stddef.h>
#include "entity.h"
#include "component/component_utility.h"
#include "component/component_types.h"

// ========================================
//
// Component Table Utility
//
// ========================================

void * JEL_component_table_create(size_t, struct JEL_ComponentInfo const *, void (*)(void *));
int    JEL_component_table_destroy(void *);

int    JEL_component_table_allocate(void *, JEL_EntityInt);

// Macro stuff
//
// This macro needs more than just type and name
// so it is seperate from the main utility one

// Recursive Macros
#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_1(component, prev, type, name) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated);

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_2(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_1(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_3(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_2(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_4(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_3(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_5(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_4(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_6(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_5(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_7(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_6(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_8(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_7(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_9(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_8(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_10(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_9(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_11(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_10(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_12(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_11(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_13(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_12(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_14(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_13(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_15(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_14(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_16(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_15(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_17(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_16(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_18(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_17(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_19(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_18(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_20(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_19(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_21(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_20(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_22(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_21(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_23(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_22(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_24(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_23(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_25(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_24(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_26(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_25(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_27(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_26(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_28(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_27(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_29(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_28(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_30(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_29(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_31(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_30(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_32(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_31(component, name, __VA_ARGS__)

// Start Macros
#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_1(component, type, name) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer;

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_2(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_1(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_3(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_2(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_4(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_3(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_5(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_4(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_6(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_5(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_7(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_6(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_8(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_7(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_9(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_8(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_10(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_9(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_11(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_10(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_12(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_11(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_13(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_12(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_14(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_13(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_15(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_14(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_16(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_15(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_17(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_16(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_18(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_17(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_19(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_18(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_20(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_19(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_21(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_20(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_22(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_21(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_23(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_22(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_24(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_23(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_25(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_24(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_26(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_25(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_27(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_26(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_28(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_27(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_29(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_28(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_30(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_29(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_31(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_30(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_32(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_POINTERS_UPDATE_31(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_POINTERS_UPDATE(component, ...) \
  JEL_COMPONENT_MEMBERS_FUNCTION_GET(__VA_ARGS__, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_32, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_31, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_30, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_29, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_28, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_27, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_26, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_25, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_24, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_23, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_22, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_21, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_20, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_19, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_18, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_17, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_16, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_15, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_14, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_13, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_12, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_11, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_10, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_9, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_8, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_7, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_6, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_5, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_4, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_3, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_2, \
  dummy, JEL_COMPONENT_TABLE_POINTERS_UPDATE_START_1)(component, __VA_ARGS__)

#endif

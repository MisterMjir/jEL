#ifndef COMPONENT_TABLE_UTILITY
#define COMPONENT_TABLE_UTILITY

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
#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_1(component, prev, type, name) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated);

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_2(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_1(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_3(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_2(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_4(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_3(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_5(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_4(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_6(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_5(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_7(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_6(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_8(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_7(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_9(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_8(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_10(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_9(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_11(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_10(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_12(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_11(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_13(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_12(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_14(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_13(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_15(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_14(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_16(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_15(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_17(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_16(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_18(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_17(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_19(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_18(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_20(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_19(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_21(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_20(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_22(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_21(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_23(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_22(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_24(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_23(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_25(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_24(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_26(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_25(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_27(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_26(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_28(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_27(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_29(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_28(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_30(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_29(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_31(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_30(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_32(component, prev, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) (((struct component##Table *) table)->prev + ((struct component##Table *) table)->head.allocated); \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_31(component, name, __VA_ARGS__)

// Start Macros
#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_1(component, type, name) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer;

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_2(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_1(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_3(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_2(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_4(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_3(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_5(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_4(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_6(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_5(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_7(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_6(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_8(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_7(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_9(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_8(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_10(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_9(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_11(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_10(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_12(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_11(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_13(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_12(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_14(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_13(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_15(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_14(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_16(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_15(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_17(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_16(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_18(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_17(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_19(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_18(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_20(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_19(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_21(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_20(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_22(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_21(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_23(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_22(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_24(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_23(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_25(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_24(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_26(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_25(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_27(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_26(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_28(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_27(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_29(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_28(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_30(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_29(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_31(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_30(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_32(component, type, name, ...) \
  ((struct component##Table *) table)->name = (type *) ((struct component##Table *) table)->head.buffer; \
  JEL_COMPONENT_TABLE_UPDATE_POINTERS_31(component, name, __VA_ARGS__)

#define JEL_COMPONENT_TABLE_UPDATE_POINTERS(component, ...) \
  JEL_COMPONENT_MEMBERS_FUNCTION_GET(__VA_ARGS__, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_32, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_31, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_30, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_29, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_28, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_27, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_26, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_25, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_24, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_23, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_22, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_21, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_20, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_19, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_18, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_17, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_16, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_15, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_14, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_13, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_12, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_11, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_10, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_9, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_8, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_7, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_6, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_5, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_4, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_3, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_2, \
  dummy, JEL_COMPONENT_TABLE_UPDATE_POINTERS_START_1)(component, __VA_ARGS__)

#endif

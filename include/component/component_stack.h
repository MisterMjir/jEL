#ifndef COMPONENT_STACK_H
#define COMPONENT_STACK_H

#include <stdint.h>
#include <stddef.h>
#include "component.h"

// ========================================
//
// Component Stack
//
// Keeps track of component info and stores
// pointers to all the tables
//
// ========================================

struct JEL_ComponentInfo {
  uint8_t members_num;
  size_t  members_sizes;
};

struct JEL_ComponentStack {
  JEL_ComponentInt           infos_allocated;
  JEL_ComponentInt           infos_num;
  struct JEL_ComponentInfo  *infos;
  JEL_ComponentInt           tables_allocated;
  JEL_ComponentInt           tables_num;
  void                     **tables;
};

#endif

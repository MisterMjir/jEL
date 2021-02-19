#ifndef JEL_COMPONENT_STACK_H
#define JEL_COMPONENT_STACK_H

#include "component_types.h"

// ========================================
//
// Component Stack
//
// Keeps track of all component tables
//
// ========================================

struct JEL_ComponentStack {
  JEL_ComponentInt   tables_allocated;
  JEL_ComponentInt   tables_num;
  void             **tables;
};

#endif

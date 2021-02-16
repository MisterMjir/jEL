#ifndef COMPONENT_TABLE_H
#define COMPONENT_TABLE_H

#include "component.h"
#include "entity.h"

// ========================================
// 
// Component Table
//
// The 'database' for all the component data
//
// ========================================

#define JEL_COMPONENT_TABLE_HEAD \
  JEL_ComponentInt  component_index; \
  JEL_EntityInt     allocated; \
  JEL_EntityInt     num; \
  void             *buffer

#endif

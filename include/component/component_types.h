#ifndef JEL_COMPONENT_TYPES_H
#define JEL_COMPONENT_TYPES_H

#include <stdint.h>
#include <stddef.h>
#include "entity.h"

typedef uint32_t JEL_ComponentInt;

struct JEL_ComponentInfo {
  uint8_t const        members_num;
  size_t  const *const members_sizes;
  size_t  const        members_sizes_total;
  void         (*const update_pointers)(void *, JEL_EntityInt);
};

// A component id is a bit array
#define JEL_COMPONENT_ID_INTS 4
typedef JEL_ComponentInt JEL_ComponentId[JEL_COMPONENT_ID_INTS];

#endif

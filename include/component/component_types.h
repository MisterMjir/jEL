#ifndef JEL_COMPONENT_TYPES_H
#define JEL_COMPONENT_TYPES_H

#include <stdint.h>
#include <stddef.h>

typedef uint32_t JEL_ComponentInt;

struct JEL_ComponentInfo {
  uint8_t const        members_num;
  size_t  const *const members_sizes;
  size_t  const        members_sizes_total;
};

#endif

#include "type.h"

// ========================================
// JEL_type_index_add
//
// @desc
//   Adds a type index to a type
// @param type
//   The type to modify
// @param index
//   The index of the bit to set in the type
// @return
//   0 on success
// ========================================
int JEL_type_index_add(JEL_Type type, JEL_TypeIndex index)
{
  // Example: set index 32 when JEL_Type is uint32_t
  // sizeof(JEL_Type) / JEL_TYPE_INTS gives the sizeof the int being used
  // index / 32 = 1, index % 32 = 0
  // 1st element, set the first bit to 0, the 33rd bit of the bit array
  type[index / (sizeof(JEL_Type) / JEL_TYPE_INTS)] |= 1 << (index % (sizeof(JEL_Type) / JEL_TYPE_INTS));

  return 0;
}

#include "type.h"

/*
 * JEL_type_index_add
 *
 * @desc
 *   Adds a type index to a type
 * @param type
 *   The type to modify
 * @param index
 *   The index of the bit to set in the type
 * @return
 *   0 on success
 */
int JEL_type_index_add(JEL_Type type, JEL_TypeIndex index)
{
  /*
   * Index / and % the number of bits in one of the type ints
   * sizeof(JEL_Type) / JEL_TYPE_INTS gives the bytes of 1 int
   * * 8 that gives the bits
   */
  type[index / ((sizeof(JEL_Type) / JEL_TYPE_INTS * 8))] |= 1 << (index % ((sizeof(JEL_Type) / JEL_TYPE_INTS) * 8));

  return 0;
}

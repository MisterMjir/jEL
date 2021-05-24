#include "type.h"
#include "core.h"

/*
 * JEL_type_init
 *
 * @desc
 *   Inits a type to all 0s except JEL_EntityC
 * @param type
 *   Type to init
 * @return
 *   0 on success
 */
int JEL_type_init(JEL_Type type)
{
  for (int i = 0; i < JEL_TYPE_INTS; ++i) {
    type[i] = 0;
  }

  JEL_type_index_add(type, JEL_EntityC_id);

  return 0;
}

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

/*
 * JEL_type_set
 *
 * @desc
 *   Sets a JEL_Type to another JEL_Type
 * @param dest
 *   The type to set (lvalue of assignment)
 * @param src
 *   The type to set to (rvalue of assignment)
 */
int JEL_type_set(JEL_Type dest, JEL_Type src)
{
  for (int i = 0; i < JEL_TYPE_INTS; ++i) {
    dest[i] = src[i];
  }

  return 0;
}

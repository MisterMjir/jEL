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
void JEL_type_init(JEL_Type type)
{
  type[0] = 2;
  for (int i = 1; i < JEL_TYPE_INTS; ++i) {
    type[i] = 0;
  }

}

/*
 * JEL_type_add
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
void JEL_type_add(JEL_Type type, JEL_TypeIndex index)
{
  /*
   * Index / and % the number of bits in one of the type ints
   * sizeof(JEL_Type) / JEL_TYPE_INTS gives the bytes of 1 int
   * * 8 that gives the bits
   */
  type[index / ((sizeof(JEL_Type) / JEL_TYPE_INTS * 8))] |= 1 << (index % ((sizeof(JEL_Type) / JEL_TYPE_INTS) * 8));
}

/*
 * JEL_type_remove
 *
 * @desc
 *   Removes a type index to a type
 * @param type
 *   The type to modify
 * @param index
 *   The index of the bit to set in the type
 * @return
 *   0 on success
 */
void JEL_type_remove(JEL_Type type, JEL_TypeIndex index)
{
  /* Same as add but sets 0 instead of 1 */
  type[index / ((sizeof(JEL_Type) / JEL_TYPE_INTS * 8))] |= 0 << (index % ((sizeof(JEL_Type) / JEL_TYPE_INTS) * 8));
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
void JEL_type_set(JEL_Type dest, JEL_Type src)
{
  for (int i = 0; i < JEL_TYPE_INTS; ++i) {
    dest[i] = src[i];
  }
}

/*
 * JEL_type_cmp
 *
 * @return
 *   0 if different
 *   1 if match
 */
int JEL_type_cmp(JEL_Type a, JEL_Type b)
{
  for (int i = 0; i < JEL_TYPE_INTS; ++i) {
    if (a[i] != b[i]) return 0;
  }

  return 1;
}

int JEL_type_index_check(JEL_Type t, JEL_TypeIndex i)
{
  return t[i / (sizeof(JEL_Type) / JEL_TYPE_INTS * 8)] & (1 << i % (sizeof(JEL_Type) / JEL_TYPE_INTS * 8));
}

/*
 * JEL_type_num
 *
 * @desc
 *   Find the number of types
 */
int JEL_type_num(JEL_Type t)
{
  int num = 0;

  for (unsigned int type_index = 1; type_index < sizeof(JEL_Type) * 8; ++type_index) {
    num += JEL_TYPE_GET(t, type_index) ? 1 : 0;
  }

  return num;
}

#ifndef JEL_TYPE_H
#define JEL_TYPE_H

/*
 * Types
 *
 * Types apply to entities and tables. Types
 * are a bit array representing what components
 * are being used
 */

#include <stdint.h>
#include <stddef.h>

#define JEL_TYPE_INTS 4
typedef uint32_t JEL_Type[JEL_TYPE_INTS];

typedef size_t JEL_TypeIndex;

/* Add an type index to a type */
int JEL_type_index_add(JEL_Type, JEL_TypeIndex);
int JEL_type_set(JEL_Type, JEL_Type);

#define JEL_ID_SET_HELPER_P(component) id[component##_id / 32] |= 1 << (component##_id % 32);

#define JEL_ID_SET(id, ...) \
  JEL_COMPONENTS_ITERATE_P(JEL_ID_SET_HELPER_P, __VA_ARGS__)

#define JEL_ID_SET_ARG_P(type, ...) \
{ \
  JEL_Type id; \
  JEL_type_set(id, type); \
  JEL_ID_SET(id, __VA_ARGS__); \
  JEL_type_set(type, id); \
}

#endif

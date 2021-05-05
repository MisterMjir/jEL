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
#endif

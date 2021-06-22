#include "utility.h"
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/* JEL_data_create helper */
#define IF_TYPE(type, promotion) \
  if (sizes[i] == sizeof(type)) { \
    type data = (type) va_arg(args, promotion); \
    memcpy(dp, &data, sizes[i]); \
  }

/*
 * JEL_data_create
 *
 * @desc
 *   Creates a buffer of data
 * @param argc
 *   The number of arguments
 * @param ...
 *   Sizes and then values
 * @return
 *   A pointer to a buffer with the data
 */
void * JEL_data_create(int argc, ...)
{
  void *buffer;
  size_t size = 0;
  va_list args;
  size_t *sizes; /* Array of sizes */

  sizes = malloc(argc * sizeof(size_t));

  va_start(args, argc);

  /* Prepare the buffer */
  for (int i = 0; i < argc; ++i) {
    sizes[i] = va_arg(args, size_t);
    size += sizes[i];
  }

  buffer = malloc(size);

  /* Copy the data */
  int8_t *dp = buffer;
  for (int i = 0; i < argc; ++i) {
    /* Some sizes are redundant but just in case */
    IF_TYPE(short int, int)
    else IF_TYPE(int, int)
    else IF_TYPE(long int, long int)
    else IF_TYPE(long long int, long long int)
    else IF_TYPE(char, int)
    else IF_TYPE(float, double)
    else IF_TYPE(double, double)
    else IF_TYPE(long double, long double)
    else {
      /* Size not supported */
      free(buffer);
      free(sizes);
      va_end(args);
      return NULL;
    }

    dp += sizes[i];
  }

  va_end(args);

  free(sizes);

  return buffer;
}

/*
 * JEL_data_destroy
 *
 * @desc
 *   Frees a buffer created with JEL_data
 *   The reasoning for this function is so it can
 *   match with create, since free's pair up with
 *   malloc's
 * @param data
 *   Pointer to JEL_data
 * @return
 *   0
 */
int JEL_data_destroy(void *buffer)
{
  free(buffer);

  return 0;
}

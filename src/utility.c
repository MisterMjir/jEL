#include "utility.h"
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

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
  size_t sizes[argc];

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
    if (sizes[i] == sizeof(short int)) {
      short int data = (short int) va_arg(args, int);
      memcpy(dp, &data, sizes[i]);
    }
    else if (sizes[i] == sizeof(int)) {
      int data = va_arg(args, int);
      memcpy(dp, &data, sizes[i]);
    }
    else if (sizes[i] == sizeof(long int)) {
      long int data = va_arg(args, long int);
      memcpy(dp, &data, sizes[i]);
    }
    else if (sizes[i] == sizeof(long long int)) {
      long long int data = va_arg(args, long long int);
      memcpy(dp, &data, sizes[i]);
    }
    else if (sizes[i] == sizeof(char)) {
      char data = (char) va_arg(args, int);
      memcpy(dp, &data, sizes[i]);
    }
    else if (sizes[i] == sizeof(float)) {
      float data = (float) va_arg(args, double);
      memcpy(dp, &data, sizes[i]);
    }
    else if (sizes[i] == sizeof(double)) {
      double data = va_arg(args, double);
      memcpy(dp, &data, sizes[i]);
    }
    else if (sizes[i] == sizeof(long double)) {
      long double data = va_arg(args, long double);
      memcpy(dp, &data, sizes[i]);
    }
    else {
      /* Size not supported */
      free(buffer);
      va_end(args);
      return NULL;
    }

    dp += sizes[i];
  }

  va_end(args);

  return buffer;
}

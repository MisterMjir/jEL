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
 *   Currently only supports byte sizes
 *   of 1, 2, 4
 *   TODO: Improve this function
 * @param format
 *   Comma seperated byte sizes
 *   ex. "1,4,2"
 * @param ...
 *   Values
 * @return
 *   A pointer to a buffer with the data
 */
void * JEL_data_create(const char *format, ...)
{
  void *buffer;
  int i = 0;
  int size = 0;
  va_list args;

  va_start(args, format);

  /* Prepare the buffer */
  while (format[i] != '\0') {
    if (format[i] == ',') {
      ++i;
      continue;
    }
    else if (format[i] == '1') {
      size += 8; 
    }
    else if (format[i] == '2') {
      size += 16;
    }
    else if (format[i] == '4') {
      size += 32;
    }

    ++i;
  }

  buffer = malloc(size);

  /* Copy the data */
  int8_t *dp = buffer;
  while (format[0] != '\0') {
    if (format[0] == ',') {
      ++format;
      continue;
    }
    else if (format[0] == '1') {
      int8_t d = (int8_t) va_arg(args, int);
      memcpy(dp, &d, sizeof(int8_t));
      dp += sizeof(int8_t);
    }
    else if (format[0] == '2') {
      int16_t d = (int16_t) va_arg(args, int);
      memcpy(dp, &d, sizeof(int16_t));
      dp += sizeof(int16_t);
    }
    else if (format[0] == '4') {
      int32_t d = (int32_t) va_arg(args, int32_t);
      memcpy(dp, &d, sizeof(int32_t));
      dp += sizeof(int32_t);
    }

    ++format;
  }

  va_end(args);

  return buffer;
}

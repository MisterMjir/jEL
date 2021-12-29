#include "logger.h"
#include <stdio.h>
#include <stdarg.h>

#define JEL_LOG

/*
 * JEL_log
 *
 * @desc
 *   Prints out information tp
 *   stderr
 * @param fmt
 *   printf like format
 * @param ...
 *   arguments based off format
 * @return
 *   The result of the print (number of
 *   characters written or negative if
 *   error)
 */
int JEL_log(const char *fmt, ...)
{
  int result = 0;

  #ifdef JEL_LOG
    va_list va;
    va_start(va, fmt);

    result = fprintf (stderr, "jEL: ");
    result = vfprintf(stderr, fmt, va);
    result = fprintf (stderr, "\n");

    va_end(va);
  #endif

  return result;
}

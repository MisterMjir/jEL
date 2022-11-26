#include "utility.h"
#include "component.h"
#include "core.h"
#include "logger/logger.h"
#include <stdio.h>

#define JEL_MAX_COMPONENT_NAME 64

/*
 * JEL_type_set_str
 *
 * @desc
 *   Sets a type based off a string, it
 *   uses JEL_type_add really
 * @param t
 *   The type
 * @param str
 *   A string of comma seperated component names
 *   (it's ok to have spaces, they will be ignored)
 *   The last component must not have a comma after it
 * @return
 *   Success code
 */
int JEL_type_set_str(JEL_Type t, const char *str)
{
  char  buffer[JEL_MAX_COMPONENT_NAME]; /* Super generous with buffer size, keep names small */
  char *bp = buffer;
  while (*str) {
    if (*str == ' ') { ++str; continue; } 
    if (*str == ',') {
      *bp = '\0';
      JEL_TypeIndex ti = JEL_component_map_get(&JEL_CTX->component_map, buffer);
      if (!ti) {
        JEL_log("Could not set type: Component %s is not registered", buffer);
        return -1;
      }

      JEL_type_add(t, ti);
      bp = buffer;
      ++str;
      continue;
    }
    *bp++ = *str;
    ++str;
  }

  *bp = '\0';
  JEL_TypeIndex ti = JEL_component_map_get(&JEL_CTX->component_map, buffer);
  if (!ti) {
    JEL_log("Could not set type: Component %s is not registered", buffer);
    return -1;
  }

  JEL_type_add(t, ti);

  return 0;
}

/*
 * JEL_data_dump
 * 
 * @desc
 *   Dumps all JEL data into a file
 */
int JEL_data_dump(void)
{
  FILE *file;

  file = fopen("data.jd", "w");

  /* Amount of components and component names */
  /*
  fwrite(&JEL_CTX->component_table.count, sizeof(JEL_CTX->component_table.count), 1, file); // unsigned int
  for (unsigned int i = 0; i < JEL_CTX->component_table.count; ++i) {
    fputs(JEL_component_n);
  }
  */


  fclose(file);

  return 0;
}
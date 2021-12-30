#include "utility.h"
#include "component.h"
#include "core.h"
#include "logger/logger.h"

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
  char  buffer[64]; /* Super generous with buffer size, keep names small */
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

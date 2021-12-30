#include "component.h"
#include <string.h>
#include "logger/logger.h"

/*
 * hash
 *
 * @desc
 *   Takes a string and hashes it
 *   This is the djb2 algorithm
 * @param str
 *   The string to hash
 * @return
 *   Unsigned long number hash
 */
static unsigned int hash(const char *str)
{
  unsigned long hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;

  return hash;
}

/*
 * JEL_component_map_create
 *
 * @desc
 *   Initializes/creates a component map
 * @param map
 *   Map to create
 */
void JEL_component_map_create(struct JEL_ComponentMap *map)
{
  for (int i = 0; i < JEL_MAX_COMPONENTS; ++i) {
    map->components[i].key = NULL;
    map->components[i].next = NULL;
  }
}

/*
 * JEL_component_map_destroy
 *
 * @desc
 *   Cleans all the linked lists and
 *   name-keys
 * @param map
 *   Map to free up
 */
void JEL_component_map_destroy(struct JEL_ComponentMap *map)
{
  for (int i = 0; i < JEL_MAX_COMPONENTS; ++i) {
    free(map->components[i].key);  
  
    struct JEL_ComponentMapItem *next = map->components[i].next;
    
    while (next != NULL) {
      struct JEL_ComponentMapItem *current = next;
      next = next->next;
      free(current->key);
      free(current);
    }
  }
}

/*
 * JEL_component_map_add
 *
 * @desc
 *   Adds a key-value pair
 * @param map
 *   Map to add pair to
 * @param key
 *   Name of the component
 * @param value
 *   Index of the component in
 *   the table
 * @return
 *    0 on success
 *   -1 if an allocation failed
 */
int JEL_component_map_add(struct JEL_ComponentMap *map, const char *key, JEL_TypeIndex value)
{
  unsigned int index = hash(key) % JEL_MAX_COMPONENTS; /* Index of the pair in the hash table */
  struct JEL_ComponentMapItem *item = &map->components[index];

  /* Not new item, go through the linked list */
  if (map->components[index].key) {
    while (item->next) {
      item = item->next;
    }

    item->next = malloc(sizeof(*item->next));
    item = item->next;
  }

  map->components[index].value = value;
  if (!(map->components[index].key = malloc(strlen(key) + 1))) {
    JEL_log("Could not allocate component map: Out of memory");
    return -1;
  }
  strcpy(map->components[index].key, key);

  return 0;
}

/*
 * JEL_component_map_get
 *
 * @desc
 *   Gets a value from a key
 * @param map
 *   Map to get from
 * @param key
 *   Name of the component
 * @return
 *   Either the index or 0 if not found
 */
JEL_TypeIndex JEL_component_map_get(struct JEL_ComponentMap *map, const char *key)
{
  unsigned int index = hash(key) % JEL_MAX_COMPONENTS;
  struct JEL_ComponentMapItem *item = &map->components[index];

  while (strcmp(key, item->key)) {
    if (item->next)
      item = item->next;
    else
      return 0;
  }

  return item->value;
}

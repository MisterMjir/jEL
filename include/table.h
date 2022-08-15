#ifndef JEL_TABLE_H
#define JEL_TABLE_H

/*
 * Tables
 *
 * Big buffer of data
 *
 * The first section should always be
 * a JEL_EntityC component/buffer
 *
 * The first item should be reserved
 * for errors
 * 
 * Less error checking in exchange for
 * speed, only JEL should call these
 * table functions
 */

#include "type.h"
#include "entity.h"

struct JEL_Table {
  unsigned int   allocated;
  unsigned int   count;
  void          *buffer;
  JEL_Type       type;
  size_t         size; /* Total size of each component members */
  /* Type stuff for easier use */
  unsigned int   types_num;
  JEL_TypeIndex *types;
  void         **type_buffers;
};

/*
 * Table functions
 * 
 * create     | Create the table
 * destroy    | Destroy the table
 * allocate   | Allocate more rows for the table
 * add        | Add an entity to a table, return its index
 * remove     | Remove an entity from a table
 * index      | Find the index of an entity
 * set        | Set a component based off a struct
 * set_prop   | Set a component property/member
 * get        | Put a component into a a struct
 * get_it     | Gets a table iterator for a component
 * switch     | Move an entity from one table to another
 */
int          JEL_table_create  (struct JEL_Table *table, JEL_Type type);
void         JEL_table_destroy (struct JEL_Table *table);
int          JEL_table_allocate(struct JEL_Table *table, unsigned int count);
unsigned int JEL_table_add     (struct JEL_Table *table, JEL_Entity entity);
int          JEL_table_remove  (struct JEL_Table *table, unsigned int idx);
unsigned int JEL_table_index   (struct JEL_Table *table, JEL_Entity entity);
int          JEL_table_set     (struct JEL_Table *table, unsigned int idx, JEL_TypeIndex component_index, void *data);
int          JEL_table_set_prop(struct JEL_Table *table, JEL_Entity entity, JEL_TypeIndex ti, size_t size, size_t offset, void *data);
int          JEL_table_get     (struct JEL_Table *table, unsigned int idx, JEL_TypeIndex component_index, void *data);
int          JEL_table_get_it  (struct JEL_Table *table, void *it, JEL_TypeIndex ti);
int          JEL_table_switch  (struct JEL_Table *a, struct JEL_Table *b, JEL_Entity entity);

#define JEL_IT(it, table, comp) \
  { \
    JEL_table_get_it(table, &it, JEL_component_map_get(&JEL_CTX->component_map, #comp)); \
  }

struct JEL_TableStack {
  unsigned int        allocated;
  unsigned int        count;
  struct JEL_Table  **tables;
};

/*
 *
 */
int                JEL_table_stack_create  (struct JEL_TableStack *stack);
void               JEL_table_stack_destroy (struct JEL_TableStack *stack);
struct JEL_Table * JEL_table_stack_push    (struct JEL_TableStack *stack, JEL_Type type);
int                JEL_table_stack_allocate(struct JEL_TableStack *stack, unsigned int count);
struct JEL_Table * JEL_table_stack_get     (struct JEL_TableStack *stack, JEL_Type type);

#endif

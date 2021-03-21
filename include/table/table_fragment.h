#ifndef JEL_TABLE_FRAGMENT_H
#define JEL_TABLE_FRAGMENT_H

#include "component/component_utility.h"
#include "table_fragment_update_pointers.h" // TODO: Make this a 'table' file instead of a 'component' file

// ========================================
//
// Component Table Fragments
//
// Fragments of a table that make up a
// JEL_Table. Fragments (when casted to their
// specific type) have pointers to each of
// their members. All fragments have a fragment
// head, which has generic fragment information.
//
// This info and stuff is needed so any table
// can be allocated properly without knowing
// it's type.
//
// Generic types and casting works by having
// the first member of every fragment struct
// being a JEL_FragmentHead_P struct, pretty
// cool stuff.
//
// ========================================

// Header info for all fragments (private)
struct JEL_TableFragmentHead_P {
  struct JEL_ComponentInfo const *const info; // TODO: It should be now FragmentInfo (component doesn't need an update_pointers)
  void                           *buffer_start; // Where fragment's portion of the table buffer starts
};

// Generic fragment struct
struct JEL_TableFragment {
  struct JEL_TableFragmentHead_P head;
};

// ========================================
//
// Component Registration
//
// - Create the fragment struct
// - Create the fragment update pointers function
// - Create the fragment info struct
//
// ========================================

#define JEL_TABLE_FRAGMENT_MEMBERS_SET_P(type, name) type *name;

#define JEL_TABLE_FRAGMENT_CREATE_P(component, ...) \
  struct component##Fragment { \
    struct JEL_TableFragmentHead_P head; \
    JEL_COMPONENT_MEMBERS_ITERATE_P(JEL_TABLE_FRAGMENT_MEMBERS_SET_P, __VA_ARGS__) \
  }; \
  \
  void component##_update_pointers_p(void *fragment, JEL_EntityInt allocated) \
  { \
    JEL_TABLE_FRAGMENT_POINTERS_UPDATE_P(component, __VA_ARGS__) \
  } \

#endif

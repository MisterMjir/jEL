#ifndef JEL_CORE_H
#define JEL_CORE_H

#include "context.h"

// ========================================
//
// Core
//
// Only global variable in library for the
// current context
//
// Errors are specific to a context
//
// Utility functions for contexes
//
// ========================================

extern struct JEL_Context *JEL_context_current;

struct JEL_Context * JEL_context_create     (void);
int                  JEL_context_destroy    (struct JEL_Context *);
int                  JEL_context_set_current(struct JEL_Context *);

#endif

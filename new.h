
/*
  New declaration
 */

#ifndef NEW_H
# define NEW_H

# include <stdarg.h>

#include "Object.h"

Object* new(Class * class, ...);
Object* va_new(Class* class, va_list* ap);
void delete(Object * ptr);

#endif

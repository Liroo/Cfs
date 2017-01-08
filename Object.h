
/*
  Object declaration
 */

#ifndef CLASS_H
# define CLASS_H

# include <sys/types.h>

typedef void Object;
typedef void (*ctor_t)(Object * self, va_list * args);
typedef void (*dtor_t)(Object * self);
typedef char const* (*to_string_t)(Object* self);

typedef struct {
    const size_t        __size__;
    const char*         __name__;
    ctor_t              __init__;
    dtor_t              __del__;
} Class;

# define str(o) (((Class*) o)->__str__ != NULL ? ((Class*) o)->__str__(o) : "")

#endif

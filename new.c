/*
 * New.c implementation of new(ObjectType)
 */

#include <string.h>
#include <stdarg.h>
#include "Object.h"
#include "raise.h"
#include "new.h"

Object		*new(Class *class, ...)
{
  Object	*res;

  /*
   * call va_new by extracting ap list
   */
  va_list	ap;

  va_start(ap, class);
  res = va_new(class, &ap);
  va_end(ap);

  return res;
}

Object	*va_new(Class *class, va_list *ap)
{
  Class	*newClass;

  if (!class)
    return NULL;

  /*
   * create new Class
   */
  if (!(newClass = malloc(class->__size__)))
    raise("Out of memory");
  memcpy(newClass, class, class->__size__);

  /*
   * call constructor with ap list
   */
  if (newClass->__init__)
    newClass->__init__(newClass, ap);

  return newClass;
}

void	delete(Object *ptr)
{
  if (!ptr)
    return;
  /*
   * call destructor
   */
  if (((Class *)ptr)->__del__)
    ((Class *)ptr)->__del__(ptr);
  free(ptr); // bye bye deer pi-ti-air
}

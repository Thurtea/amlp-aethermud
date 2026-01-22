#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include "gc.h"
#include "vm.h"

typedef struct array_t {
    GC *gc;                 /* Owning garbage collector (nullable) */
    VMValue *elements;      /* Element storage */
    size_t length;          /* Number of elements */
    size_t capacity;        /* Allocated capacity */
} array_t;

array_t* array_new(GC *gc, size_t capacity);
int array_push(array_t *arr, VMValue value);
int array_pop(array_t *arr, VMValue *out);
VMValue array_get(const array_t *arr, size_t index);
int array_set(array_t *arr, size_t index, VMValue value);
int array_insert(array_t *arr, size_t index, VMValue value);
int array_delete(array_t *arr, size_t index);
size_t array_length(const array_t *arr);
array_t* array_clone(const array_t *arr, GC *gc);
void array_free(array_t *arr);

#endif /* ARRAY_H */

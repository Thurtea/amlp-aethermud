#include "array.h"
#include <stdlib.h>
#include <string.h>

static void* arr_alloc(GC *gc, size_t size, GCObjectType type) {
    if (gc) {
        return gc_alloc(gc, size, type);
    }
    return malloc(size);
}

static void arr_release(GC *gc, void *ptr) {
    if (!ptr) return;
    if (gc) {
        gc_release(gc, ptr);
    } else {
        free(ptr);
    }
}

array_t* array_new(GC *gc, size_t capacity) {
    array_t *arr = (array_t *)arr_alloc(gc, sizeof(array_t), GC_TYPE_ARRAY);
    if (!arr) return NULL;

    arr->gc = gc;
    arr->length = 0;
    arr->capacity = capacity > 0 ? capacity : 8;
    arr->elements = (VMValue *)arr_alloc(gc, sizeof(VMValue) * arr->capacity, GC_TYPE_GENERIC);
    if (!arr->elements) {
        arr_release(gc, arr);
        return NULL;
    }

    for (size_t i = 0; i < arr->capacity; i++) {
        arr->elements[i].type = VALUE_UNINITIALIZED;
    }

    return arr;
}

static int array_grow(array_t *arr) {
    size_t new_cap = arr->capacity > 0 ? arr->capacity * 2 : 8;
    VMValue *new_elems = (VMValue *)arr_alloc(arr->gc, sizeof(VMValue) * new_cap, GC_TYPE_GENERIC);
    if (!new_elems) return -1;

    for (size_t i = 0; i < new_cap; i++) {
        new_elems[i].type = VALUE_UNINITIALIZED;
    }

    if (arr->elements) {
        memcpy(new_elems, arr->elements, sizeof(VMValue) * arr->length);
        arr_release(arr->gc, arr->elements);
    }

    arr->elements = new_elems;
    arr->capacity = new_cap;
    return 0;
}

int array_push(array_t *arr, VMValue value) {
    if (!arr) return -1;
    if (arr->length >= arr->capacity) {
        if (array_grow(arr) != 0) return -1;
    }
    arr->elements[arr->length++] = value;
    return 0;
}

int array_pop(array_t *arr, VMValue *out) {
    if (!arr || arr->length == 0) return -1;
    if (out) {
        *out = arr->elements[arr->length - 1];
    }
    arr->length--;
    return 0;
}

VMValue array_get(const array_t *arr, size_t index) {
    if (!arr || index >= arr->length) {
        return vm_value_create_null();
    }
    return arr->elements[index];
}

int array_set(array_t *arr, size_t index, VMValue value) {
    if (!arr || index >= arr->length) return -1;
    vm_value_free(&arr->elements[index]);
    arr->elements[index] = value;
    return 0;
}

int array_insert(array_t *arr, size_t index, VMValue value) {
    if (!arr || index > arr->length) return -1;
    if (arr->length >= arr->capacity) {
        if (array_grow(arr) != 0) return -1;
    }
    for (size_t i = arr->length; i > index; i--) {
        arr->elements[i] = arr->elements[i - 1];
    }
    arr->elements[index] = value;
    arr->length++;
    return 0;
}

int array_delete(array_t *arr, size_t index) {
    if (!arr || index >= arr->length) return -1;
    vm_value_free(&arr->elements[index]);
    for (size_t i = index; i + 1 < arr->length; i++) {
        arr->elements[i] = arr->elements[i + 1];
    }
    arr->length--;
    return 0;
}

size_t array_length(const array_t *arr) {
    return arr ? arr->length : 0;
}

array_t* array_clone(const array_t *arr, GC *gc) {
    if (!arr) return NULL;
    array_t *copy = array_new(gc ? gc : arr->gc, arr->length);
    if (!copy) return NULL;
    copy->length = arr->length;
    for (size_t i = 0; i < arr->length; i++) {
        copy->elements[i] = vm_value_clone(arr->elements[i]);
    }
    return copy;
}

void array_free(array_t *arr) {
    if (!arr) return;
    if (arr->elements) {
        for (size_t i = 0; i < arr->length; i++) {
            vm_value_free(&arr->elements[i]);
        }
        arr_release(arr->gc, arr->elements);
        arr->elements = NULL;
    }
    arr_release(arr->gc, arr);
}

#ifndef MAPPING_H
#define MAPPING_H

#include <stddef.h>
#include "gc.h"
#include "vm.h"
#include "array.h"

typedef struct mapping_entry_t {
    char *key;
    VMValue value;
    struct mapping_entry_t *next;
} mapping_entry_t;

typedef struct mapping_t {
    GC *gc;
    mapping_entry_t **buckets;
    size_t bucket_count;
    size_t size;
} mapping_t;

mapping_t* mapping_new(GC *gc, size_t buckets);
mapping_entry_t* mapping_set(mapping_t *map, const char *key, VMValue value);
VMValue mapping_get(const mapping_t *map, const char *key);
int mapping_delete(mapping_t *map, const char *key);
array_t* mapping_keys(const mapping_t *map);
array_t* mapping_values(const mapping_t *map);
size_t mapping_size(const mapping_t *map);
mapping_t* mapping_clone(const mapping_t *map, GC *gc);
void mapping_free(mapping_t *map);

#endif /* MAPPING_H */

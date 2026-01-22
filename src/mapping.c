#include "mapping.h"
#include <stdlib.h>
#include <string.h>

static unsigned int map_hash(const char *key, size_t capacity) {
    unsigned int hash = 0;
    for (const char *p = key; *p; ++p) {
        hash = ((hash << 5) + hash) ^ (unsigned char)(*p);
    }
    return hash % (capacity ? capacity : 1);
}

static void* map_alloc(GC *gc, size_t size, GCObjectType type) {
    if (gc) return gc_alloc(gc, size, type);
    return malloc(size);
}

static void map_release(GC *gc, void *ptr) {
    if (!ptr) return;
    if (gc) {
        gc_release(gc, ptr);
    } else {
        free(ptr);
    }
}

mapping_t* mapping_new(GC *gc, size_t buckets) {
    size_t bucket_count = buckets > 0 ? buckets : 16;
    mapping_t *map = (mapping_t *)map_alloc(gc, sizeof(mapping_t), GC_TYPE_MAPPING);
    if (!map) return NULL;

    map->gc = gc;
    map->bucket_count = bucket_count;
    map->size = 0;
    map->buckets = (mapping_entry_t **)map_alloc(gc, sizeof(mapping_entry_t *) * bucket_count, GC_TYPE_GENERIC);
    if (!map->buckets) {
        map_release(gc, map);
        return NULL;
    }
    for (size_t i = 0; i < bucket_count; i++) {
        map->buckets[i] = NULL;
    }

    return map;
}

mapping_entry_t* mapping_set(mapping_t *map, const char *key, VMValue value) {
    if (!map || !key) return NULL;

    unsigned int idx = map_hash(key, map->bucket_count);
    mapping_entry_t *entry = map->buckets[idx];

    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            vm_value_free(&entry->value);
            entry->value = value;
            return entry;
        }
        entry = entry->next;
    }

    entry = (mapping_entry_t *)map_alloc(map->gc, sizeof(mapping_entry_t), GC_TYPE_GENERIC);
    if (!entry) return NULL;
    entry->key = (char *)malloc(strlen(key) + 1);
    if (!entry->key) {
        map_release(map->gc, entry);
        return NULL;
    }
    strcpy(entry->key, key);
    entry->value = value;
    entry->next = map->buckets[idx];
    map->buckets[idx] = entry;
    map->size++;
    return entry;
}

VMValue mapping_get(const mapping_t *map, const char *key) {
    if (!map || !key) return vm_value_create_null();
    unsigned int idx = map_hash(key, map->bucket_count);
    mapping_entry_t *entry = map->buckets[idx];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return vm_value_create_null();
}

int mapping_delete(mapping_t *map, const char *key) {
    if (!map || !key) return -1;
    unsigned int idx = map_hash(key, map->bucket_count);
    mapping_entry_t **cursor = &map->buckets[idx];
    while (*cursor) {
        mapping_entry_t *entry = *cursor;
        if (strcmp(entry->key, key) == 0) {
            *cursor = entry->next;
            vm_value_free(&entry->value);
            if (entry->key) free(entry->key);
            map_release(map->gc, entry);
            map->size--;
            return 0;
        }
        cursor = &(*cursor)->next;
    }
    return -1;
}

array_t* mapping_keys(const mapping_t *map) {
    if (!map) return NULL;
    array_t *arr = array_new(map->gc, map->size);
    if (!arr) return NULL;
    for (size_t i = 0; i < map->bucket_count; i++) {
        mapping_entry_t *entry = map->buckets[i];
        while (entry) {
            array_push(arr, vm_value_create_string(entry->key));
            entry = entry->next;
        }
    }
    return arr;
}

array_t* mapping_values(const mapping_t *map) {
    if (!map) return NULL;
    array_t *arr = array_new(map->gc, map->size);
    if (!arr) return NULL;
    for (size_t i = 0; i < map->bucket_count; i++) {
        mapping_entry_t *entry = map->buckets[i];
        while (entry) {
            array_push(arr, vm_value_clone(entry->value));
            entry = entry->next;
        }
    }
    return arr;
}

size_t mapping_size(const mapping_t *map) {
    return map ? map->size : 0;
}

mapping_t* mapping_clone(const mapping_t *map, GC *gc) {
    if (!map) return NULL;
    mapping_t *copy = mapping_new(gc ? gc : map->gc, map->bucket_count);
    if (!copy) return NULL;
    for (size_t i = 0; i < map->bucket_count; i++) {
        mapping_entry_t *entry = map->buckets[i];
        while (entry) {
            mapping_set(copy, entry->key, vm_value_clone(entry->value));
            entry = entry->next;
        }
    }
    return copy;
}

void mapping_free(mapping_t *map) {
    if (!map) return;
    if (map->buckets) {
        for (size_t i = 0; i < map->bucket_count; i++) {
            mapping_entry_t *entry = map->buckets[i];
            while (entry) {
                mapping_entry_t *next = entry->next;
                vm_value_free(&entry->value);
                if (entry->key) free(entry->key);
                map_release(map->gc, entry);
                entry = next;
            }
        }
        map_release(map->gc, map->buckets);
        map->buckets = NULL;
    }
    map_release(map->gc, map);
}

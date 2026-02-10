/**
 * gc.c - Garbage Collection System Implementation
 * 
 * Reference-counted garbage collector with cycle detection.
 * 
 * Phase 5 Implementation - January 22, 2026
 */

#include "gc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* ========== Helper Functions ========== */

/**
 * Find GCObject wrapper for a pointer
 */
GCObject* gc_find_object(GC *gc, void *ptr) {
    if (!gc || !ptr) return NULL;
    
    for (int i = 0; i < gc->object_count; i++) {
        if (gc->objects[i] && gc->objects[i]->ptr == ptr) {
            return gc->objects[i];
        }
    }
    
    return NULL;
}

/**
 * Remove object from tracking array
 */
static int gc_remove_object(GC *gc, GCObject *obj) {
    if (!gc || !obj) return -1;
    
    for (int i = 0; i < gc->object_count; i++) {
        if (gc->objects[i] == obj) {
            /* Shift remaining objects down */
            for (int j = i; j < gc->object_count - 1; j++) {
                gc->objects[j] = gc->objects[j + 1];
            }
            gc->object_count--;
            return 0;
        }
    }
    
    return -1;
}

/* ========== Core GC Functions ========== */

GC* gc_init(void) {
    GC *gc = (GC *)malloc(sizeof(GC));
    if (!gc) return NULL;
    
    gc->object_capacity = GC_INITIAL_CAPACITY;
    gc->object_count = 0;
    gc->objects = (GCObject **)malloc(sizeof(GCObject *) * gc->object_capacity);
    
    if (!gc->objects) {
        free(gc);
        return NULL;
    }
    
    /* Initialize statistics */
    gc->total_allocated = 0;
    gc->total_freed = 0;
    gc->allocation_count = 0;
    gc->collection_count = 0;
    
    /* Initialize configuration */
    gc->collect_threshold = GC_COLLECT_THRESHOLD;
    gc->auto_collect_enabled = 1;
    
    printf("[GC] Initialized (capacity: %d)\n", gc->object_capacity);
    
    return gc;
}

void* gc_alloc(GC *gc, size_t size, GCObjectType type) {
    if (!gc || size == 0) return NULL;
    
    /* Allocate memory */
    void *ptr = malloc(size);
    if (!ptr) return NULL;
    
    /* Track with GC */
    GCObject *obj = gc_track(gc, ptr, size, type);
    if (!obj) {
        free(ptr);
        return NULL;
    }
    
    gc->allocation_count++;
    
    /* Auto-collect if threshold reached */
    if (gc->auto_collect_enabled && 
        gc->allocation_count >= gc->collect_threshold) {
        gc_collect(gc);
        gc->allocation_count = 0;
    }
    
    return ptr;
}

GCObject* gc_track(GC *gc, void *ptr, size_t size, GCObjectType type) {
    if (!gc || !ptr) return NULL;
    
    /* Check if we need to expand tracking array */
    if (gc->object_count >= gc->object_capacity) {
        if (gc->object_capacity >= GC_MAX_OBJECTS) {
            fprintf(stderr, "[GC] Maximum object limit reached (%d)\n", GC_MAX_OBJECTS);
            return NULL;
        }
        
        gc->object_capacity *= 2;
        gc->objects = (GCObject **)realloc(gc->objects, 
                                           sizeof(GCObject *) * gc->object_capacity);
        if (!gc->objects) return NULL;
    }
    
    /* Create GCObject wrapper */
    GCObject *obj = (GCObject *)malloc(sizeof(GCObject));
    if (!obj) return NULL;
    
    obj->ptr = ptr;
    obj->type = type;
    obj->ref_count = 1;  /* Start with reference count of 1 */
    obj->freed = 0;
    obj->marked = 0;
    obj->size = size;
    obj->next = NULL;
    
    /* Add to tracking array */
    gc->objects[gc->object_count++] = obj;
    gc->total_allocated += size;
    
    return obj;
}

int gc_retain(GC *gc, void *ptr) {
    if (!gc || !ptr) return -1;
    
    GCObject *obj = gc_find_object(gc, ptr);
    if (!obj) return -1;
    if (obj->freed) return -1;
    
    obj->ref_count++;
    return obj->ref_count;
}

int gc_release(GC *gc, void *ptr) {
    if (!gc || !ptr) return -1;
    
    GCObject *obj = gc_find_object(gc, ptr);
    if (!obj) return -1;
    if (obj->freed) return -1;
    
    obj->ref_count--;
    
    /* Free if reference count reaches zero */
    if (obj->ref_count <= 0) {
        gc->total_freed += obj->size;
        
        /* Free the actual object (defensive) */
        if (!obj->freed) {
            obj->freed = 1;
            if (obj->ptr) {
                free(obj->ptr);
                obj->ptr = NULL;
            }
        }

        /* Remove from tracking and free wrapper */
        gc_remove_object(gc, obj);
        free(obj);
        
        return -1;  /* Indicate object was freed */
    }
    
    return obj->ref_count;
}

int gc_collect(GC *gc) {
    if (!gc) return 0;
    
    int freed_count = 0;
    int i = 0;
    
    while (i < gc->object_count) {
        GCObject *obj = gc->objects[i];
        
        if (obj && obj->ref_count <= 0) {
            /* Free the object */
            gc->total_freed += obj->size;
            if (!obj->freed) {
                obj->freed = 1;
                if (obj->ptr) {
                    free(obj->ptr);
                    obj->ptr = NULL;
                }
            }

            /* Remove from tracking and free wrapper */
            gc_remove_object(gc, obj);
            free(obj);
            
            freed_count++;
            /* Don't increment i since we shifted array down */
        } else {
            i++;
        }
    }
    
    gc->collection_count++;
    
    if (freed_count > 0) {
        printf("[GC] Collected %d objects\n", freed_count);
    }
    
    return freed_count;
}

int gc_collect_full(GC *gc) {
    if (!gc) return 0;
    
    /* Mark phase: clear all marks */
    for (int i = 0; i < gc->object_count; i++) {
        if (gc->objects[i]) {
            gc->objects[i]->marked = 0;
        }
    }
    
    /* Mark phase: mark reachable objects (ref_count > 0) */
    for (int i = 0; i < gc->object_count; i++) {
        if (gc->objects[i] && gc->objects[i]->ref_count > 0) {
            gc->objects[i]->marked = 1;
        }
    }
    
    /* Sweep phase: collect unmarked objects */
    int freed_count = 0;
    int i = 0;
    
    while (i < gc->object_count) {
        GCObject *obj = gc->objects[i];
        
        if (obj && !obj->marked) {
            /* Unreachable object - free it */
            gc->total_freed += obj->size;
            if (!obj->freed) {
                obj->freed = 1;
                if (obj->ptr) {
                    free(obj->ptr);
                    obj->ptr = NULL;
                }
            }

            gc_remove_object(gc, obj);
            free(obj);
            
            freed_count++;
        } else {
            i++;
        }
    }
    
    gc->collection_count++;
    
    if (freed_count > 0) {
        printf("[GC] Full collection freed %d objects\n", freed_count);
    }
    
    return freed_count;
}

void gc_free(GC *gc) {
    if (!gc) return;
    
    printf("[GC] Freeing garbage collector...\n");
    
    /* Free all tracked objects */
    for (int i = 0; i < gc->object_count; i++) {
        if (gc->objects[i]) {
            GCObject *obj = gc->objects[i];
            if (!obj->freed) {
                if (obj->ptr) {
                    free(obj->ptr);
                    obj->ptr = NULL;
                }
                obj->freed = 1;
            }
            free(obj);
        }
    }
    
    /* Free tracking array */
    if (gc->objects) {
        free(gc->objects);
    }
    
    /* Print final statistics */
    printf("[GC] Final statistics:\n");
    printf("  Total allocated: %zu bytes\n", gc->total_allocated);
    printf("  Total freed: %zu bytes\n", gc->total_freed);
    printf("  Collections: %d\n", gc->collection_count);
    
    free(gc);
}

/* ========== Reference Management ========== */

int gc_get_ref_count(GC *gc, void *ptr) {
    if (!gc || !ptr) return -1;
    
    GCObject *obj = gc_find_object(gc, ptr);
    return obj ? obj->ref_count : -1;
}

int gc_set_ref_count(GC *gc, void *ptr, int count) {
    if (!gc || !ptr || count < 0) return -1;
    
    GCObject *obj = gc_find_object(gc, ptr);
    if (!obj) return -1;
    
    obj->ref_count = count;
    return 0;
}

/* ========== Statistics & Debugging ========== */

size_t gc_get_allocated_bytes(GC *gc) {
    if (!gc) return 0;
    return gc->total_allocated - gc->total_freed;
}

int gc_get_object_count(GC *gc) {
    return gc ? gc->object_count : 0;
}

void gc_print_stats(GC *gc) {
    if (!gc) return;
    
    printf("\n[GC Statistics]\n");
    printf("  Objects tracked: %d\n", gc->object_count);
    printf("  Total allocated: %zu bytes\n", gc->total_allocated);
    printf("  Total freed: %zu bytes\n", gc->total_freed);
    printf("  Currently allocated: %zu bytes\n", gc_get_allocated_bytes(gc));
    printf("  Collections performed: %d\n", gc->collection_count);
    printf("  Auto-collect: %s\n", gc->auto_collect_enabled ? "enabled" : "disabled");
    printf("  Collect threshold: %d allocations\n", gc->collect_threshold);
    printf("\n");
}

void gc_print_objects(GC *gc) {
    if (!gc) return;
    
    printf("\n[GC Tracked Objects]\n");
    
    for (int i = 0; i < gc->object_count; i++) {
        GCObject *obj = gc->objects[i];
        if (obj) {
            printf("  [%d] %p: type=%s, refs=%d, size=%zu bytes\n",
                   i, obj->ptr, gc_type_name(obj->type), 
                   obj->ref_count, obj->size);
        }
    }
    
    printf("\n");
}

int gc_find_leaks(GC *gc) {
    if (!gc) return 0;
    
    int leak_count = 0;
    
    printf("\n[GC Leak Detection]\n");
    
    for (int i = 0; i < gc->object_count; i++) {
        GCObject *obj = gc->objects[i];
        if (obj && obj->ref_count > 0) {
            /* This is a potential leak - object has references but might be unreachable */
            printf("  Potential leak: %p (type=%s, refs=%d, size=%zu)\n",
                   obj->ptr, gc_type_name(obj->type), obj->ref_count, obj->size);
            leak_count++;
        }
    }
    
    if (leak_count == 0) {
        printf("  No leaks detected\n");
    } else {
        printf("  Found %d potential leaks\n", leak_count);
    }
    
    printf("\n");
    
    return leak_count;
}

/* ========== Configuration ========== */

void gc_set_auto_collect(GC *gc, int enabled) {
    if (gc) {
        gc->auto_collect_enabled = enabled;
    }
}

void gc_set_collect_threshold(GC *gc, int threshold) {
    if (gc && threshold > 0) {
        gc->collect_threshold = threshold;
    }
}

/* ========== Utility Functions ========== */

int gc_is_tracked(GC *gc, void *ptr) {
    return gc_find_object(gc, ptr) != NULL;
}

const char* gc_type_name(GCObjectType type) {
    switch (type) {
        case GC_TYPE_OBJECT: return "object";
        case GC_TYPE_ARRAY: return "array";
        case GC_TYPE_MAPPING: return "mapping";
        case GC_TYPE_STRING: return "string";
        case GC_TYPE_FUNCTION: return "function";
        case GC_TYPE_GENERIC: return "generic";
        default: return "unknown";
    }
}

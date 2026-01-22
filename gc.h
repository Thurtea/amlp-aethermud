/**
 * gc.h - Garbage Collection System Header
 * 
 * Reference-counted garbage collector for the AMLP LPC driver.
 * Manages automatic memory cleanup for objects, arrays, mappings, and strings.
 * 
 * Features:
 * - Reference counting for automatic cleanup
 * - Cycle detection for circular references
 * - Integration with object system
 * - Leak detection and reporting
 * - Configurable collection thresholds
 * 
 * Phase 5 Implementation - January 22, 2026
 */

#ifndef GC_H
#define GC_H

#include <stddef.h>

/* ========== Forward Declarations ========== */

typedef struct GCObject GCObject;
typedef struct GC GC;

/* ========== Constants ========== */

#define GC_INITIAL_CAPACITY 256
#define GC_COLLECT_THRESHOLD 1000    /* Collect after this many allocations */
#define GC_MAX_OBJECTS 100000         /* Maximum tracked objects */

/* ========== Object Types ========== */

typedef enum {
    GC_TYPE_OBJECT,        /* LPC object (obj_t) */
    GC_TYPE_ARRAY,         /* VM array */
    GC_TYPE_MAPPING,       /* VM mapping */
    GC_TYPE_STRING,        /* Heap-allocated string */
    GC_TYPE_FUNCTION,      /* VM function */
    GC_TYPE_GENERIC,       /* Generic allocation */
} GCObjectType;

/* ========== GC Object Wrapper ========== */

/**
 * Wrapper for any garbage-collected object
 * Tracks reference count and metadata
 */
struct GCObject {
    void *ptr;                  /* Pointer to actual object */
    GCObjectType type;          /* Type of object */
    int ref_count;              /* Reference count */
    int marked;                 /* Mark bit for cycle detection */
    size_t size;                /* Size in bytes */
    GCObject *next;             /* Next in linked list */
};

/* ========== Garbage Collector ========== */

/**
 * Main garbage collector structure
 * Tracks all allocated objects and manages cleanup
 */
struct GC {
    GCObject **objects;         /* Array of tracked objects */
    int object_count;           /* Number of tracked objects */
    int object_capacity;        /* Capacity of objects array */
    
    /* Statistics */
    size_t total_allocated;     /* Total bytes allocated */
    size_t total_freed;         /* Total bytes freed */
    int allocation_count;       /* Number of allocations since last collect */
    int collection_count;       /* Number of collections performed */
    
    /* Configuration */
    int collect_threshold;      /* Collect after this many allocations */
    int auto_collect_enabled;   /* Enable automatic collection */
};

/* ========== Core GC Functions ========== */

/**
 * Initialize the garbage collector
 * 
 * @return Pointer to GC instance, or NULL on failure
 */
GC* gc_init(void);

/**
 * Allocate memory tracked by GC
 * 
 * @param gc Garbage collector instance
 * @param size Size in bytes to allocate
 * @param type Type of object being allocated
 * @return Pointer to allocated memory, or NULL on failure
 */
void* gc_alloc(GC *gc, size_t size, GCObjectType type);

/**
 * Track an existing pointer with GC
 * Used for objects allocated outside GC that need tracking
 * 
 * @param gc Garbage collector instance
 * @param ptr Pointer to track
 * @param size Size of object
 * @param type Type of object
 * @return GCObject wrapper, or NULL on failure
 */
GCObject* gc_track(GC *gc, void *ptr, size_t size, GCObjectType type);

/**
 * Increment reference count
 * 
 * @param gc Garbage collector instance
 * @param ptr Pointer to object
 * @return New reference count, or -1 if not found
 */
int gc_retain(GC *gc, void *ptr);

/**
 * Decrement reference count and free if reaches zero
 * 
 * @param gc Garbage collector instance
 * @param ptr Pointer to object
 * @return New reference count, or -1 if freed/not found
 */
int gc_release(GC *gc, void *ptr);

/**
 * Perform garbage collection cycle
 * Frees all objects with ref_count == 0
 * 
 * @param gc Garbage collector instance
 * @return Number of objects freed
 */
int gc_collect(GC *gc);

/**
 * Perform full collection including cycle detection
 * More expensive than gc_collect() but handles circular references
 * 
 * @param gc Garbage collector instance
 * @return Number of objects freed
 */
int gc_collect_full(GC *gc);

/**
 * Free all objects and the GC itself
 * 
 * @param gc Garbage collector instance
 */
void gc_free(GC *gc);

/* ========== Reference Management ========== */

/**
 * Get reference count of an object
 * 
 * @param gc Garbage collector instance
 * @param ptr Pointer to object
 * @return Reference count, or -1 if not found
 */
int gc_get_ref_count(GC *gc, void *ptr);

/**
 * Set reference count directly (advanced usage)
 * 
 * @param gc Garbage collector instance
 * @param ptr Pointer to object
 * @param count New reference count
 * @return 0 on success, -1 on failure
 */
int gc_set_ref_count(GC *gc, void *ptr, int count);

/* ========== Statistics & Debugging ========== */

/**
 * Get total memory currently allocated
 * 
 * @param gc Garbage collector instance
 * @return Total bytes allocated
 */
size_t gc_get_allocated_bytes(GC *gc);

/**
 * Get number of tracked objects
 * 
 * @param gc Garbage collector instance
 * @return Number of objects
 */
int gc_get_object_count(GC *gc);

/**
 * Print GC statistics
 * 
 * @param gc Garbage collector instance
 */
void gc_print_stats(GC *gc);

/**
 * Print all tracked objects (debug)
 * 
 * @param gc Garbage collector instance
 */
void gc_print_objects(GC *gc);

/**
 * Find memory leaks (objects with ref_count > 0 that are unreachable)
 * 
 * @param gc Garbage collector instance
 * @return Number of potential leaks found
 */
int gc_find_leaks(GC *gc);

/* ========== Configuration ========== */

/**
 * Enable or disable automatic collection
 * 
 * @param gc Garbage collector instance
 * @param enabled 1 to enable, 0 to disable
 */
void gc_set_auto_collect(GC *gc, int enabled);

/**
 * Set collection threshold (number of allocations before auto-collect)
 * 
 * @param gc Garbage collector instance
 * @param threshold Number of allocations
 */
void gc_set_collect_threshold(GC *gc, int threshold);

/* ========== Utility Functions ========== */

/**
 * Find GCObject wrapper for a pointer
 * 
 * @param gc Garbage collector instance
 * @param ptr Pointer to find
 * @return GCObject wrapper, or NULL if not found
 */
GCObject* gc_find_object(GC *gc, void *ptr);

/**
 * Check if pointer is tracked by GC
 * 
 * @param gc Garbage collector instance
 * @param ptr Pointer to check
 * @return 1 if tracked, 0 otherwise
 */
int gc_is_tracked(GC *gc, void *ptr);

/**
 * Get type name string
 * 
 * @param type GC object type
 * @return Type name string
 */
const char* gc_type_name(GCObjectType type);

#endif /* GC_H */

/**
 * object.h - LPC Object System Header
 * 
 * Defines the object type system for the AMLP LPC driver.
 * Objects are the fundamental building blocks of LPC programs:
 * - Have properties (data members stored in hash map)
 * - Have methods (functions defined in the object)
 * - Support inheritance (prototype chain)
 * - Can be instantiated/cloned
 * 
 * Architecture:
 *   obj_t: Core object structure
 *   - name: Object identifier
 *   - proto: Prototype (parent) for inheritance
 *   - properties: Hash map of property name -> VMValue
 *   - methods: Array of functions defined in this object
 * 
 * Phase 4 Implementation - January 22, 2026
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "vm.h"
#include <stddef.h>

/* ========== Forward Declarations ========== */

typedef struct obj_t obj_t;
typedef struct ObjProperty ObjProperty;
typedef struct ObjManager ObjManager;

/* ========== Constants ========== */

#define OBJ_PROPERTY_HASH_SIZE 32
#define OBJ_INITIAL_METHOD_CAPACITY 16
#define OBJ_MANAGER_INITIAL_CAPACITY 128

/* ========== Object Property (Hash Map Entry) ========== */

/**
 * Property entry in object property hash map
 * Stores name-value pairs with chaining for collision resolution
 */
typedef struct ObjProperty {
    char *name;                     /* Property name (heap-allocated) */
    VMValue value;                  /* Property value */
    struct ObjProperty *next;       /* Next entry in collision chain */
} ObjProperty;

/* ========== Object Structure ========== */

/**
 * Core object structure
 * Represents a single LPC object with properties, methods, and inheritance
 */
struct obj_t {
    char *name;                     /* Object name/identifier (heap-allocated) */
    obj_t *proto;                   /* Prototype (parent) for inheritance, or NULL */
    
    /* Properties (hash map) */
    ObjProperty **properties;       /* Hash table of properties */
    int property_count;             /* Number of properties stored */
    int property_capacity;          /* Capacity of hash table */
    
    /* Methods (array of function pointers) */
    VMFunction **methods;           /* Array of method function pointers */
    int method_count;               /* Number of methods */
    int method_capacity;            /* Capacity of methods array */
    
    /* Reference counting for garbage collection */
    int ref_count;                  /* Reference count (future use) */
    
    /* Object state */
    int is_destroyed;               /* Flag: 1 if object is destroyed */
};

/* ========== Object Manager ========== */

/**
 * Global object registry and manager
 * Tracks all active objects in the system
 */
struct ObjManager {
    obj_t **objects;                /* Array of object pointers */
    int object_count;               /* Number of active objects */
    int object_capacity;            /* Capacity of objects array */
};

/* ========== Object Lifecycle Functions ========== */

/**
 * Create a new object with the given name
 * 
 * @param name Object name/identifier
 * @return Pointer to newly allocated object, or NULL on failure
 */
obj_t* obj_new(const char *name);

/**
 * Clone an existing object (shallow copy with inheritance)
 * Creates a new object with the original as its prototype
 * 
 * @param original Object to clone
 * @return Pointer to cloned object, or NULL on failure
 */
obj_t* obj_clone(obj_t *original);

/**
 * Destroy an object and free its resources
 * Marks object as destroyed and frees all properties/methods
 * 
 * @param obj Object to destroy
 */
void obj_destroy(obj_t *obj);

/**
 * Completely free an object's memory
 * Called after obj_destroy() when ready to deallocate
 * 
 * @param obj Object to free
 */
void obj_free(obj_t *obj);

/* ========== Property Access Functions ========== */

/**
 * Get a property value from an object
 * Searches object, then walks prototype chain
 * 
 * @param obj Object to query
 * @param prop_name Property name
 * @return Property value, or VALUE_NULL if not found
 */
VMValue obj_get_prop(obj_t *obj, const char *prop_name);

/**
 * Set a property value on an object
 * Creates property if it doesn't exist
 * 
 * @param obj Object to modify
 * @param prop_name Property name
 * @param value Value to set
 * @return 0 on success, -1 on failure
 */
int obj_set_prop(obj_t *obj, const char *prop_name, VMValue value);

/**
 * Check if object has a property (own or inherited)
 * 
 * @param obj Object to query
 * @param prop_name Property name
 * @return 1 if property exists, 0 otherwise
 */
int obj_has_prop(obj_t *obj, const char *prop_name);

/**
 * Delete a property from an object
 * Only deletes from this object, not prototype
 * 
 * @param obj Object to modify
 * @param prop_name Property name to delete
 * @return 0 on success, -1 if property not found
 */
int obj_delete_prop(obj_t *obj, const char *prop_name);

/* ========== Method Management Functions ========== */

/**
 * Add a method to an object
 * Methods are stored as function pointers
 * 
 * @param obj Object to modify
 * @param method Function pointer to add
 * @return Method index on success, -1 on failure
 */
int obj_add_method(obj_t *obj, VMFunction *method);

/**
 * Get a method by name from object or prototype chain
 * 
 * @param obj Object to query
 * @param method_name Method name
 * @return Function pointer, or NULL if not found
 */
VMFunction* obj_get_method(obj_t *obj, const char *method_name);

/**
 * Call a method on an object
 * Looks up method by name and invokes it with arguments
 * 
 * @param vm Virtual machine context
 * @param obj Object instance
 * @param method_name Method to call
 * @param args Array of arguments
 * @param arg_count Number of arguments
 * @return Result value from method call
 */
VMValue obj_call_method(VirtualMachine *vm, obj_t *obj, const char *method_name, 
                        VMValue *args, int arg_count);

/* ========== Inheritance Functions ========== */

/**
 * Set the prototype (parent) of an object for inheritance
 * 
 * @param obj Object to modify
 * @param proto Prototype object
 */
void obj_set_proto(obj_t *obj, obj_t *proto);

/**
 * Get the prototype of an object
 * 
 * @param obj Object to query
 * @return Prototype object, or NULL if no prototype
 */
obj_t* obj_get_proto(obj_t *obj);

/* ========== Object Manager Functions ========== */

/**
 * Initialize the global object manager
 * 
 * @return Pointer to object manager, or NULL on failure
 */
ObjManager* obj_manager_init(void);

/**
 * Register an object with the manager
 * 
 * @param manager Object manager
 * @param obj Object to register
 * @return 0 on success, -1 on failure
 */
int obj_manager_register(ObjManager *manager, obj_t *obj);

/**
 * Unregister an object from the manager
 * 
 * @param manager Object manager
 * @param obj Object to unregister
 * @return 0 on success, -1 on failure
 */
int obj_manager_unregister(ObjManager *manager, obj_t *obj);

/**
 * Find an object by name in the manager
 * 
 * @param manager Object manager
 * @param name Object name
 * @return Object pointer, or NULL if not found
 */
obj_t* obj_manager_find(ObjManager *manager, const char *name);

/**
 * Free all objects and the manager
 * 
 * @param manager Object manager to free
 */
void obj_manager_free(ObjManager *manager);

/* ========== Utility Functions ========== */

/**
 * Print object information (for debugging)
 * 
 * @param obj Object to print
 */
void obj_print(obj_t *obj);

/**
 * Get property count (including inherited)
 * 
 * @param obj Object to query
 * @return Total property count
 */
int obj_get_property_count(obj_t *obj);

/**
 * Get method count (including inherited)
 * 
 * @param obj Object to query
 * @return Total method count
 */
int obj_get_method_count(obj_t *obj);

#endif /* OBJECT_H */

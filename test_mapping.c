/**
 * test_mapping.c - Mapping Module Test Suite
 * 
 * Comprehensive tests for GC-aware hash maps.
 * 
 * Phase 6 - January 22, 2026
 */

#include "mapping.h"
#include "array.h"
#include "vm.h"
#include "gc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* ========== Test Framework ========== */

static int test_count = 0;
static int test_passed = 0;
static int test_failed = 0;

void test_setup(const char *test_name) {
    test_count++;
    printf("\n[TEST %d] %s\n", test_count, test_name);
}

void test_assert(int condition, const char *message) {
    if (condition) {
        printf("  ✓ PASS\n");
        test_passed++;
    } else {
        printf("  ✗ FAIL: %s\n", message);
        test_failed++;
    }
}

/* ========== TESTS: Mapping Creation ========== */

void test_mapping_new(void) {
    test_setup("Create new mapping");
    
    GC *gc = gc_init();
    mapping_t *map = mapping_new(gc, 16);
    
    test_assert(map != NULL, "Mapping should be created");
    test_assert(mapping_size(map) == 0, "Initial size should be 0");
    test_assert(map->bucket_count == 16, "Bucket count should be 16");
    
    mapping_free(map);
    gc_free(gc);
}

void test_mapping_new_zero_buckets(void) {
    test_setup("Create mapping with zero buckets");
    
    GC *gc = gc_init();
    mapping_t *map = mapping_new(gc, 0);
    
    test_assert(map != NULL, "Mapping should be created");
    test_assert(map->bucket_count > 0, "Should have default bucket count");
    
    mapping_free(map);
    gc_free(gc);
}

void test_mapping_new_no_gc(void) {
    test_setup("Create mapping without GC");
    
    mapping_t *map = mapping_new(NULL, 8);
    
    test_assert(map != NULL, "Mapping should be created without GC");
    test_assert(mapping_size(map) == 0, "Size should be 0");
    
    mapping_free(map);
}

/* ========== TESTS: Set/Get Operations ========== */

void test_mapping_set(void) {
    test_setup("Set key-value pairs");
    
    GC *gc = gc_init();
    mapping_t *map = mapping_new(gc, 16);
    
    mapping_entry_t *e1 = mapping_set(map, "name", vm_value_create_string("Alice"));
    mapping_entry_t *e2 = mapping_set(map, "age", vm_value_create_int(30));
    mapping_entry_t *e3 = mapping_set(map, "score", vm_value_create_float(95.5));
    
    test_assert(e1 != NULL && e2 != NULL && e3 != NULL, "Set should succeed");
    test_assert(mapping_size(map) == 3, "Size should be 3");
    
    mapping_free(map);
    gc_free(gc);
}

void test_mapping_get(void) {
    test_setup("Get values by key");
    
    GC *gc = gc_init();
    mapping_t *map = mapping_new(gc, 16);
    
    mapping_set(map, "city", vm_value_create_string("New York"));
    mapping_set(map, "population", vm_value_create_int(8000000));
    
    VMValue v1 = mapping_get(map, "city");
    VMValue v2 = mapping_get(map, "population");
    
    test_assert(v1.type == VALUE_STRING, "Type should be STRING");
    test_assert(strcmp(v1.data.string_value, "New York") == 0, "Value should be 'New York'");
    test_assert(v2.type == VALUE_INT, "Type should be INT");
    test_assert(v2.data.int_value == 8000000, "Value should be 8000000");
    
    mapping_free(map);
    gc_free(gc);
}

void test_mapping_get_nonexistent(void) {
    test_setup("Get nonexistent key");
    
    GC *gc = gc_init();
    mapping_t *map = mapping_new(gc, 16);
    
    mapping_set(map, "exists", vm_value_create_int(1));
    
    VMValue v = mapping_get(map, "does_not_exist");
    
    test_assert(v.type == VALUE_NULL, "Nonexistent key should return NULL");
    
    mapping_free(map);
    gc_free(gc);
}

void test_mapping_set_update(void) {
    test_setup("Update existing key");
    
    GC *gc = gc_init();
    mapping_t *map = mapping_new(gc, 16);
    
    mapping_set(map, "counter", vm_value_create_int(1));
    mapping_set(map, "counter", vm_value_create_int(2));
    mapping_set(map, "counter", vm_value_create_int(3));
    
    test_assert(mapping_size(map) == 1, "Size should remain 1 (update)");
    
    VMValue v = mapping_get(map, "counter");
    test_assert(v.data.int_value == 3, "Value should be updated to 3");
    
    mapping_free(map);
    gc_free(gc);
}

/* ========== TESTS: Delete Operations ========== */

void test_mapping_delete(void) {
    test_setup("Delete key-value pair");
    
    GC *gc = gc_init();
    mapping_t *map = mapping_new(gc, 16);
    
    mapping_set(map, "key1", vm_value_create_int(1));
    mapping_set(map, "key2", vm_value_create_int(2));
    mapping_set(map, "key3", vm_value_create_int(3));
    
    int result = mapping_delete(map, "key2");
    
    test_assert(result == 0, "Delete should succeed");
    test_assert(mapping_size(map) == 2, "Size should be 2 after delete");
    test_assert(mapping_get(map, "key2").type == VALUE_NULL, "Deleted key should return NULL");
    test_assert(mapping_get(map, "key1").data.int_value == 1, "Other keys should remain");
    test_assert(mapping_get(map, "key3").data.int_value == 3, "Other keys should remain");
    
    mapping_free(map);
    gc_free(gc);
}

void test_mapping_delete_nonexistent(void) {
    test_setup("Delete nonexistent key");
    
    GC *gc = gc_init();
    mapping_t *map = mapping_new(gc, 16);
    
    mapping_set(map, "exists", vm_value_create_int(1));
    
    int result = mapping_delete(map, "does_not_exist");
    
    test_assert(result == -1, "Delete nonexistent key should fail");
    test_assert(mapping_size(map) == 1, "Size should remain 1");
    
    mapping_free(map);
    gc_free(gc);
}

void test_mapping_delete_all(void) {
    test_setup("Delete all entries");
    
    GC *gc = gc_init();
    mapping_t *map = mapping_new(gc, 16);
    
    mapping_set(map, "a", vm_value_create_int(1));
    mapping_set(map, "b", vm_value_create_int(2));
    mapping_set(map, "c", vm_value_create_int(3));
    
    mapping_delete(map, "a");
    mapping_delete(map, "b");
    mapping_delete(map, "c");
    
    test_assert(mapping_size(map) == 0, "Size should be 0 after deleting all");
    
    mapping_free(map);
    gc_free(gc);
}

/* ========== TESTS: Keys/Values Operations ========== */

void test_mapping_keys(void) {
    test_setup("Get all keys as array");
    
    GC *gc = gc_init();
    mapping_t *map = mapping_new(gc, 16);
    
    mapping_set(map, "apple", vm_value_create_int(1));
    mapping_set(map, "banana", vm_value_create_int(2));
    mapping_set(map, "cherry", vm_value_create_int(3));
    
    array_t *keys = mapping_keys(map);
    
    test_assert(keys != NULL, "Keys array should be created");
    test_assert(array_length(keys) == 3, "Should have 3 keys");
    
    /* Check that all keys are present (order doesn't matter) */
    int found_apple = 0, found_banana = 0, found_cherry = 0;
    for (size_t i = 0; i < array_length(keys); i++) {
        VMValue key = array_get(keys, i);
        if (key.type == VALUE_STRING) {
            if (strcmp(key.data.string_value, "apple") == 0) found_apple = 1;
            if (strcmp(key.data.string_value, "banana") == 0) found_banana = 1;
            if (strcmp(key.data.string_value, "cherry") == 0) found_cherry = 1;
        }
    }
    
    test_assert(found_apple && found_banana && found_cherry, "All keys should be present");
    
    array_free(keys);
    mapping_free(map);
    gc_free(gc);
}

void test_mapping_values(void) {
    test_setup("Get all values as array");
    
    GC *gc = gc_init();
    mapping_t *map = mapping_new(gc, 16);
    
    mapping_set(map, "x", vm_value_create_int(10));
    mapping_set(map, "y", vm_value_create_int(20));
    mapping_set(map, "z", vm_value_create_int(30));
    
    array_t *values = mapping_values(map);
    
    test_assert(values != NULL, "Values array should be created");
    test_assert(array_length(values) == 3, "Should have 3 values");
    
    /* Check that all values are present (order doesn't matter) */
    int found_10 = 0, found_20 = 0, found_30 = 0;
    for (size_t i = 0; i < array_length(values); i++) {
        VMValue val = array_get(values, i);
        if (val.type == VALUE_INT) {
            if (val.data.int_value == 10) found_10 = 1;
            if (val.data.int_value == 20) found_20 = 1;
            if (val.data.int_value == 30) found_30 = 1;
        }
    }
    
    test_assert(found_10 && found_20 && found_30, "All values should be present");
    
    array_free(values);
    mapping_free(map);
    gc_free(gc);
}

void test_mapping_keys_empty(void) {
    test_setup("Get keys from empty mapping");
    
    GC *gc = gc_init();
    mapping_t *map = mapping_new(gc, 16);
    
    array_t *keys = mapping_keys(map);
    
    test_assert(keys != NULL, "Keys array should be created");
    test_assert(array_length(keys) == 0, "Empty mapping should have 0 keys");
    
    array_free(keys);
    mapping_free(map);
    gc_free(gc);
}

/* ========== TESTS: Clone Operations ========== */

void test_mapping_clone(void) {
    test_setup("Clone mapping");
    
    GC *gc = gc_init();
    mapping_t *map = mapping_new(gc, 16);
    
    mapping_set(map, "name", vm_value_create_string("Bob"));
    mapping_set(map, "age", vm_value_create_int(25));
    
    mapping_t *clone = mapping_clone(map, gc);
    
    test_assert(clone != NULL, "Clone should be created");
    test_assert(clone != map, "Clone should be different object");
    test_assert(mapping_size(clone) == 2, "Clone should have same size");
    
    VMValue v1 = mapping_get(clone, "name");
    VMValue v2 = mapping_get(clone, "age");
    
    test_assert(v1.type == VALUE_STRING, "Clone should have name");
    test_assert(strcmp(v1.data.string_value, "Bob") == 0, "Name should be 'Bob'");
    test_assert(v2.data.int_value == 25, "Age should be 25");
    
    mapping_free(clone);
    mapping_free(map);
    gc_free(gc);
}

void test_mapping_clone_empty(void) {
    test_setup("Clone empty mapping");
    
    GC *gc = gc_init();
    mapping_t *map = mapping_new(gc, 16);
    
    mapping_t *clone = mapping_clone(map, gc);
    
    test_assert(clone != NULL, "Clone of empty mapping should be created");
    test_assert(mapping_size(clone) == 0, "Clone should be empty");
    
    mapping_free(clone);
    mapping_free(map);
    gc_free(gc);
}

void test_mapping_clone_independence(void) {
    test_setup("Clone independence (modification)");
    
    GC *gc = gc_init();
    mapping_t *map = mapping_new(gc, 16);
    
    mapping_set(map, "value", vm_value_create_int(100));
    
    mapping_t *clone = mapping_clone(map, gc);
    
    mapping_set(map, "value", vm_value_create_int(999));
    
    test_assert(mapping_get(map, "value").data.int_value == 999, "Original should be modified");
    test_assert(mapping_get(clone, "value").data.int_value == 100, "Clone should be unchanged");
    
    mapping_free(clone);
    mapping_free(map);
    gc_free(gc);
}

/* ========== TESTS: Size Tracking ========== */

void test_mapping_size(void) {
    test_setup("Mapping size tracking");
    
    GC *gc = gc_init();
    mapping_t *map = mapping_new(gc, 16);
    
    test_assert(mapping_size(map) == 0, "Initial size 0");
    
    mapping_set(map, "a", vm_value_create_int(1));
    test_assert(mapping_size(map) == 1, "Size 1 after set");
    
    mapping_set(map, "b", vm_value_create_int(2));
    test_assert(mapping_size(map) == 2, "Size 2 after set");
    
    mapping_set(map, "a", vm_value_create_int(3));
    test_assert(mapping_size(map) == 2, "Size 2 after update (not insert)");
    
    mapping_delete(map, "a");
    test_assert(mapping_size(map) == 1, "Size 1 after delete");
    
    mapping_free(map);
    gc_free(gc);
}

/* ========== TESTS: Hash Collisions ========== */

void test_mapping_many_entries(void) {
    test_setup("Many entries (hash collision handling)");
    
    GC *gc = gc_init();
    mapping_t *map = mapping_new(gc, 4);  /* Small bucket count */
    
    char key[32];
    for (int i = 0; i < 20; i++) {
        snprintf(key, sizeof(key), "key_%d", i);
        mapping_set(map, key, vm_value_create_int(i * 10));
    }
    
    test_assert(mapping_size(map) == 20, "Should have 20 entries");
    
    /* Verify all entries can be retrieved */
    int all_found = 1;
    for (int i = 0; i < 20; i++) {
        snprintf(key, sizeof(key), "key_%d", i);
        VMValue v = mapping_get(map, key);
        if (v.type != VALUE_INT || v.data.int_value != i * 10) {
            all_found = 0;
            break;
        }
    }
    
    test_assert(all_found, "All entries should be retrievable");
    
    mapping_free(map);
    gc_free(gc);
}

/* ========== TESTS: Edge Cases ========== */

void test_mapping_mixed_value_types(void) {
    test_setup("Mapping with mixed value types");
    
    GC *gc = gc_init();
    mapping_t *map = mapping_new(gc, 16);
    
    mapping_set(map, "int_val", vm_value_create_int(42));
    mapping_set(map, "float_val", vm_value_create_float(3.14));
    mapping_set(map, "string_val", vm_value_create_string("hello"));
    mapping_set(map, "null_val", vm_value_create_null());
    
    test_assert(mapping_size(map) == 4, "Should have 4 entries");
    test_assert(mapping_get(map, "int_val").type == VALUE_INT, "int_val should be INT");
    test_assert(mapping_get(map, "float_val").type == VALUE_FLOAT, "float_val should be FLOAT");
    test_assert(mapping_get(map, "string_val").type == VALUE_STRING, "string_val should be STRING");
    test_assert(mapping_get(map, "null_val").type == VALUE_NULL, "null_val should be NULL");
    
    mapping_free(map);
    gc_free(gc);
}

void test_mapping_empty_key(void) {
    test_setup("Mapping with empty string key");
    
    GC *gc = gc_init();
    mapping_t *map = mapping_new(gc, 16);
    
    mapping_entry_t *entry = mapping_set(map, "", vm_value_create_int(999));
    
    test_assert(entry != NULL, "Empty key should be allowed");
    test_assert(mapping_get(map, "").data.int_value == 999, "Empty key should retrieve value");
    
    mapping_free(map);
    gc_free(gc);
}

void test_mapping_null_handling(void) {
    test_setup("Mapping operations with NULL");
    
    test_assert(mapping_size(NULL) == 0, "Size of NULL mapping should be 0");
    test_assert(mapping_set(NULL, "key", vm_value_create_int(1)) == NULL, "Set to NULL should fail");
    test_assert(mapping_get(NULL, "key").type == VALUE_NULL, "Get from NULL should return NULL");
    test_assert(mapping_delete(NULL, "key") == -1, "Delete from NULL should fail");
    test_assert(mapping_keys(NULL) == NULL, "Keys of NULL should return NULL");
    test_assert(mapping_values(NULL) == NULL, "Values of NULL should return NULL");
    test_assert(mapping_clone(NULL, NULL) == NULL, "Clone NULL should return NULL");
    
    mapping_free(NULL);  /* Should not crash */
    test_assert(1, "Free NULL should not crash");
}

/* ========== TESTS: GC Integration ========== */

void test_mapping_gc_allocation(void) {
    test_setup("Mapping GC allocation tracking");
    
    GC *gc = gc_init();
    size_t before = gc->total_allocated;
    
    mapping_t *map = mapping_new(gc, 16);
    mapping_set(map, "test", vm_value_create_int(1));
    
    test_assert(gc->total_allocated > before, "GC should track allocation");
    
    mapping_free(map);
    
    test_assert(gc->total_freed > 0, "GC should track deallocation");
    
    gc_free(gc);
}

void test_mapping_multiple_gc_mappings(void) {
    test_setup("Multiple mappings with same GC");
    
    GC *gc = gc_init();
    
    mapping_t *map1 = mapping_new(gc, 8);
    mapping_t *map2 = mapping_new(gc, 8);
    mapping_t *map3 = mapping_new(gc, 8);
    
    mapping_set(map1, "id", vm_value_create_int(1));
    mapping_set(map2, "id", vm_value_create_int(2));
    mapping_set(map3, "id", vm_value_create_int(3));
    
    test_assert(mapping_get(map1, "id").data.int_value == 1, "Mapping 1 should be independent");
    test_assert(mapping_get(map2, "id").data.int_value == 2, "Mapping 2 should be independent");
    test_assert(mapping_get(map3, "id").data.int_value == 3, "Mapping 3 should be independent");
    
    mapping_free(map1);
    mapping_free(map2);
    mapping_free(map3);
    gc_free(gc);
}

/* ========== Main Test Runner ========== */

int main(void) {
    printf("\n========================================\n");
    printf("AMLP Mapping Module - Test Suite\n");
    printf("========================================\n");
    
    /* Mapping Creation Tests */
    test_mapping_new();
    test_mapping_new_zero_buckets();
    test_mapping_new_no_gc();
    
    /* Set/Get Tests */
    test_mapping_set();
    test_mapping_get();
    test_mapping_get_nonexistent();
    test_mapping_set_update();
    
    /* Delete Tests */
    test_mapping_delete();
    test_mapping_delete_nonexistent();
    test_mapping_delete_all();
    
    /* Keys/Values Tests */
    test_mapping_keys();
    test_mapping_values();
    test_mapping_keys_empty();
    
    /* Clone Tests */
    test_mapping_clone();
    test_mapping_clone_empty();
    test_mapping_clone_independence();
    
    /* Size Tracking */
    test_mapping_size();
    
    /* Hash Collision Tests */
    test_mapping_many_entries();
    
    /* Edge Cases */
    test_mapping_mixed_value_types();
    test_mapping_empty_key();
    test_mapping_null_handling();
    
    /* GC Integration Tests */
    test_mapping_gc_allocation();
    test_mapping_multiple_gc_mappings();
    
    /* Summary */
    printf("\n========================================\n");
    printf("Test Results: %d/%d passed", test_passed, test_count);
    if (test_failed > 0) {
        printf(" (%d failed)", test_failed);
    }
    printf("\n========================================\n\n");
    
    return (test_failed == 0) ? 0 : 1;
}

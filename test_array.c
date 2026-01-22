/**
 * test_array.c - Array Module Test Suite
 * 
 * Comprehensive tests for GC-aware dynamic arrays.
 * 
 * Phase 6 - January 22, 2026
 */

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

/* ========== TESTS: Array Creation ========== */

void test_array_new(void) {
    test_setup("Create new array");
    
    GC *gc = gc_init();
    array_t *arr = array_new(gc, 10);
    
    test_assert(arr != NULL, "Array should be created");
    test_assert(array_length(arr) == 0, "Initial length should be 0");
    test_assert(arr->capacity >= 10, "Capacity should be at least 10");
    
    array_free(arr);
    gc_free(gc);
}

void test_array_new_zero_capacity(void) {
    test_setup("Create array with zero capacity");
    
    GC *gc = gc_init();
    array_t *arr = array_new(gc, 0);
    
    test_assert(arr != NULL, "Array should be created");
    test_assert(arr->capacity > 0, "Should have default capacity");
    
    array_free(arr);
    gc_free(gc);
}

void test_array_new_no_gc(void) {
    test_setup("Create array without GC");
    
    array_t *arr = array_new(NULL, 5);
    
    test_assert(arr != NULL, "Array should be created without GC");
    test_assert(array_length(arr) == 0, "Length should be 0");
    
    array_free(arr);
}

/* ========== TESTS: Push/Pop Operations ========== */

void test_array_push(void) {
    test_setup("Push elements to array");
    
    GC *gc = gc_init();
    array_t *arr = array_new(gc, 2);
    
    int result1 = array_push(arr, vm_value_create_int(10));
    int result2 = array_push(arr, vm_value_create_int(20));
    int result3 = array_push(arr, vm_value_create_int(30));
    
    test_assert(result1 == 0 && result2 == 0 && result3 == 0, "Push should succeed");
    test_assert(array_length(arr) == 3, "Length should be 3");
    test_assert(array_get(arr, 0).data.int_value == 10, "First element should be 10");
    test_assert(array_get(arr, 1).data.int_value == 20, "Second element should be 20");
    test_assert(array_get(arr, 2).data.int_value == 30, "Third element should be 30");
    
    array_free(arr);
    gc_free(gc);
}

void test_array_pop(void) {
    test_setup("Pop elements from array");
    
    GC *gc = gc_init();
    array_t *arr = array_new(gc, 5);
    
    array_push(arr, vm_value_create_int(100));
    array_push(arr, vm_value_create_int(200));
    array_push(arr, vm_value_create_int(300));
    
    VMValue val;
    int result = array_pop(arr, &val);
    
    test_assert(result == 0, "Pop should succeed");
    test_assert(val.data.int_value == 300, "Popped value should be 300");
    test_assert(array_length(arr) == 2, "Length should be 2 after pop");
    
    array_free(arr);
    gc_free(gc);
}

void test_array_pop_empty(void) {
    test_setup("Pop from empty array");
    
    GC *gc = gc_init();
    array_t *arr = array_new(gc, 5);
    
    VMValue val;
    int result = array_pop(arr, &val);
    
    test_assert(result == -1, "Pop from empty array should fail");
    
    array_free(arr);
    gc_free(gc);
}

void test_array_push_resize(void) {
    test_setup("Push with automatic resize");
    
    GC *gc = gc_init();
    array_t *arr = array_new(gc, 2);
    
    for (int i = 0; i < 10; i++) {
        array_push(arr, vm_value_create_int(i));
    }
    
    test_assert(array_length(arr) == 10, "Should have 10 elements");
    test_assert(arr->capacity >= 10, "Capacity should grow");
    test_assert(array_get(arr, 9).data.int_value == 9, "Last element should be 9");
    
    array_free(arr);
    gc_free(gc);
}

/* ========== TESTS: Get/Set Operations ========== */

void test_array_get(void) {
    test_setup("Get element by index");
    
    GC *gc = gc_init();
    array_t *arr = array_new(gc, 5);
    
    array_push(arr, vm_value_create_string("first"));
    array_push(arr, vm_value_create_string("second"));
    array_push(arr, vm_value_create_string("third"));
    
    VMValue v0 = array_get(arr, 0);
    VMValue v1 = array_get(arr, 1);
    VMValue v2 = array_get(arr, 2);
    
    test_assert(v0.type == VALUE_STRING, "Type should be STRING");
    test_assert(strcmp(v0.data.string_value, "first") == 0, "Should get 'first'");
    test_assert(strcmp(v1.data.string_value, "second") == 0, "Should get 'second'");
    test_assert(strcmp(v2.data.string_value, "third") == 0, "Should get 'third'");
    
    array_free(arr);
    gc_free(gc);
}

void test_array_get_out_of_bounds(void) {
    test_setup("Get with out-of-bounds index");
    
    GC *gc = gc_init();
    array_t *arr = array_new(gc, 5);
    
    array_push(arr, vm_value_create_int(42));
    
    VMValue v = array_get(arr, 10);
    
    test_assert(v.type == VALUE_NULL, "Out-of-bounds should return NULL");
    
    array_free(arr);
    gc_free(gc);
}

void test_array_set(void) {
    test_setup("Set element by index");
    
    GC *gc = gc_init();
    array_t *arr = array_new(gc, 5);
    
    array_push(arr, vm_value_create_int(1));
    array_push(arr, vm_value_create_int(2));
    array_push(arr, vm_value_create_int(3));
    
    int result = array_set(arr, 1, vm_value_create_int(999));
    
    test_assert(result == 0, "Set should succeed");
    test_assert(array_get(arr, 1).data.int_value == 999, "Value should be updated to 999");
    test_assert(array_length(arr) == 3, "Length should remain 3");
    
    array_free(arr);
    gc_free(gc);
}

void test_array_set_out_of_bounds(void) {
    test_setup("Set with out-of-bounds index");
    
    GC *gc = gc_init();
    array_t *arr = array_new(gc, 5);
    
    array_push(arr, vm_value_create_int(1));
    
    int result = array_set(arr, 10, vm_value_create_int(999));
    
    test_assert(result == -1, "Set out-of-bounds should fail");
    
    array_free(arr);
    gc_free(gc);
}

/* ========== TESTS: Insert/Delete Operations ========== */

void test_array_insert(void) {
    test_setup("Insert element at index");
    
    GC *gc = gc_init();
    array_t *arr = array_new(gc, 5);
    
    array_push(arr, vm_value_create_int(10));
    array_push(arr, vm_value_create_int(30));
    
    int result = array_insert(arr, 1, vm_value_create_int(20));
    
    test_assert(result == 0, "Insert should succeed");
    test_assert(array_length(arr) == 3, "Length should be 3");
    test_assert(array_get(arr, 0).data.int_value == 10, "Element 0 should be 10");
    test_assert(array_get(arr, 1).data.int_value == 20, "Element 1 should be 20");
    test_assert(array_get(arr, 2).data.int_value == 30, "Element 2 should be 30");
    
    array_free(arr);
    gc_free(gc);
}

void test_array_insert_at_end(void) {
    test_setup("Insert at end of array");
    
    GC *gc = gc_init();
    array_t *arr = array_new(gc, 5);
    
    array_push(arr, vm_value_create_int(1));
    array_push(arr, vm_value_create_int(2));
    
    int result = array_insert(arr, 2, vm_value_create_int(3));
    
    test_assert(result == 0, "Insert at end should succeed");
    test_assert(array_length(arr) == 3, "Length should be 3");
    test_assert(array_get(arr, 2).data.int_value == 3, "Last element should be 3");
    
    array_free(arr);
    gc_free(gc);
}

void test_array_delete(void) {
    test_setup("Delete element by index");
    
    GC *gc = gc_init();
    array_t *arr = array_new(gc, 5);
    
    array_push(arr, vm_value_create_int(10));
    array_push(arr, vm_value_create_int(20));
    array_push(arr, vm_value_create_int(30));
    
    int result = array_delete(arr, 1);
    
    test_assert(result == 0, "Delete should succeed");
    test_assert(array_length(arr) == 2, "Length should be 2");
    test_assert(array_get(arr, 0).data.int_value == 10, "Element 0 should be 10");
    test_assert(array_get(arr, 1).data.int_value == 30, "Element 1 should be 30");
    
    array_free(arr);
    gc_free(gc);
}

void test_array_delete_out_of_bounds(void) {
    test_setup("Delete with out-of-bounds index");
    
    GC *gc = gc_init();
    array_t *arr = array_new(gc, 5);
    
    array_push(arr, vm_value_create_int(1));
    
    int result = array_delete(arr, 10);
    
    test_assert(result == -1, "Delete out-of-bounds should fail");
    test_assert(array_length(arr) == 1, "Length should remain 1");
    
    array_free(arr);
    gc_free(gc);
}

/* ========== TESTS: Clone Operations ========== */

void test_array_clone(void) {
    test_setup("Clone array");
    
    GC *gc = gc_init();
    array_t *arr = array_new(gc, 5);
    
    array_push(arr, vm_value_create_int(1));
    array_push(arr, vm_value_create_int(2));
    array_push(arr, vm_value_create_int(3));
    
    array_t *clone = array_clone(arr, gc);
    
    test_assert(clone != NULL, "Clone should be created");
    test_assert(clone != arr, "Clone should be different object");
    test_assert(array_length(clone) == 3, "Clone should have same length");
    test_assert(array_get(clone, 0).data.int_value == 1, "Clone element 0 should be 1");
    test_assert(array_get(clone, 1).data.int_value == 2, "Clone element 1 should be 2");
    test_assert(array_get(clone, 2).data.int_value == 3, "Clone element 2 should be 3");
    
    array_free(clone);
    array_free(arr);
    gc_free(gc);
}

void test_array_clone_empty(void) {
    test_setup("Clone empty array");
    
    GC *gc = gc_init();
    array_t *arr = array_new(gc, 5);
    
    array_t *clone = array_clone(arr, gc);
    
    test_assert(clone != NULL, "Clone of empty array should be created");
    test_assert(array_length(clone) == 0, "Clone should be empty");
    
    array_free(clone);
    array_free(arr);
    gc_free(gc);
}

void test_array_clone_independence(void) {
    test_setup("Clone independence (modification)");
    
    GC *gc = gc_init();
    array_t *arr = array_new(gc, 5);
    
    array_push(arr, vm_value_create_int(100));
    
    array_t *clone = array_clone(arr, gc);
    
    array_set(arr, 0, vm_value_create_int(999));
    
    test_assert(array_get(arr, 0).data.int_value == 999, "Original should be modified");
    test_assert(array_get(clone, 0).data.int_value == 100, "Clone should be unchanged");
    
    array_free(clone);
    array_free(arr);
    gc_free(gc);
}

/* ========== TESTS: Edge Cases ========== */

void test_array_mixed_types(void) {
    test_setup("Array with mixed value types");
    
    GC *gc = gc_init();
    array_t *arr = array_new(gc, 5);
    
    array_push(arr, vm_value_create_int(42));
    array_push(arr, vm_value_create_float(3.14));
    array_push(arr, vm_value_create_string("hello"));
    array_push(arr, vm_value_create_null());
    
    test_assert(array_length(arr) == 4, "Should have 4 elements");
    test_assert(array_get(arr, 0).type == VALUE_INT, "Element 0 should be INT");
    test_assert(array_get(arr, 1).type == VALUE_FLOAT, "Element 1 should be FLOAT");
    test_assert(array_get(arr, 2).type == VALUE_STRING, "Element 2 should be STRING");
    test_assert(array_get(arr, 3).type == VALUE_NULL, "Element 3 should be NULL");
    
    array_free(arr);
    gc_free(gc);
}

void test_array_length(void) {
    test_setup("Array length tracking");
    
    GC *gc = gc_init();
    array_t *arr = array_new(gc, 5);
    
    test_assert(array_length(arr) == 0, "Initial length 0");
    
    array_push(arr, vm_value_create_int(1));
    test_assert(array_length(arr) == 1, "Length 1 after push");
    
    array_push(arr, vm_value_create_int(2));
    test_assert(array_length(arr) == 2, "Length 2 after push");
    
    VMValue v;
    array_pop(arr, &v);
    test_assert(array_length(arr) == 1, "Length 1 after pop");
    
    array_free(arr);
    gc_free(gc);
}

void test_array_null_handling(void) {
    test_setup("Array operations with NULL");
    
    test_assert(array_length(NULL) == 0, "Length of NULL array should be 0");
    test_assert(array_push(NULL, vm_value_create_int(1)) == -1, "Push to NULL should fail");
    test_assert(array_clone(NULL, NULL) == NULL, "Clone NULL should return NULL");
    
    array_free(NULL);  /* Should not crash */
    test_assert(1, "Free NULL should not crash");
}

/* ========== TESTS: GC Integration ========== */

void test_array_gc_allocation(void) {
    test_setup("Array GC allocation tracking");
    
    GC *gc = gc_init();
    size_t before = gc->total_allocated;
    
    array_t *arr = array_new(gc, 10);
    
    test_assert(gc->total_allocated > before, "GC should track allocation");
    
    array_free(arr);
    
    test_assert(gc->total_freed > 0, "GC should track deallocation");
    
    gc_free(gc);
}

void test_array_multiple_gc_arrays(void) {
    test_setup("Multiple arrays with same GC");
    
    GC *gc = gc_init();
    
    array_t *arr1 = array_new(gc, 5);
    array_t *arr2 = array_new(gc, 5);
    array_t *arr3 = array_new(gc, 5);
    
    array_push(arr1, vm_value_create_int(1));
    array_push(arr2, vm_value_create_int(2));
    array_push(arr3, vm_value_create_int(3));
    
    test_assert(array_get(arr1, 0).data.int_value == 1, "Array 1 should be independent");
    test_assert(array_get(arr2, 0).data.int_value == 2, "Array 2 should be independent");
    test_assert(array_get(arr3, 0).data.int_value == 3, "Array 3 should be independent");
    
    array_free(arr1);
    array_free(arr2);
    array_free(arr3);
    gc_free(gc);
}

/* ========== Main Test Runner ========== */

int main(void) {
    printf("\n========================================\n");
    printf("AMLP Array Module - Test Suite\n");
    printf("========================================\n");
    
    /* Array Creation Tests */
    test_array_new();
    test_array_new_zero_capacity();
    test_array_new_no_gc();
    
    /* Push/Pop Tests */
    test_array_push();
    test_array_pop();
    test_array_pop_empty();
    test_array_push_resize();
    
    /* Get/Set Tests */
    test_array_get();
    test_array_get_out_of_bounds();
    test_array_set();
    test_array_set_out_of_bounds();
    
    /* Insert/Delete Tests */
    test_array_insert();
    test_array_insert_at_end();
    test_array_delete();
    test_array_delete_out_of_bounds();
    
    /* Clone Tests */
    test_array_clone();
    test_array_clone_empty();
    test_array_clone_independence();
    
    /* Edge Cases */
    test_array_mixed_types();
    test_array_length();
    test_array_null_handling();
    
    /* GC Integration Tests */
    test_array_gc_allocation();
    test_array_multiple_gc_arrays();
    
    /* Summary */
    printf("\n========================================\n");
    printf("Test Results: %d/%d passed", test_passed, test_count);
    if (test_failed > 0) {
        printf(" (%d failed)", test_failed);
    }
    printf("\n========================================\n\n");
    
    return (test_failed == 0) ? 0 : 1;
}

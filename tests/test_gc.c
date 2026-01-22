/**
 * test_gc.c - Garbage Collector Test Suite
 * 
 * Comprehensive tests for the garbage collection system.
 * 
 * Phase 5 - January 22, 2026
 */

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

/* ========== TESTS: GC Initialization ========== */

void test_gc_init(void) {
    test_setup("Initialize garbage collector");
    
    GC *gc = gc_init();
    
    test_assert(gc != NULL, "GC should be initialized");
    test_assert(gc->object_count == 0, "Initial object count should be 0");
    test_assert(gc->total_allocated == 0, "Initial allocated bytes should be 0");
    
    gc_free(gc);
}

void test_gc_alloc_basic(void) {
    test_setup("Allocate memory with GC");
    
    GC *gc = gc_init();
    
    void *ptr = gc_alloc(gc, 100, GC_TYPE_GENERIC);
    
    test_assert(ptr != NULL, "Allocation should succeed");
    test_assert(gc->object_count == 1, "Should track 1 object");
    test_assert(gc_is_tracked(gc, ptr), "Pointer should be tracked");
    
    gc_free(gc);
}

void test_gc_track_existing(void) {
    test_setup("Track existing pointer");
    
    GC *gc = gc_init();
    void *ptr = malloc(50);
    
    GCObject *obj = gc_track(gc, ptr, 50, GC_TYPE_STRING);
    
    test_assert(obj != NULL, "Tracking should succeed");
    test_assert(obj->ref_count == 1, "Initial ref count should be 1");
    test_assert(gc->object_count == 1, "Should track 1 object");
    
    gc_free(gc);
}

/* ========== TESTS: Reference Counting ========== */

void test_gc_retain(void) {
    test_setup("Retain increases reference count");
    
    GC *gc = gc_init();
    void *ptr = gc_alloc(gc, 100, GC_TYPE_GENERIC);
    
    int ref1 = gc_retain(gc, ptr);
    int ref2 = gc_retain(gc, ptr);
    
    test_assert(ref1 == 2, "First retain should return 2");
    test_assert(ref2 == 3, "Second retain should return 3");
    test_assert(gc_get_ref_count(gc, ptr) == 3, "Final ref count should be 3");
    
    gc_free(gc);
}

void test_gc_release(void) {
    test_setup("Release decreases reference count");
    
    GC *gc = gc_init();
    void *ptr = gc_alloc(gc, 100, GC_TYPE_GENERIC);
    
    gc_retain(gc, ptr);  /* ref_count = 2 */
    gc_retain(gc, ptr);  /* ref_count = 3 */
    
    int ref1 = gc_release(gc, ptr);  /* ref_count = 2 */
    int ref2 = gc_release(gc, ptr);  /* ref_count = 1 */
    
    test_assert(ref1 == 2, "First release should return 2");
    test_assert(ref2 == 1, "Second release should return 1");
    test_assert(gc->object_count == 1, "Object should still exist");
    
    gc_free(gc);
}

void test_gc_release_frees(void) {
    test_setup("Release frees when ref count reaches 0");
    
    GC *gc = gc_init();
    void *ptr = gc_alloc(gc, 100, GC_TYPE_GENERIC);
    
    int initial_count = gc->object_count;
    int result = gc_release(gc, ptr);
    
    test_assert(result == -1, "Release should return -1 when freed");
    test_assert(gc->object_count == initial_count - 1, "Object should be removed");
    test_assert(!gc_is_tracked(gc, ptr), "Pointer should no longer be tracked");
    
    gc_free(gc);
}

void test_gc_multiple_objects(void) {
    test_setup("Track multiple objects");
    
    GC *gc = gc_init();
    
    void *ptr1 = gc_alloc(gc, 100, GC_TYPE_GENERIC);
    void *ptr2 = gc_alloc(gc, 200, GC_TYPE_STRING);
    void *ptr3 = gc_alloc(gc, 300, GC_TYPE_ARRAY);
    
    test_assert(gc->object_count == 3, "Should track 3 objects");
    test_assert(gc_is_tracked(gc, ptr1), "ptr1 should be tracked");
    test_assert(gc_is_tracked(gc, ptr2), "ptr2 should be tracked");
    test_assert(gc_is_tracked(gc, ptr3), "ptr3 should be tracked");
    
    gc_free(gc);
}

/* ========== TESTS: Collection ========== */

void test_gc_collect_basic(void) {
    test_setup("Basic garbage collection");
    
    GC *gc = gc_init();
    
    void *ptr1 = gc_alloc(gc, 100, GC_TYPE_GENERIC);
    void *ptr2 = gc_alloc(gc, 200, GC_TYPE_GENERIC);
    
    /* Release both to ref_count 0 */
    gc_release(gc, ptr1);
    gc_release(gc, ptr2);
    
    test_assert(gc->object_count == 0, "Both objects should be freed immediately");
    
    gc_free(gc);
}

void test_gc_collect_partial(void) {
    test_setup("Collect only zero-ref objects");
    
    GC *gc = gc_init();
    gc_set_auto_collect(gc, 0);  /* Disable auto-collect */
    
    void *ptr1 = gc_alloc(gc, 100, GC_TYPE_GENERIC);
    void *ptr2 = gc_alloc(gc, 200, GC_TYPE_GENERIC);
    void *ptr3 = gc_alloc(gc, 300, GC_TYPE_GENERIC);
    
    /* Keep ptr2 alive, set others to 0 */
    gc_set_ref_count(gc, ptr1, 0);
    gc_set_ref_count(gc, ptr3, 0);
    
    int freed = gc_collect(gc);
    
    test_assert(freed == 2, "Should free 2 objects");
    test_assert(gc->object_count == 1, "Should have 1 object remaining");
    test_assert(gc_is_tracked(gc, ptr2), "ptr2 should still be tracked");
    
    gc_free(gc);
}

void test_gc_collect_full(void) {
    test_setup("Full collection with mark-sweep");
    
    GC *gc = gc_init();
    gc_set_auto_collect(gc, 0);
    
    void *ptr1 = gc_alloc(gc, 100, GC_TYPE_GENERIC);
    void *ptr2 = gc_alloc(gc, 200, GC_TYPE_GENERIC);
    
    /* Set both to ref_count 0 */
    gc_set_ref_count(gc, ptr1, 0);
    gc_set_ref_count(gc, ptr2, 0);
    
    int freed = gc_collect_full(gc);
    
    test_assert(freed == 2, "Full collect should free both");
    test_assert(gc->object_count == 0, "All objects should be freed");
    
    gc_free(gc);
}

void test_gc_auto_collect(void) {
    test_setup("Auto-collect at threshold");
    
    GC *gc = gc_init();
    gc_set_collect_threshold(gc, 5);
    gc_set_auto_collect(gc, 1);
    
    /* Allocate and immediately release objects */
    for (int i = 0; i < 10; i++) {
        void *ptr = gc_alloc(gc, 100, GC_TYPE_GENERIC);
        gc_release(gc, ptr);
    }
    
    test_assert(gc->collection_count > 0, "Should have triggered auto-collect");
    test_assert(gc->object_count == 0, "All objects should be freed");
    
    gc_free(gc);
}

/* ========== TESTS: Statistics ========== */

void test_gc_get_allocated_bytes(void) {
    test_setup("Get currently allocated bytes");
    
    GC *gc = gc_init();
    
    void *ptr1 = gc_alloc(gc, 100, GC_TYPE_GENERIC);
    void *ptr2 = gc_alloc(gc, 200, GC_TYPE_GENERIC);
    (void)ptr2;  /* Used indirectly via allocated bytes */
    
    size_t allocated = gc_get_allocated_bytes(gc);
    
    test_assert(allocated == 300, "Should have 300 bytes allocated");
    
    gc_release(gc, ptr1);
    allocated = gc_get_allocated_bytes(gc);
    
    test_assert(allocated == 200, "Should have 200 bytes after freeing ptr1");
    
    gc_free(gc);
}

void test_gc_get_object_count(void) {
    test_setup("Get tracked object count");
    
    GC *gc = gc_init();
    
    test_assert(gc_get_object_count(gc) == 0, "Initial count should be 0");
    
    gc_alloc(gc, 100, GC_TYPE_GENERIC);
    test_assert(gc_get_object_count(gc) == 1, "Count should be 1");
    
    gc_alloc(gc, 200, GC_TYPE_GENERIC);
    test_assert(gc_get_object_count(gc) == 2, "Count should be 2");
    
    gc_free(gc);
}

void test_gc_find_leaks(void) {
    test_setup("Detect memory leaks");
    
    GC *gc = gc_init();
    gc_set_auto_collect(gc, 0);
    
    /* Create objects with positive ref counts (potential leaks) */
    gc_alloc(gc, 100, GC_TYPE_GENERIC);
    gc_alloc(gc, 200, GC_TYPE_STRING);
    
    int leaks = gc_find_leaks(gc);
    
    test_assert(leaks == 2, "Should detect 2 potential leaks");
    
    gc_free(gc);
}

/* ========== TESTS: Configuration ========== */

void test_gc_set_auto_collect(void) {
    test_setup("Configure auto-collect");
    
    GC *gc = gc_init();
    
    test_assert(gc->auto_collect_enabled == 1, "Auto-collect enabled by default");
    
    gc_set_auto_collect(gc, 0);
    test_assert(gc->auto_collect_enabled == 0, "Should disable auto-collect");
    
    gc_set_auto_collect(gc, 1);
    test_assert(gc->auto_collect_enabled == 1, "Should enable auto-collect");
    
    gc_free(gc);
}

void test_gc_set_threshold(void) {
    test_setup("Configure collection threshold");
    
    GC *gc = gc_init();
    
    gc_set_collect_threshold(gc, 500);
    test_assert(gc->collect_threshold == 500, "Should set threshold to 500");
    
    gc_set_collect_threshold(gc, -10);  /* Invalid */
    test_assert(gc->collect_threshold == 500, "Should ignore invalid threshold");
    
    gc_free(gc);
}

/* ========== TESTS: Object Types ========== */

void test_gc_type_object(void) {
    test_setup("Track GC_TYPE_OBJECT");
    
    GC *gc = gc_init();
    void *ptr = gc_alloc(gc, 100, GC_TYPE_OBJECT);
    
    GCObject *obj = gc_find_object(gc, ptr);
    
    test_assert(obj != NULL, "Object should be found");
    test_assert(obj->type == GC_TYPE_OBJECT, "Type should be OBJECT");
    
    gc_free(gc);
}

void test_gc_type_array(void) {
    test_setup("Track GC_TYPE_ARRAY");
    
    GC *gc = gc_init();
    void *ptr = gc_alloc(gc, 100, GC_TYPE_ARRAY);
    
    GCObject *obj = gc_find_object(gc, ptr);
    
    test_assert(obj->type == GC_TYPE_ARRAY, "Type should be ARRAY");
    
    gc_free(gc);
}

void test_gc_type_mapping(void) {
    test_setup("Track GC_TYPE_MAPPING");
    
    GC *gc = gc_init();
    void *ptr = gc_alloc(gc, 100, GC_TYPE_MAPPING);
    
    GCObject *obj = gc_find_object(gc, ptr);
    
    test_assert(obj->type == GC_TYPE_MAPPING, "Type should be MAPPING");
    
    gc_free(gc);
}

void test_gc_type_string(void) {
    test_setup("Track GC_TYPE_STRING");
    
    GC *gc = gc_init();
    void *ptr = gc_alloc(gc, 100, GC_TYPE_STRING);
    
    GCObject *obj = gc_find_object(gc, ptr);
    
    test_assert(obj->type == GC_TYPE_STRING, "Type should be STRING");
    
    gc_free(gc);
}

/* ========== TESTS: Edge Cases ========== */

void test_gc_double_release(void) {
    test_setup("Double release is safe");
    
    GC *gc = gc_init();
    void *ptr = gc_alloc(gc, 100, GC_TYPE_GENERIC);
    
    gc_release(gc, ptr);  /* Frees object */
    int result = gc_release(gc, ptr);  /* Should return -1 (not found) */
    
    test_assert(result == -1, "Second release should return -1");
    
    gc_free(gc);
}

void test_gc_null_pointer(void) {
    test_setup("NULL pointer operations are safe");
    
    GC *gc = gc_init();
    
    void *ptr = gc_alloc(gc, 0, GC_TYPE_GENERIC);
    test_assert(ptr == NULL, "Alloc with size 0 should return NULL");
    
    int result = gc_retain(gc, NULL);
    test_assert(result == -1, "Retain NULL should return -1");
    
    result = gc_release(gc, NULL);
    test_assert(result == -1, "Release NULL should return -1");
    
    gc_free(gc);
}

void test_gc_find_nonexistent(void) {
    test_setup("Find non-existent pointer");
    
    GC *gc = gc_init();
    void *fake_ptr = (void *)0x1234;
    
    GCObject *obj = gc_find_object(gc, fake_ptr);
    
    test_assert(obj == NULL, "Should not find non-existent pointer");
    test_assert(!gc_is_tracked(gc, fake_ptr), "Fake pointer should not be tracked");
    
    gc_free(gc);
}

/* ========== Main Test Runner ========== */

int main(void) {
    printf("\n========================================\n");
    printf("AMLP Garbage Collector - Test Suite\n");
    printf("========================================\n");
    
    /* GC Initialization Tests */
    test_gc_init();
    test_gc_alloc_basic();
    test_gc_track_existing();
    
    /* Reference Counting Tests */
    test_gc_retain();
    test_gc_release();
    test_gc_release_frees();
    test_gc_multiple_objects();
    
    /* Collection Tests */
    test_gc_collect_basic();
    test_gc_collect_partial();
    test_gc_collect_full();
    test_gc_auto_collect();
    
    /* Statistics Tests */
    test_gc_get_allocated_bytes();
    test_gc_get_object_count();
    test_gc_find_leaks();
    
    /* Configuration Tests */
    test_gc_set_auto_collect();
    test_gc_set_threshold();
    
    /* Object Type Tests */
    test_gc_type_object();
    test_gc_type_array();
    test_gc_type_mapping();
    test_gc_type_string();
    
    /* Edge Case Tests */
    test_gc_double_release();
    test_gc_null_pointer();
    test_gc_find_nonexistent();
    
    /* Summary */
    printf("\n========================================\n");
    printf("Test Results: %d/%d passed", test_passed, test_count);
    if (test_failed > 0) {
        printf(" (%d failed)", test_failed);
    }
    printf("\n========================================\n\n");
    
    return (test_failed == 0) ? 0 : 1;
}

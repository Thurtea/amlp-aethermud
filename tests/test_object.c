/**
 * test_object.c - Object System Test Suite
 * 
 * Comprehensive tests for the LPC object system:
 * - Object creation and lifecycle
 * - Property get/set/delete
 * - Method management
 * - Inheritance (prototype chain)
 * - Object manager
 * 
 * Phase 4 - January 22, 2026
 */

#include "object.h"
#include "vm.h"
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

/* ========== TESTS: Object Lifecycle ========== */

void test_create_object(void) {
    test_setup("Create a new object");
    
    obj_t *obj = obj_new("test_object");
    
    test_assert(obj != NULL, "Object should be created");
    test_assert(strcmp(obj->name, "test_object") == 0, "Object name should match");
    test_assert(obj->proto == NULL, "Object should have no prototype");
    test_assert(obj->property_count == 0, "Object should have no properties");
    test_assert(obj->method_count == 0, "Object should have no methods");
    test_assert(obj->is_destroyed == 0, "Object should not be destroyed");
    
    obj_free(obj);
}

void test_clone_object(void) {
    test_setup("Clone an existing object");
    
    obj_t *original = obj_new("original");
    obj_set_prop(original, "x", vm_value_create_int(42));
    
    obj_t *clone = obj_clone(original);
    
    test_assert(clone != NULL, "Clone should be created");
    test_assert(clone->proto == original, "Clone should have original as prototype");
    test_assert(original->ref_count == 2, "Original ref count should be 2");
    
    /* Clone should inherit property */
    VMValue val = obj_get_prop(clone, "x");
    test_assert(val.type == VALUE_INT && val.data.int_value == 42, 
                "Clone should inherit property from original");
    
    obj_free(clone);
    obj_free(original);
}

void test_destroy_object(void) {
    test_setup("Destroy an object");
    
    obj_t *obj = obj_new("destroy_test");
    obj_destroy(obj);
    
    test_assert(obj->is_destroyed == 1, "Object should be marked as destroyed");
    
    obj_free(obj);
}

/* ========== TESTS: Property Operations ========== */

void test_set_property_int(void) {
    test_setup("Set integer property");
    
    obj_t *obj = obj_new("prop_test");
    int result = obj_set_prop(obj, "health", vm_value_create_int(100));
    
    test_assert(result == 0, "Set property should succeed");
    test_assert(obj->property_count == 1, "Object should have 1 property");
    
    obj_free(obj);
}

void test_get_property_int(void) {
    test_setup("Get integer property");
    
    obj_t *obj = obj_new("prop_test");
    obj_set_prop(obj, "health", vm_value_create_int(100));
    
    VMValue val = obj_get_prop(obj, "health");
    
    test_assert(val.type == VALUE_INT, "Property should be int type");
    test_assert(val.data.int_value == 100, "Property value should be 100");
    
    obj_free(obj);
}

void test_set_property_string(void) {
    test_setup("Set string property");
    
    obj_t *obj = obj_new("prop_test");
    obj_set_prop(obj, "name", vm_value_create_string("Alice"));
    
    VMValue val = obj_get_prop(obj, "name");
    
    test_assert(val.type == VALUE_STRING, "Property should be string type");
    test_assert(strcmp(val.data.string_value, "Alice") == 0, 
                "Property value should be 'Alice'");
    
    obj_free(obj);
}

void test_set_property_float(void) {
    test_setup("Set float property");
    
    obj_t *obj = obj_new("prop_test");
    obj_set_prop(obj, "speed", vm_value_create_float(3.14));
    
    VMValue val = obj_get_prop(obj, "speed");
    
    test_assert(val.type == VALUE_FLOAT, "Property should be float type");
    test_assert(val.data.float_value > 3.13 && val.data.float_value < 3.15, 
                "Property value should be ~3.14");
    
    obj_free(obj);
}

void test_update_property(void) {
    test_setup("Update existing property");
    
    obj_t *obj = obj_new("prop_test");
    obj_set_prop(obj, "value", vm_value_create_int(10));
    obj_set_prop(obj, "value", vm_value_create_int(20));
    
    VMValue val = obj_get_prop(obj, "value");
    
    test_assert(val.data.int_value == 20, "Property should be updated to 20");
    test_assert(obj->property_count == 1, "Should still have only 1 property");
    
    obj_free(obj);
}

void test_multiple_properties(void) {
    test_setup("Set multiple properties");
    
    obj_t *obj = obj_new("prop_test");
    obj_set_prop(obj, "health", vm_value_create_int(100));
    obj_set_prop(obj, "mana", vm_value_create_int(50));
    obj_set_prop(obj, "name", vm_value_create_string("Bob"));
    
    test_assert(obj->property_count == 3, "Object should have 3 properties");
    
    VMValue h = obj_get_prop(obj, "health");
    VMValue m = obj_get_prop(obj, "mana");
    VMValue n = obj_get_prop(obj, "name");
    
    test_assert(h.data.int_value == 100, "Health should be 100");
    test_assert(m.data.int_value == 50, "Mana should be 50");
    test_assert(strcmp(n.data.string_value, "Bob") == 0, "Name should be Bob");
    
    obj_free(obj);
}

void test_get_nonexistent_property(void) {
    test_setup("Get non-existent property returns null");
    
    obj_t *obj = obj_new("prop_test");
    VMValue val = obj_get_prop(obj, "nonexistent");
    
    test_assert(val.type == VALUE_NULL, "Non-existent property should return null");
    
    obj_free(obj);
}

void test_has_property(void) {
    test_setup("Check if property exists");
    
    obj_t *obj = obj_new("prop_test");
    obj_set_prop(obj, "exists", vm_value_create_int(1));
    
    test_assert(obj_has_prop(obj, "exists") == 1, "Property 'exists' should exist");
    test_assert(obj_has_prop(obj, "not_exists") == 0, "Property 'not_exists' should not exist");
    
    obj_free(obj);
}

void test_delete_property(void) {
    test_setup("Delete a property");
    
    obj_t *obj = obj_new("prop_test");
    obj_set_prop(obj, "temp", vm_value_create_int(42));
    
    int result = obj_delete_prop(obj, "temp");
    
    test_assert(result == 0, "Delete should succeed");
    test_assert(obj->property_count == 0, "Object should have 0 properties");
    test_assert(obj_has_prop(obj, "temp") == 0, "Property should no longer exist");
    
    obj_free(obj);
}

/* ========== TESTS: Inheritance ========== */

void test_inherit_property(void) {
    test_setup("Inherit property from prototype");
    
    obj_t *parent = obj_new("parent");
    obj_set_prop(parent, "inherited", vm_value_create_int(99));
    
    obj_t *child = obj_new("child");
    obj_set_proto(child, parent);
    
    VMValue val = obj_get_prop(child, "inherited");
    
    test_assert(val.type == VALUE_INT && val.data.int_value == 99, 
                "Child should inherit property from parent");
    
    obj_free(child);
    obj_free(parent);
}

void test_override_property(void) {
    test_setup("Override inherited property");
    
    obj_t *parent = obj_new("parent");
    obj_set_prop(parent, "value", vm_value_create_int(10));
    
    obj_t *child = obj_new("child");
    obj_set_proto(child, parent);
    obj_set_prop(child, "value", vm_value_create_int(20));
    
    VMValue child_val = obj_get_prop(child, "value");
    VMValue parent_val = obj_get_prop(parent, "value");
    
    test_assert(child_val.data.int_value == 20, "Child should have overridden value");
    test_assert(parent_val.data.int_value == 10, "Parent value should be unchanged");
    
    obj_free(child);
    obj_free(parent);
}

void test_prototype_chain(void) {
    test_setup("Multi-level prototype chain");
    
    obj_t *grandparent = obj_new("grandparent");
    obj_set_prop(grandparent, "level", vm_value_create_int(0));
    
    obj_t *parent = obj_new("parent");
    obj_set_proto(parent, grandparent);
    obj_set_prop(parent, "level", vm_value_create_int(1));
    
    obj_t *child = obj_new("child");
    obj_set_proto(child, parent);
    obj_set_prop(child, "level", vm_value_create_int(2));
    
    /* Each should have its own value */
    test_assert(obj_get_prop(child, "level").data.int_value == 2, "Child level should be 2");
    test_assert(obj_get_prop(parent, "level").data.int_value == 1, "Parent level should be 1");
    test_assert(obj_get_prop(grandparent, "level").data.int_value == 0, "Grandparent level should be 0");
    
    obj_free(child);
    obj_free(parent);
    obj_free(grandparent);
}

/* ========== TESTS: Method Management ========== */

void test_add_method(void) {
    test_setup("Add method to object");
    
    obj_t *obj = obj_new("method_test");
    VMFunction *method = vm_function_create("test_method", 0, 0);
    
    int idx = obj_add_method(obj, method);
    
    test_assert(idx == 0, "First method index should be 0");
    test_assert(obj->method_count == 1, "Object should have 1 method");
    
    obj_free(obj);
    vm_function_free(method);
}

void test_get_method(void) {
    test_setup("Get method by name");
    
    obj_t *obj = obj_new("method_test");
    VMFunction *method = vm_function_create("my_method", 2, 0);
    obj_add_method(obj, method);
    
    VMFunction *found = obj_get_method(obj, "my_method");
    
    test_assert(found != NULL, "Method should be found");
    test_assert(found == method, "Should return same method pointer");
    test_assert(strcmp(found->name, "my_method") == 0, "Method name should match");
    
    obj_free(obj);
    vm_function_free(method);
}

void test_inherit_method(void) {
    test_setup("Inherit method from prototype");
    
    obj_t *parent = obj_new("parent");
    VMFunction *parent_method = vm_function_create("inherited_method", 0, 0);
    obj_add_method(parent, parent_method);
    
    obj_t *child = obj_new("child");
    obj_set_proto(child, parent);
    
    VMFunction *found = obj_get_method(child, "inherited_method");
    
    test_assert(found != NULL, "Child should find inherited method");
    test_assert(found == parent_method, "Should be same method from parent");
    
    obj_free(child);
    obj_free(parent);
    vm_function_free(parent_method);
}

/* ========== TESTS: Object Manager ========== */

void test_manager_init(void) {
    test_setup("Initialize object manager");
    
    ObjManager *mgr = obj_manager_init();
    
    test_assert(mgr != NULL, "Manager should be created");
    test_assert(mgr->object_count == 0, "Manager should have 0 objects");
    
    obj_manager_free(mgr);
}

void test_manager_register(void) {
    test_setup("Register object with manager");
    
    ObjManager *mgr = obj_manager_init();
    obj_t *obj = obj_new("managed");
    
    int result = obj_manager_register(mgr, obj);
    
    test_assert(result == 0, "Register should succeed");
    test_assert(mgr->object_count == 1, "Manager should have 1 object");
    
    obj_manager_free(mgr);
}

void test_manager_find(void) {
    test_setup("Find object by name");
    
    ObjManager *mgr = obj_manager_init();
    obj_t *obj1 = obj_new("first");
    obj_t *obj2 = obj_new("second");
    
    obj_manager_register(mgr, obj1);
    obj_manager_register(mgr, obj2);
    
    obj_t *found = obj_manager_find(mgr, "second");
    
    test_assert(found != NULL, "Should find object");
    test_assert(found == obj2, "Should return correct object");
    test_assert(strcmp(found->name, "second") == 0, "Object name should match");
    
    obj_manager_free(mgr);
}

void test_manager_unregister(void) {
    test_setup("Unregister object from manager");
    
    ObjManager *mgr = obj_manager_init();
    obj_t *obj = obj_new("temporary");
    
    obj_manager_register(mgr, obj);
    int result = obj_manager_unregister(mgr, obj);
    
    test_assert(result == 0, "Unregister should succeed");
    test_assert(mgr->object_count == 0, "Manager should have 0 objects");
    
    obj_free(obj);
    obj_manager_free(mgr);
}

/* ========== TESTS: Utility Functions ========== */

void test_property_count(void) {
    test_setup("Get total property count including inherited");
    
    obj_t *parent = obj_new("parent");
    obj_set_prop(parent, "p1", vm_value_create_int(1));
    obj_set_prop(parent, "p2", vm_value_create_int(2));
    
    obj_t *child = obj_new("child");
    obj_set_proto(child, parent);
    obj_set_prop(child, "c1", vm_value_create_int(3));
    
    int count = obj_get_property_count(child);
    
    test_assert(count == 3, "Total property count should be 3 (2 inherited + 1 own)");
    
    obj_free(child);
    obj_free(parent);
}

void test_method_count(void) {
    test_setup("Get total method count including inherited");
    
    obj_t *parent = obj_new("parent");
    VMFunction *m1 = vm_function_create("m1", 0, 0);
    VMFunction *m2 = vm_function_create("m2", 0, 0);
    obj_add_method(parent, m1);
    obj_add_method(parent, m2);
    
    obj_t *child = obj_new("child");
    obj_set_proto(child, parent);
    VMFunction *m3 = vm_function_create("m3", 0, 0);
    obj_add_method(child, m3);
    
    int count = obj_get_method_count(child);
    
    test_assert(count == 3, "Total method count should be 3 (2 inherited + 1 own)");
    
    obj_free(child);
    obj_free(parent);
    vm_function_free(m1);
    vm_function_free(m2);
    vm_function_free(m3);
}

/* ========== Main Test Runner ========== */

int main(void) {
    printf("\n========================================\n");
    printf("AMLP Object System - Test Suite\n");
    printf("========================================\n");
    
    /* Object Lifecycle Tests */
    test_create_object();
    test_clone_object();
    test_destroy_object();
    
    /* Property Operation Tests */
    test_set_property_int();
    test_get_property_int();
    test_set_property_string();
    test_set_property_float();
    test_update_property();
    test_multiple_properties();
    test_get_nonexistent_property();
    test_has_property();
    test_delete_property();
    
    /* Inheritance Tests */
    test_inherit_property();
    test_override_property();
    test_prototype_chain();
    
    /* Method Management Tests */
    test_add_method();
    test_get_method();
    test_inherit_method();
    
    /* Object Manager Tests */
    test_manager_init();
    test_manager_register();
    test_manager_find();
    test_manager_unregister();
    
    /* Utility Tests */
    test_property_count();
    test_method_count();
    
    /* Summary */
    printf("\n========================================\n");
    printf("Test Results: %d/%d passed", test_passed, test_count);
    if (test_failed > 0) {
        printf(" (%d failed)", test_failed);
    }
    printf("\n========================================\n\n");
    
    return (test_failed == 0) ? 0 : 1;
}

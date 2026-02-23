/*
 * test_password.c - Password hashing tests
 *
 * Verifies that hash_password() produces a valid bcrypt hash and that
 * verify_password() correctly accepts matching and rejects non-matching
 * plaintexts.
 */

#include <stdio.h>
#include <string.h>
#include "password.h"

static int tests_run    = 0;
static int tests_passed = 0;
static int tests_failed = 0;

#define PASS(msg) do { printf("  [PASS] %s\n", msg); tests_passed++; tests_run++; } while(0)
#define FAIL(msg) do { printf("  [FAIL] %s\n", msg); tests_failed++; tests_run++; } while(0)
#define CHECK(cond, msg) do { if (cond) PASS(msg); else FAIL(msg); } while(0)

int main(void) {
    printf("=== Password hashing tests ===\n\n");

    /* --- Test 1: hash produces a bcrypt header ---------------------- */
    printf("[Test 1] hash_password produces $2b$10$ prefix\n");
    {
        const char *h = hash_password("hunter2");
        CHECK(h != NULL,                             "hash is non-NULL");
        CHECK(strncmp(h, "$2b$10$", 7) == 0,         "hash starts with $2b$10$");
        CHECK(strlen(h) == 60,                        "hash length is 60 chars");
        printf("  hash: %.60s\n", h);
    }

    /* --- Test 2: verify accepts correct password -------------------- */
    printf("\n[Test 2] verify_password accepts correct password\n");
    {
        const char *h = hash_password("correct-horse-battery-staple");
        char stored[128];
        strncpy(stored, h, sizeof(stored) - 1);
        stored[sizeof(stored) - 1] = '\0';
        CHECK(verify_password("correct-horse-battery-staple", stored) == 1,
              "verify returns 1 for matching password");
    }

    /* --- Test 3: verify rejects wrong password ---------------------- */
    printf("\n[Test 3] verify_password rejects wrong password\n");
    {
        const char *h = hash_password("right-password");
        char stored[128];
        strncpy(stored, h, sizeof(stored) - 1);
        stored[sizeof(stored) - 1] = '\0';
        CHECK(verify_password("wrong-password", stored) == 0,
              "verify returns 0 for wrong password");
    }

    /* --- Test 4: two hashes of same password differ (unique salts) -- */
    printf("\n[Test 4] Two hashes of the same input differ (unique salts)\n");
    {
        const char *h1 = hash_password("samepassword");
        char first[128];
        strncpy(first, h1, sizeof(first) - 1);
        first[sizeof(first) - 1] = '\0';

        const char *h2 = hash_password("samepassword");
        CHECK(strcmp(first, h2) != 0, "two hashes of same input are different");
    }

    /* --- Test 5: NULL/empty edge cases ------------------------------ */
    printf("\n[Test 5] Edge cases\n");
    {
        CHECK(verify_password(NULL, "$2b$10$xxx") == 0,  "NULL plaintext → 0");
        CHECK(verify_password("x",  NULL)         == 0,  "NULL stored_hash → 0");
        CHECK(verify_password("x",  "")            == 0,  "empty stored_hash → 0");
        const char *h = hash_password(NULL);
        CHECK(h != NULL && h[0] == '\0',                 "hash_password(NULL) → empty string");
    }

    /* --- Summary ---------------------------------------------------- */
    printf("\n=== Results: %d/%d passed", tests_passed, tests_run);
    if (tests_failed == 0)
        printf(" — ALL PASS ===\n");
    else
        printf(", %d FAILED ===\n", tests_failed);

    return tests_failed > 0 ? 1 : 0;
}

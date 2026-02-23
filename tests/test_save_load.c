/*
 * test_save_load.c - Inventory persistence tests
 *
 * Tests inventory_write_to_file() and inventory_read_from_file() from item.c.
 * These are the functions called by save_character() and load_character() to
 * serialise and restore the player's inventory across sessions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "item.h"

/* ---- stubs for symbols needed by item.c in unit tests ---- */
int resolve_lpc_path(const char *args, char *out, size_t sz) {
    (void)args; (void)out; (void)sz;
    return 0;
}
Item *item_create_from_lpc(const char *path) {
    (void)path;
    return NULL;
}
void send_to_player(void *sess, const char *fmt, ...) {
    (void)sess; (void)fmt;
}
void room_broadcast(void *room, const char *msg, void *exclude) {
    (void)room; (void)msg; (void)exclude;
}
void format_item_name(const char *in, char *out, size_t sz) {
    if (in && out && sz > 0) { strncpy(out, in, sz - 1); out[sz-1] = '\0'; }
}
/* ---- end stubs ---- */

/* ---- test harness ---- */
static int tests_run    = 0;
static int tests_passed = 0;
static int tests_failed = 0;

#define CHECK(cond, msg) do {                                       \
    tests_run++;                                                    \
    if (cond) { printf("  [PASS] %s\n", msg); tests_passed++; }   \
    else       { printf("  [FAIL] %s\n", msg); tests_failed++; }  \
} while(0)

/* Write inventory to a tmp file, return freshly-opened FILE* at position 0. */
static FILE *round_trip_write(Inventory *inv, EquipmentSlots *eq) {
    FILE *f = tmpfile();
    if (!f) { perror("tmpfile"); exit(1); }
    inventory_write_to_file(inv, eq, f);
    rewind(f);
    return f;
}

int main(void) {
    item_init();

    printf("=== Inventory persistence tests ===\n\n");

    /* ---- Test 1: empty inventory round-trip ---- */
    printf("[Test 1] Empty inventory round-trip\n");
    {
        Inventory inv;  inventory_init(&inv, 10);
        EquipmentSlots eq; equipment_init(&eq);

        FILE *f = round_trip_write(&inv, &eq);

        Inventory loaded; inventory_init(&loaded, 10);
        EquipmentSlots leq; equipment_init(&leq);
        inventory_read_from_file(&loaded, &leq, f);
        fclose(f);

        CHECK(loaded.item_count == 0, "loaded item_count == 0 for empty inventory");
        CHECK(loaded.items == NULL,   "loaded items list is NULL");
        inventory_free(&loaded);
    }

    /* ---- Test 2: two C-template items round-trip ---- */
    printf("\n[Test 2] Two C-template items (one equipped) round-trip\n");
    {
        Inventory inv;  inventory_init(&inv, 30);
        EquipmentSlots eq; equipment_init(&eq);

        /* Pick two template IDs that are definitely in ITEM_TEMPLATES */
        Item *sword = item_create(0);   /* template 0 */
        Item *armor = item_create(20);  /* template 20 */

        if (!sword || !armor) {
            printf("  [SKIP] item_create returned NULL — template IDs may differ\n");
            if (sword) item_free(sword);
            if (armor) item_free(armor);
        } else {
            inventory_add(&inv, sword);
            inventory_add(&inv, armor);
            /* Equip the armor in slot 3 */
            armor->is_equipped = true;
            eq.armor = armor;

            int saved_sword_id = sword->id;
            int saved_armor_id = armor->id;

            FILE *f = round_trip_write(&inv, &eq);

            Inventory loaded; inventory_init(&loaded, 30);
            EquipmentSlots leq; equipment_init(&leq);
            inventory_read_from_file(&loaded, &leq, f);
            fclose(f);

            CHECK(loaded.item_count == 2, "loaded item_count == 2");

            /* Find the armor and sword by id */
            Item *la = NULL, *ls = NULL;
            Item *cur = loaded.items;
            while (cur) {
                if (cur->id == saved_armor_id) la = cur;
                if (cur->id == saved_sword_id) ls = cur;
                cur = cur->next;
            }
            CHECK(la != NULL, "armor item found after load");
            CHECK(ls != NULL, "sword item found after load");
            if (la) {
                CHECK(la->is_equipped == true,   "armor is_equipped == true");
                CHECK(leq.armor == la,            "armor wired into EquipmentSlots.armor");
            }
            if (ls) {
                CHECK(ls->is_equipped == false,  "sword is not equipped");
            }
            inventory_free(&loaded);
            inventory_free(&inv);
        }
    }

    /* ---- Test 3: LPC-sourced item saves sentinel, loads gracefully ---- */
    printf("\n[Test 3] LPC-sourced item writes -2 sentinel, loads gracefully (no VM)\n");
    {
        Inventory inv;  inventory_init(&inv, 10);
        EquipmentSlots eq; equipment_init(&eq);

        /* Create a synthetic LPC item (item_id=-1, lpc_path set) */
        Item *lpc_item = (Item *)calloc(1, sizeof(Item));
        lpc_item->id        = -1;
        lpc_item->name      = strdup("magic ring");
        lpc_item->description = strdup("A shimmering ring.");
        lpc_item->lpc_path  = strdup("/obj/rings/magic_ring");
        lpc_item->stack_count = 1;
        inventory_add_force(&inv, lpc_item);

        FILE *f = round_trip_write(&inv, &eq);

        /* Peek at the raw bytes: first int = item_count, second int = sentinel -2 */
        rewind(f);
        int count_raw = 0, sentinel_raw = 0;
        fread(&count_raw, sizeof(int), 1, f);
        fread(&sentinel_raw, sizeof(int), 1, f);
        CHECK(count_raw == 1,    "item_count written as 1");
        CHECK(sentinel_raw == -2,"sentinel -2 written for LPC item");
        rewind(f);

        /* Load: resolve_lpc_path stub returns 0 → item skipped gracefully */
        Inventory loaded; inventory_init(&loaded, 10);
        EquipmentSlots leq; equipment_init(&leq);
        inventory_read_from_file(&loaded, &leq, f);
        fclose(f);

        CHECK(loaded.item_count == 0, "LPC item skipped gracefully (no VM, count==0)");
        inventory_free(&loaded);
        inventory_free(&inv);
    }

    /* ---- Summary ---- */
    printf("\n=== Results: %d/%d passed", tests_passed, tests_run);
    if (tests_failed == 0)
        printf(" — ALL PASS ===\n");
    else
        printf(", %d FAILED ===\n", tests_failed);

    return tests_failed > 0 ? 1 : 0;
}

# Driver Source Analysis

Total driver source files: 68

### src/array.c
- Purpose: *out = arr->elements[arr->length - 1];
- Lines: 140, Size: 3638 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #include "array.h"; #include <stdlib.h>; #include <string.h>
  - Functions (preview): static void* arr_alloc(GC *gc, size_t size, GCObjectType type) {; static void arr_release(GC *gc, void *ptr) {; array_t* array_new(GC *gc, size_t capacity) {; static int array_grow(array_t *arr) {
- Dependencies: #include "array.h", #include <stdlib.h>, #include <string.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/array.h
- Purpose: Implements array.h
- Lines: 26, Size: 844 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define ARRAY_H; #include <stddef.h>; #include "gc.h"; #include "vm.h"
  - Functions (preview): 
- Dependencies: #define ARRAY_H, #include <stddef.h>, #include "gc.h", #include "vm.h"
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/chargen.c
- Purpose: /* External function from session.c */ /* External from driver.c - find a player session by name */ /* External from room.c - movement command */
- Lines: 2808, Size: 102630 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #include "chargen.h"; #include "session_internal.h"; #include "room.h"; #include "npc.h"
  - Functions (preview): int roll_3d6(void) {; int roll_1d6(void) {; static int character_add_language(Character *ch, const char *lang) {; static void assign_starting_languages(Character *ch) {
- Dependencies: #include "chargen.h", #include "session_internal.h", #include "room.h", #include "npc.h", #include "skills.h", #include "combat.h"
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/chargen.h
- Purpose: /* Forward declare from session_internal.h */ /* Forward declare skill structures */ /* Character generation states */
- Lines: 201, Size: 7130 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define CHARGEN_H; #include <stddef.h>; #include "item.h"; #include "psionics.h"
  - Functions (preview): 
- Dependencies: #define CHARGEN_H, #include <stddef.h>, #include "item.h", #include "psionics.h", #include "magic.h", #define MAX_SCARS 5
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/codegen.c
- Purpose: /* * codegen.c - Code Generator Implementation *
- Lines: 1127, Size: 38656 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #include "codegen.h"; #include <stdio.h>; #include <stdlib.h>; #include <string.h>
  - Functions (preview): static void* xmalloc(size_t size) {; static void* xrealloc(void *ptr, size_t size) {; static char* xstrdup(const char *str) {; static unsigned int symbol_hash(const char *name) {
- Dependencies: #include "codegen.h", #include <stdio.h>, #include <stdlib.h>, #include <string.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/codegen.h
- Purpose: /* * codegen.h - Code Generator Header *
- Lines: 302, Size: 8141 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #define CODEGEN_H; #include "parser.h"; #include "vm.h"
  - Functions (preview): 
- Dependencies: #define CODEGEN_H, #include "parser.h", #include "vm.h"
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/combat.c
- Purpose: // External function declarations // Forward declarations // ============================================================================
- Lines: 1161, Size: 37389 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #include "combat.h"; #include "npc.h"; #include "room.h"; #include "skills.h"
  - Functions (preview): void combat_init(void) {; int combat_roll_dice(int num_dice, int sides) {; int combat_d20(void) {; static int combat_should_attack_this_tick(int attacks_per_round, int tick_in_round) {
- Dependencies: #include "combat.h", #include "npc.h", #include "room.h", #include "skills.h", #include "item.h", #include "session_internal.h"
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/combat.h
- Purpose: // ============================================================================ // COMBAT SYSTEM - Real-Time Heartbeat-Driven Combat // ============================================================================
- Lines: 115, Size: 4740 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define COMBAT_H; #include <stdbool.h>; #include "chargen.h"; #include "session_internal.h"
  - Functions (preview): 
- Dependencies: #define COMBAT_H, #include <stdbool.h>, #include "chargen.h", #include "session_internal.h", #define MELEE_ROUND_TICKS  8    /* 8 ticks per melee round (16 seconds at 2s/tick) */, #define COMBAT_TICK_SECS   2    /* Heartbeat interval in seconds */
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/compile_stubs.c
- Purpose: /* compile_stubs.c - Provide minimal stubs for compiler/program loader * * Tests that build efun.c may not link the full compiler/program_loader
- Lines: 36, Size: 900 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #include "compiler.h"; #include "program_loader.h"; #include "session.h"
  - Functions (preview): Program *compiler_compile_file(const char *path) {; int program_loader_load(VirtualMachine *vm, Program *prog) {; void program_free(Program *prog) {; void *get_current_player_object(void) {
- Dependencies: #include "compiler.h", #include "program_loader.h", #include "session.h"
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/compiler.c
- Purpose: /* Per-function local variable tracking (reset per function) */ /** * Read file contents into memory
- Lines: 1226, Size: 44637 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #include "compiler.h"; #include "lexer.h"; #include "parser.h"; #include "preprocessor.h"
  - Functions (preview): static char* read_file(const char *filename) {; static compiler_state_t* compiler_state_new(void) {; static void compiler_state_free(compiler_state_t *state) {; static void compiler_add_global(compiler_state_t *state, const char *name) {
- Dependencies: #include "compiler.h", #include "lexer.h", #include "parser.h", #include "preprocessor.h", #include <stdio.h>, #include <stdlib.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/compiler.h
- Purpose: // Bytecode and constants // Function table // Global variables
- Lines: 88, Size: 1971 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define COMPILER_H; #include "vm.h"; #include "codegen.h"
  - Functions (preview): 
- Dependencies: #define COMPILER_H, #include "vm.h", #include "codegen.h"
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/death.c
- Purpose: /* send_to_player is defined in the UI layer (used across modules) */ /* TODO: hook into LPC corpse creation. For now, log and notify room. */ /* TODO: delete character file and boot player */
- Lines: 96, Size: 3650 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #include "chargen.h"; #include "session_internal.h"; #include "room.h"; #include "debug.h"
  - Functions (preview): void add_death_scar(Character *ch) {; void create_player_corpse(PlayerSession *sess) {; void handle_player_death(PlayerSession *sess, PlayerSession *killer) {
- Dependencies: #include "chargen.h", #include "session_internal.h", #include "room.h", #include "debug.h", #include <stdio.h>, #include <stdlib.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/debug.h
- Purpose: /* Debug output control * Can be enabled via: * 1. Environment variable: export AMLP_DEBUG=1
- Lines: 80, Size: 1925 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define AMLP_DEBUG_H; #include <stdlib.h>; #include <stdio.h>; #include <string.h>
  - Functions (preview): 
- Dependencies: #define AMLP_DEBUG_H, #include <stdlib.h>, #include <stdio.h>, #include <string.h>, #define AMLP_DEBUG_VERBOSE() (getenv("AMLP_DEBUG") != NULL), #define DEBUG_LOG(fmt, ...) \
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/driver.c
- Purpose: /* * driver.c - AMLP MUD Driver with Network Server *
- Lines: 4877, Size: 184697 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #define _GNU_SOURCE  /* for memmem(), strcasestr() */; #include <stdio.h>; #include <stdlib.h>; #include <string.h>
  - Functions (preview): static const char *value_type_name(ValueType type) {; static void command_debug_init(void) {; static void command_debug_log_result(PlayerSession *session, VMValue result) {; void handle_shutdown_signal(int sig) {
- Dependencies: #define _GNU_SOURCE  /* for memmem(), strcasestr() */, #include <stdio.h>, #include <stdlib.h>, #include <string.h>, #include <unistd.h>, #include <errno.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/driver.h
- Purpose: /* driver.h - shared driver symbols exposed to other modules */ /* Server control flag (defined in driver.c) */
- Lines: 10, Size: 218 bytes
- Status: ⬜ stub/missing
- Core responsibilities:
  - Includes: #define DRIVER_H; #include <signal.h>
  - Functions (preview): 
- Dependencies: #define DRIVER_H, #include <signal.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/efun.c
- Purpose: /** * efun.c - External Functions (Efuns) Implementation *
- Lines: 2593, Size: 91031 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #include "efun.h"; #include "vm.h"; #include "debug.h"; #include "array.h"
  - Functions (preview): EfunRegistry* efun_init(void) {; EfunEntry* efun_find(EfunRegistry *registry, const char *name) {; void efun_free(EfunRegistry *registry) {; VMValue efun_strlen(VirtualMachine *vm, VMValue *args, int arg_count) {
- Dependencies: #include "efun.h", #include "vm.h", #include "debug.h", #include "array.h", #include "mapping.h", #include "object.h"
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/efun.h
- Purpose: /** * efun.h - External Functions (Efuns) Header *
- Lines: 203, Size: 7727 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define EFUN_H; #include "vm.h"; #include "array.h"; #include "mapping.h"
  - Functions (preview): 
- Dependencies: #define EFUN_H, #include "vm.h", #include "array.h", #include "mapping.h", #include <stddef.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/gc.c
- Purpose: /** * gc.c - Garbage Collection System Implementation *
- Lines: 431, Size: 10895 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #include "gc.h"; #include <stdlib.h>; #include <stdio.h>; #include <string.h>
  - Functions (preview): GCObject* gc_find_object(GC *gc, void *ptr) {; static int gc_remove_object(GC *gc, GCObject *obj) {; GC* gc_init(void) {; void* gc_alloc(GC *gc, size_t size, GCObjectType type) {
- Dependencies: #include "gc.h", #include <stdlib.h>, #include <stdio.h>, #include <string.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/gc.h
- Purpose: /** * gc.h - Garbage Collection System Header *
- Lines: 263, Size: 6750 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define GC_H; #include <stddef.h>; #define GC_INITIAL_CAPACITY 256; #define GC_COLLECT_THRESHOLD 1000    /* Collect after this many allocations */
  - Functions (preview): 
- Dependencies: #define GC_H, #include <stddef.h>, #define GC_INITIAL_CAPACITY 256, #define GC_COLLECT_THRESHOLD 1000    /* Collect after this many allocations */, #define GC_MAX_OBJECTS 100000         /* Maximum tracked objects */
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/item.c
- Purpose: /* External function declaration */ /* Item Template Database */ /* Initialize item system and database */
- Lines: 851, Size: 33943 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #include "item.h"; #include "chargen.h"; #include "session_internal.h"; #include "debug.h"
  - Functions (preview): void item_init(void) {; Item* item_create(int template_id) {
- Dependencies: #include "item.h", #include "chargen.h", #include "session_internal.h", #include "debug.h", #include <stdio.h>, #include <stdlib.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/item.h
- Purpose: /* Forward declarations to avoid circular includes */ /* Item Types */ /* Weapon Types */
- Lines: 128, Size: 4503 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define ITEM_H; #include <stdbool.h>; #include <stddef.h>  // For size_t; #define TOTAL_ITEM_TEMPLATES 50
  - Functions (preview): 
- Dependencies: #define ITEM_H, #include <stdbool.h>, #include <stddef.h>  // For size_t, #define TOTAL_ITEM_TEMPLATES 50
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/lexer.c
- Purpose: /* * lexer.c - Lexical Analyzer Implementation *
- Lines: 605, Size: 18889 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #define _POSIX_C_SOURCE 200809L; #include "lexer.h"; #include <ctype.h>; #include <errno.h>
  - Functions (preview): static int is_keyword(const char *value) {; static Token make_token(TokenType type, const char *value, int line, int column) {; static int lexer_is_at_end(Lexer *lexer) {; static char lexer_current_char(Lexer *lexer) {
- Dependencies: #define _POSIX_C_SOURCE 200809L, #include "lexer.h", #include <ctype.h>, #include <errno.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/lexer.h
- Purpose: /* * lexer.h - Lexical Analyzer Header *
- Lines: 148, Size: 4667 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define LEXER_H; #include <stdio.h>; #include <stdlib.h>; #include <string.h>
  - Functions (preview): 
- Dependencies: #define LEXER_H, #include <stdio.h>, #include <stdlib.h>, #include <string.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/magic.c
- Purpose: /* Forward declaration */ /* =============== MAGIC SPELLS DATABASE =============== */ /* WARLOCK GRADE SPELLS (0-7) - Level 1-5 */
- Lines: 1038, Size: 42324 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #include "magic.h"; #include "chargen.h"; #include "session_internal.h"; #include "room.h"
  - Functions (preview): void magic_init(void) {; MagicSpell* magic_find_spell_by_id(int spell_id) {; MagicSpell* magic_find_spell_by_name(const char *name) {; MagicSpell* magic_find_spell_by_lpc_id(const char *lpc_id) {
- Dependencies: #include "magic.h", #include "chargen.h", #include "session_internal.h", #include "room.h", #include "npc.h", #include "vm.h"
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/magic.h
- Purpose: /* Forward declarations */ /* Magic Spell Schools */ /* Magic spell structure */
- Lines: 125, Size: 4975 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define MAGIC_H; #include <stdbool.h>; #include <time.h>
  - Functions (preview): 
- Dependencies: #define MAGIC_H, #include <stdbool.h>, #include <time.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/mapping.c
- Purpose: Implements mapping.c
- Lines: 172, Size: 4954 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #include "mapping.h"; #include <stdlib.h>; #include <string.h>
  - Functions (preview): static unsigned int map_hash(const char *key, size_t capacity) {; static void* map_alloc(GC *gc, size_t size, GCObjectType type) {; static void map_release(GC *gc, void *ptr) {; mapping_t* mapping_new(GC *gc, size_t buckets) {
- Dependencies: #include "mapping.h", #include <stdlib.h>, #include <string.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/mapping.h
- Purpose: Implements mapping.h
- Lines: 32, Size: 845 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define MAPPING_H; #include <stddef.h>; #include "gc.h"; #include "vm.h"
  - Functions (preview): 
- Dependencies: #define MAPPING_H, #include <stddef.h>, #include "gc.h", #include "vm.h", #include "array.h"
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/master_object.c
- Purpose: /* Module state */ /* Use efun_load_object to compile, load, handle inheritance, and call create() */
- Lines: 148, Size: 4024 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #include "master_object.h"; #include "vm.h"; #include "efun.h"; #include <stdio.h>
  - Functions (preview): int master_object_init(const char *path, VirtualMachine *vm) {; static char *find_master_file(void) {; int master_register_callbacks(void) {; void master_callback_compile_object(const char *filename) {
- Dependencies: #include "master_object.h", #include "vm.h", #include "efun.h", #include <stdio.h>, #include <stdlib.h>, #include <string.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/master_object.h
- Purpose: /* Initialize master object from file and set up VM */ /* Register master object callbacks with the driver */ /* Callback functions - invoked by driver, implemented by master object */
- Lines: 20, Size: 648 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define MASTER_OBJECT_H; #include "compiler.h"
  - Functions (preview): 
- Dependencies: #define MASTER_OBJECT_H, #include "compiler.h"
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/npc.c
- Purpose: /* npc.c - NPC/mob spawning, AI, and combat integration */ /* External */ /* ================================================================ */
- Lines: 449, Size: 15092 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #include "npc.h"; #include "combat.h"; #include "room.h"; #include "session_internal.h"
  - Functions (preview): void npc_init(void) {; void npc_cleanup(void) {; NPC* npc_spawn(NpcTemplateId template_id, int room_id) {; void npc_despawn(NPC *npc) {
- Dependencies: #include "npc.h", #include "combat.h", #include "room.h", #include "session_internal.h", #include "race_loader.h", #include <stdlib.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/npc.h
- Purpose: /* npc.h - NPC/mob system for spawnable creatures */ /* Forward declarations */ /* NPC template IDs */
- Lines: 94, Size: 2777 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define NPC_H; #include <stdbool.h>; #include "chargen.h"; #define MAX_NPCS_PER_ROOM 8
  - Functions (preview): 
- Dependencies: #define NPC_H, #include <stdbool.h>, #include "chargen.h", #define MAX_NPCS_PER_ROOM 8, #define MAX_NPCS_GLOBAL 64
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/object.c
- Purpose: /** * object.c - LPC Object System Implementation *
- Lines: 535, Size: 14859 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #include "object.h"; #include "vm.h"; #include "debug.h"; #include <stdlib.h>
  - Functions (preview): static int property_hash(const char *name, int capacity) {; static ObjProperty* find_property(obj_t *obj, const char *prop_name) {; obj_t* obj_new(const char *name) {; obj_t* obj_clone(obj_t *original) {
- Dependencies: #include "object.h", #include "vm.h", #include "debug.h", #include <stdlib.h>, #include <string.h>, #include <stdio.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/object.h
- Purpose: /** * object.h - LPC Object System Header *
- Lines: 288, Size: 7778 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define OBJECT_H; #include "vm.h"; #include <stddef.h>; #define OBJ_PROPERTY_HASH_SIZE 32
  - Functions (preview): 
- Dependencies: #define OBJECT_H, #include "vm.h", #include <stddef.h>, #define OBJ_PROPERTY_HASH_SIZE 32, #define OBJ_INITIAL_METHOD_CAPACITY 16, #define OBJ_MANAGER_INITIAL_CAPACITY 128
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/parser.c
- Purpose: /* * parser.c - Parser Implementation *
- Lines: 1615, Size: 61814 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #define _POSIX_C_SOURCE 200809L; #include "parser.h"; #include "lexer.h"; #include <stdlib.h>
  - Functions (preview): static void parser_advance(Parser *parser) {; static int parser_check(Parser *parser, TokenType type) {; static int parser_match(Parser *parser, TokenType type) {; static void parser_expect(Parser *parser, TokenType type) {
- Dependencies: #define _POSIX_C_SOURCE 200809L, #include "parser.h", #include "lexer.h", #include <stdlib.h>, #include <string.h>, #include <stdio.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/parser.h
- Purpose: /* * parser.h - Parser Header *
- Lines: 326, Size: 10974 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #define PARSER_H; #include "lexer.h"
  - Functions (preview): 
- Dependencies: #define PARSER_H, #include "lexer.h"
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/parser_state.h
- Purpose: /* Magic number for state validation */ /* State validation macros */
- Lines: 37, Size: 1007 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define PARSER_STATE_H; #include <stdint.h>; #include <stdio.h>; #include <stdlib.h>
  - Functions (preview): 
- Dependencies: #define PARSER_STATE_H, #include <stdint.h>, #include <stdio.h>, #include <stdlib.h>, #define PARSER_STATE_MAGIC 0x50415253  /* "PARS" */, #define PARSER_STATE_INIT(state) \
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/preprocessor.c
- Purpose: /** * preprocessor.c - LPC Preprocessor Implementation *
- Lines: 634, Size: 18587 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #include "preprocessor.h"; #include <stdio.h>; #include <stdlib.h>; #include <string.h>
  - Functions (preview): static void ppbuf_init(PPBuf *b) {; static void ppbuf_append(PPBuf *b, const char *s, size_t n) {; static void ppbuf_append_str(PPBuf *b, const char *s) {; static void ppbuf_append_char(PPBuf *b, char c) {
- Dependencies: #include "preprocessor.h", #include <stdio.h>, #include <stdlib.h>, #include <string.h>, #include <ctype.h>, #include <limits.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/preprocessor.h
- Purpose: /** * preprocessor.h - LPC Preprocessor *
- Lines: 24, Size: 670 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define PREPROCESSOR_H
  - Functions (preview): 
- Dependencies: #define PREPROCESSOR_H
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/program.c
- Purpose: /** * Load and compile program from file */
- Lines: 125, Size: 3340 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #include "program.h"; #include "vm.h"; #include <stdio.h>; #include <stdlib.h>
  - Functions (preview): Program* program_load_file(const char *filename) {; Program* program_load_string(const char *source, const char *name) {; int program_function_count(Program *prog) {; const char* program_function_name(Program *prog, int index) {
- Dependencies: #include "program.h", #include "vm.h", #include <stdio.h>, #include <stdlib.h>, #include <string.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/program.h
- Purpose: /** * Program management - handles loading, execution, and lifecycle of compiled LPC programs */
- Lines: 46, Size: 1307 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define PROGRAM_H; #include "compiler.h"
  - Functions (preview): 
- Dependencies: #define PROGRAM_H, #include "compiler.h"
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/program_loader.c
- Purpose: /* * program_loader.c - Program Loader Implementation *
- Lines: 541, Size: 20953 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #define _POSIX_C_SOURCE 200809L; #include "program_loader.h"; #include <stdio.h>; #include <stdlib.h>
  - Functions (preview): static uint8_t read_u8(const uint8_t *bytecode, size_t *offset) {; static uint16_t read_u16(const uint8_t *bytecode, size_t *offset) {; static long read_i64(const uint8_t *bytecode, size_t *offset) {; static double read_f64(const uint8_t *bytecode, size_t *offset) {
- Dependencies: #define _POSIX_C_SOURCE 200809L, #include "program_loader.h", #include <stdio.h>, #include <stdlib.h>, #include <string.h>, #include <unistd.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/program_loader.h
- Purpose: /* * program_loader.h - Program Loader *
- Lines: 60, Size: 1974 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define PROGRAM_LOADER_H; #include "compiler.h"; #include "vm.h"
  - Functions (preview): 
- Dependencies: #define PROGRAM_LOADER_H, #include "compiler.h", #include "vm.h"
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/psionics.c
- Purpose: /* Forward declaration */ /* =============== PSIONIC POWERS DATABASE =============== */ /* SUPER PSIONIC POWERS (0-5) */
- Lines: 640, Size: 27271 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #include "psionics.h"; #include "chargen.h"; #include "session_internal.h"; #include "room.h"
  - Functions (preview): void psionics_init(void) {; PsionicPower* psionics_find_power_by_id(int power_id) {; PsionicPower* psionics_find_power_by_name(const char *name) {; KnownPower* psionics_find_known_power(Character *ch, int power_id) {
- Dependencies: #include "psionics.h", #include "chargen.h", #include "session_internal.h", #include "room.h", #include <stdlib.h>, #include <string.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/psionics.h
- Purpose: /* Forward declarations */ /* Psionic Power Categories */ /* Psionic power structure */
- Lines: 102, Size: 3855 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define PSIONICS_H; #include <stdbool.h>; #include <time.h>
  - Functions (preview): 
- Dependencies: #define PSIONICS_H, #include <stdbool.h>, #include <time.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/race_loader.c
- Purpose: /* race_loader.c - Race / O.C.C. data loading and level progression * * Parses LPC race and OCC definition files from lib/races/ and lib/occs/,
- Lines: 765, Size: 27315 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #include "race_loader.h"; #include "chargen.h"; #include <string.h>; #include <stdlib.h>
  - Functions (preview): static void add_natural_weapon(Character *ch, const char *name) {; static void name_to_filename(const char *name, char *out, size_t out_sz) {; static char *read_file_to_buffer(const char *path) {; char *lpc_extract_string(const char *buf, const char *snake, const char *pascal) {
- Dependencies: #include "race_loader.h", #include "chargen.h", #include <string.h>, #include <stdlib.h>, #include <ctype.h>, #include <stdio.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/race_loader.h
- Purpose: /* race_loader.h - Load and apply race / O.C.C. data to characters */ /* ---- Parsed mapping for LPC ([ "key": val, ... ]) ---- */ /* XP table (Palladium-inspired, levels 1-15) */
- Lines: 71, Size: 2527 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define RACE_LOADER_H; #include "session_internal.h"; #define PARSED_MAP_MAX 16; #define MAX_LEVEL 15
  - Functions (preview): 
- Dependencies: #define RACE_LOADER_H, #include "session_internal.h", #define PARSED_MAP_MAX 16, #define MAX_LEVEL 15, #define MAX_LOADED_RACES 128, #define MAX_LOADED_OCCS  128
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/room.c
- Purpose: /* World data - bootstrap C rooms */ /* Dynamic LPC room pool */ /* Path lookup table for LPC rooms */
- Lines: 1666, Size: 59216 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #include "room.h"; #include "npc.h"; #include "item.h"; #include "session_internal.h"
  - Functions (preview): static void preprocess_lpc_macros(char *out, const char *in, size_t max_out) {; static char* room_extract_string(const char *buf, const char *setter_name) {; static int room_parse_add_exits(const char *buf, RoomExit **exits_out) {; static int room_parse_set_exits(const char *buf, RoomExit **exits_out) {
- Dependencies: #include "room.h", #include "npc.h", #include "item.h", #include "session_internal.h", #include <stdio.h>, #include <stdlib.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/room.h
- Purpose: /* Forward declare from session_internal.h */ /* Flexible exit: supports any direction name + LPC path destinations */ /* Examinable room detail from set_items() */
- Lines: 83, Size: 2737 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define ROOM_H; #include <stddef.h>; #include <stdbool.h>; #include "item.h"
  - Functions (preview): 
- Dependencies: #define ROOM_H, #include <stddef.h>, #include <stdbool.h>, #include "item.h", #define MAX_NPCS_PER_ROOM 8
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/server.c
- Purpose: /* * server.c - Filesystem Commands for AMLP MUD Driver *
- Lines: 552, Size: 18794 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #define _GNU_SOURCE  /* for strdup() */; #include <stdio.h>; #include <stdlib.h>; #include <string.h>
  - Functions (preview): static void get_player_home_dir(PlayerSession *session, char *buf, size_t buf_size) {; int cmd_ls_filesystem(PlayerSession *session, const char *args) {; int cmd_cd_filesystem(PlayerSession *session, const char *args) {; int cmd_pwd_filesystem(PlayerSession *session) {
- Dependencies: #define _GNU_SOURCE  /* for strdup() */, #include <stdio.h>, #include <stdlib.h>, #include <string.h>, #include <unistd.h>, #include <sys/stat.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/session.c
- Purpose: /* session.c - Driver session implementation for VM context access */ /* Opaque player session pointer implementation lives in driver; we keep a * single pointer here that the driver sets when routing commands into
- Lines: 18, Size: 594 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #include "session.h"; #include "session_internal.h"
  - Functions (preview): void *get_current_player_object(void) {; void set_current_session(void *session) {
- Dependencies: #include "session.h", #include "session_internal.h"
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/session.h
- Purpose: /* session.h - Session API for efuns to access current player object */ /* Forward declaration */ /* Return the current player object for the executing VM context, or NULL. */
- Lines: 21, Size: 659 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define SESSION_H
  - Functions (preview): 
- Dependencies: #define SESSION_H
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/session_internal.h
- Purpose: /* session_internal.h - Internal PlayerSession definition shared by driver and session.c */ /* Forward declarations */ /* Character generation and game state */
- Lines: 89, Size: 3240 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define SESSION_INTERNAL_H; #include <time.h>; #include <netinet/in.h>; #include "websocket.h"
  - Functions (preview): 
- Dependencies: #define SESSION_INTERNAL_H, #include <time.h>, #include <netinet/in.h>, #include "websocket.h", #include "chargen.h"  /* Character generation system */, #define MAX_CLIENTS 100
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/simul_efun.c
- Purpose: /** * Create new simul efun registry */
- Lines: 170, Size: 4568 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #include "simul_efun.h"; #include <stdlib.h>; #include <string.h>; #include <stdio.h>
  - Functions (preview): simul_efun_registry_t* simul_efun_registry_new(void) {; void simul_efun_registry_free(simul_efun_registry_t *registry) {; int simul_efun_load_object(simul_efun_registry_t *registry, const char *filename) {; int simul_efun_find(simul_efun_registry_t *registry, const char *name) {
- Dependencies: #include "simul_efun.h", #include <stdlib.h>, #include <string.h>, #include <stdio.h>, #define INITIAL_SIMUL_EFUN_CAPACITY 32
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/simul_efun.h
- Purpose: /** * Simulated efuns - LPC functions that behave like built-in efuns * Allows LPC code to define custom efun-like functions in a simul_efun object
- Lines: 43, Size: 1273 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define SIMUL_EFUN_H; #include "compiler.h"; #include "vm.h"
  - Functions (preview): 
- Dependencies: #define SIMUL_EFUN_H, #include "compiler.h", #include "vm.h"
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/skills.c
- Purpose: /* skills.c - Rifts RPG Skill System Implementation */ /* External declarations */ /* ========== SKILL DATABASE ========== */
- Lines: 920, Size: 27307 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #include <stdio.h>; #include <stdlib.h>; #include <string.h>; #include <time.h>
  - Functions (preview): 
- Dependencies: #include <stdio.h>, #include <stdlib.h>, #include <string.h>, #include <time.h>, #include "skills.h", #include "session_internal.h"
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/skills.h
- Purpose: /* skills.h - Rifts RPG skill system definitions */ /* Race/OCC info structure (mirrors chargen.c) */ /* Maximum skills per character */
- Lines: 64, Size: 2037 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define __SKILLS_H__; #include "chargen.h"  /* For PlayerSkill typedef */; #include "session_internal.h"  /* For PlayerSession */; #define MAX_PLAYER_SKILLS 20
  - Functions (preview): 
- Dependencies: #define __SKILLS_H__, #include "chargen.h"  /* For PlayerSkill typedef */, #include "session_internal.h"  /* For PlayerSession */, #define MAX_PLAYER_SKILLS 20
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/skills_config.h
- Purpose: /* * skills_config.h - O.C.C.-specific skill configurations *
- Lines: 318, Size: 10103 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #define SKILLS_CONFIG_H; #include "wiz_tools.h"
  - Functions (preview): static inline OCCSkillConfig *get_occ_skill_config(const char *occ_name) {
- Dependencies: #define SKILLS_CONFIG_H, #include "wiz_tools.h"
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/terminal_ui.c
- Purpose: // ANSI Color Codes // ANSI Control Codes // ASCII Box Drawing Characters
- Lines: 197, Size: 5435 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #include "terminal_ui.h"; #include <stdio.h>; #include <string.h>; #define COLOR_RESET   "\033[0m"
  - Functions (preview): static void move_cursor(int x, int y) {; void tui_init(void) {; void tui_cleanup(void) {; void tui_draw_box(int x, int y, int width, int height, const char* title) {
- Dependencies: #include "terminal_ui.h", #include <stdio.h>, #include <string.h>, #define COLOR_RESET   "\033[0m", #define COLOR_CYAN    "\033[36m", #define COLOR_YELLOW  "\033[33m"
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/terminal_ui.h
- Purpose: // Terminal UI module for styled build output // Uses ANSI escape codes and UTF-8 box drawing characters // Initialize terminal (clear screen, hide cursor)
- Lines: 31, Size: 970 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define TERMINAL_UI_H
  - Functions (preview): 
- Dependencies: #define TERMINAL_UI_H
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/test_stubs.c
- Purpose: /* test_stubs.c - minimal test-time stubs for symbols referenced by core modules * These are lightweight no-op implementations used when building unit tests * so tests can link without pulling the full driver/network code.
- Lines: 66, Size: 2343 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #include <stddef.h>; #include <stdlib.h>
  - Functions (preview): void send_message_to_player_session(void *player_obj, const char *message) {; void *get_current_player_object(void) {; void set_current_session(void *session) {; char *ws_convert_ansi(const char *text, int keep_colors) {
- Dependencies: #include <stddef.h>, #include <stdlib.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/ui_frames.c
- Purpose: /* ui_frames.c - Unicode box-drawing UI helpers for AetherMUD */ /* External from session.c */ /* ASCII box-drawing characters (plain telnet compatible) */
- Lines: 140, Size: 4808 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #include "ui_frames.h"; #include "session_internal.h"; #include <stdio.h>; #include <string.h>
  - Functions (preview): static void draw_hline(PlayerSession *sess, int width) {; void frame_top(PlayerSession *sess, int width) {; void frame_bottom(PlayerSession *sess, int width) {; void frame_sep(PlayerSession *sess, int width) {
- Dependencies: #include "ui_frames.h", #include "session_internal.h", #include <stdio.h>, #include <string.h>, #define BOX_TL "+", #define BOX_TR "+"
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/ui_frames.h
- Purpose: /* ui_frames.h - Unicode box-drawing UI helpers for AetherMUD */ /* Forward declaration */ /* Default frame width (inner content width, not counting borders) */
- Lines: 39, Size: 1713 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define UI_FRAMES_H; #define FRAME_WIDTH 80
  - Functions (preview): 
- Dependencies: #define UI_FRAMES_H, #define FRAME_WIDTH 80
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/vm.c
- Purpose: /* * vm.c - Virtual Machine Implementation *
- Lines: 1456, Size: 55335 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #define _POSIX_C_SOURCE 200809L; #include "vm.h"; #include "efun.h"; #include "object.h"
  - Functions (preview): static VMStringHeader *vm_string_header(const char *data) {; static char *vm_string_create(const char *value, size_t len) {; VirtualMachine* vm_init(void) {; int vm_load_program(VirtualMachine *vm, ASTNode *program) {
- Dependencies: #define _POSIX_C_SOURCE 200809L, #include "vm.h", #include "efun.h", #include "object.h", #include "debug.h", #include <stdio.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/vm.h
- Purpose: /* * vm.h - Virtual Machine Header *
- Lines: 483, Size: 14437 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #define VM_H; #include "parser.h"; #include "gc.h"; #include <stdint.h>
  - Functions (preview): 
- Dependencies: #define VM_H, #include "parser.h", #include "gc.h", #include <stdint.h>, #include <stddef.h>, #include <stdio.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/websocket.c
- Purpose: /* * websocket.c - WebSocket Protocol Implementation for AMLP MUD Driver *
- Lines: 632, Size: 19432 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #include "websocket.h"; #include <stdio.h>; #include <stdlib.h>; #include <string.h>
  - Functions (preview): static uint32_t sha1_rol(uint32_t value, int bits) {; static void sha1_hash(const uint8_t *data, size_t len, uint8_t *output) {; static char *base64_encode(const uint8_t *data, size_t len) {; static char *find_header_value(const char *request, const char *header) {
- Dependencies: #include "websocket.h", #include <stdio.h>, #include <stdlib.h>, #include <string.h>, #include <ctype.h>
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/websocket.h
- Purpose: /* * websocket.h - WebSocket Protocol Support for AMLP MUD Driver *
- Lines: 180, Size: 5528 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define WEBSOCKET_H; #include <stdint.h>; #include <stddef.h>; #define WS_OPCODE_CONTINUATION  0x0
  - Functions (preview): 
- Dependencies: #define WEBSOCKET_H, #include <stdint.h>, #include <stddef.h>, #define WS_OPCODE_CONTINUATION  0x0, #define WS_OPCODE_TEXT          0x1, #define WS_OPCODE_BINARY        0x2
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/wiz_tools.c
- Purpose: /* * wiz_tools.c - Implementation of wizard customization tools *
- Lines: 1089, Size: 40983 bytes
- Status: ✅ complete
- Core responsibilities:
  - Includes: #include "wiz_tools.h"; #include <stdio.h>; #include <stdarg.h>; #include <stdlib.h>
  - Functions (preview): int wiz_goto(PlayerSession *sess, const char *room_arg) {; int wiz_summon(PlayerSession *sess, const char *player_name) {; int wiz_teleport(PlayerSession *sess, const char *player_name, const char *room_arg) {; int wiz_force(PlayerSession *sess, const char *target_name, const char *command) {
- Dependencies: #include "wiz_tools.h", #include <stdio.h>, #include <stdarg.h>, #include <stdlib.h>, #include <string.h>, #include "room.h"
- Integration points: Referenced by other src/ files and lib/ via headers.

### src/wiz_tools.h
- Purpose: /* * wiz_tools.h - Wizard command tools for character customization *
- Lines: 180, Size: 6392 bytes
- Status: ⚠️ partial
- Core responsibilities:
  - Includes: #define WIZ_TOOLS_H; #define MAX_PRIMARY_SKILLS 15; #define MAX_OCC_RELATED_SKILLS 12; #define MAX_SECONDARY_SKILLS 8
  - Functions (preview): 
- Dependencies: #define WIZ_TOOLS_H, #define MAX_PRIMARY_SKILLS 15, #define MAX_OCC_RELATED_SKILLS 12, #define MAX_SECONDARY_SKILLS 8
- Integration points: Referenced by other src/ files and lib/ via headers.

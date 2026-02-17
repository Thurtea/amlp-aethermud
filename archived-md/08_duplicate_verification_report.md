# Duplicate Verification Report

Scanned top 20 high-priority C/H duplicates.

## 1. array.c
- Canonical: `src/array.c`
- Compare `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/array.c` -> `src/array.c`
  - Diff (first 20 lines):
    --- src/array.c	2026-02-05 13:29:29.583783839 -0400
    +++ mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/array.c	2011-07-25 18:02:48.000000000 -0300
    @@ -1,140 +1,2344 @@
    -#include "array.h"
    -#include <stdlib.h>
    -#include <string.h>
    +#include "std.h"
    +#include "lpc_incl.h"
    +#include "comm.h"
    +#include "regexp.h"
    +#include "backend.h"
    +#include "qsort.h"
    +#include "md.h"
    +#include "efun_protos.h"
     
    -static void* arr_alloc(GC *gc, size_t size, GCObjectType type) {
    -    if (gc) {
    -        return gc_alloc(gc, size, type);
    +/*
    + * This file contains functions used to manipulate arrays.
 - References in `Makefile`:
   - 21:                      $(SRC_DIR)/array.c \
   - 41:              $(SRC_DIR)/gc.c $(SRC_DIR)/efun.c $(SRC_DIR)/array.c \

**Status:** ⚠️ NEEDS MANUAL REVIEW (Red)

## 2. array.h
- Canonical: `src/array.h`
- Compare `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/array.h` -> `src/array.h`
  - Diff (first 20 lines):
    --- src/array.h	2026-02-05 13:29:29.583783839 -0400
    +++ mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/array.h	2011-07-25 18:02:48.000000000 -0300
    @@ -1,26 +1,76 @@
     #ifndef ARRAY_H
     #define ARRAY_H
     
    -#include <stddef.h>
    -#include "gc.h"
    -#include "vm.h"
    -
    -typedef struct array_t {
    -    GC *gc;                 /* Owning garbage collector (nullable) */
    -    VMValue *elements;      /* Element storage */
    -    size_t length;          /* Number of elements */
    -    size_t capacity;        /* Allocated capacity */
    +/* It is usually better to include "lpc_incl.h" instead of including this
    +   directly */
    +
    +typedef struct array_s {
    +    unsigned short ref;
 - #include references:
   - src/array.c:1:#include "array.h"
   - src/mapping.h:7:#include "array.h"
   - src/efun.c:12:#include "array.h"
   - src/vm.c:19:#include "array.h"
   - src/efun.h:15:#include "array.h"

**Status:** ⚠️ NEEDS MANUAL REVIEW (Red)

## 3. combat.c
- Canonical: `src/combat.c`
- Compare `mud-references/deadsouls/ds3.8.2/lib/lib/combat.c` -> `src/combat.c`
  - Diff (first 20 lines):
    --- src/combat.c	2026-02-15 23:40:27.215795722 -0400
    +++ mud-references/deadsouls/ds3.8.2/lib/lib/combat.c	2009-12-30 05:55:00.000000000 -0400
    @@ -1,1161 +1,1202 @@
    -#include "combat.h"
    -#include "npc.h"
    -#include "room.h"
    -#include "skills.h"
    -#include "item.h"
    -#include "session_internal.h"
    -#include "race_loader.h"
    -#include <stdio.h>
    -#include <stdlib.h>
    -#include <string.h>
    -#include <time.h>
    -#include <ctype.h>
    -#include <strings.h>
    -
    -// External function declarations
    -extern void send_to_player(PlayerSession *sess, const char *format, ...);
    -extern void send_prompt(PlayerSession *session);
 - References in `Makefile`:
   - 48:			  $(SRC_DIR)/combat.c $(SRC_DIR)/item.c $(SRC_DIR)/psionics.c \

**Status:** ⚠️ NEEDS MANUAL REVIEW (Red)

## 4. combat.h
- Canonical: `src/combat.h`
- Compare `lib/include/combat.h` -> `src/combat.h`
  - Diff (first 20 lines):
    --- src/combat.h	2026-02-15 23:37:36.103861300 -0400
    +++ lib/include/combat.h	2026-02-05 13:29:29.575783839 -0400
    @@ -1,115 +1,272 @@
    -#ifndef COMBAT_H
    -#define COMBAT_H
    +// /lib/include/combat.h
    +// Combat System Constants, Archetypes, and Attack Verbs
    +// Phase 2 - Real-Time Verb-Based Combat System
    +
    +#ifndef __COMBAT_H__
    +#define __COMBAT_H__
    +
    +// =============================================================================
    +// COMBAT ARCHETYPES
    +// =============================================================================
    +
    +#define ARCHETYPE_DRAGON            "dragon"
    +#define ARCHETYPE_HUMANOID_UNARMED  "humanoid_unarmed"
    +#define ARCHETYPE_ARMED_MELEE       "armed_melee"
    +#define ARCHETYPE_ARMED_RANGED      "armed_ranged"
 - #include references:
   - src/driver.c:49:#include "combat.h"
   - src/combat.c:1:#include "combat.h"
   - src/chargen.c:6:#include "combat.h"
   - src/npc.c:4:#include "combat.h"
   - lib/daemon/combat.lpc:5:#include <combat.h>
   - lib/cmds/dragon/breath.lpc:5:#include <combat.h>

**Status:** ⚠️ NEEDS MANUAL REVIEW (Red)

## 5. compiler.c
- Canonical: `src/compiler.c`
- Compare `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/compiler.c` -> `src/compiler.c`
  - Diff (first 20 lines):
    --- src/compiler.c	2026-02-09 13:05:19.765752810 -0400
    +++ mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/compiler.c	2011-07-25 18:02:50.000000000 -0300
    @@ -1,1226 +1,2750 @@
    +#include "std.h"
    +#include "lpc_incl.h"
     #include "compiler.h"
    -#include "lexer.h"
    -#include "parser.h"
    -#include "preprocessor.h"
    -#include <stdio.h>
    -#include <stdlib.h>
    -#include <string.h>
    -#include <ctype.h>
    -#include <unistd.h>
    -
    -#define MAX_ERRORS 100
    -#define INITIAL_BYTECODE_SIZE 1024
    -#define INITIAL_FUNCTION_COUNT 16
    -#define INITIAL_GLOBALS_COUNT 16
    -
 - References in `Makefile`:
   - 27:                      $(SRC_DIR)/compiler.c \
   - 42:              $(SRC_DIR)/mapping.c $(SRC_DIR)/compiler.c $(SRC_DIR)/program.c \

**Status:** ⚠️ NEEDS MANUAL REVIEW (Red)

## 6. compiler.h
- Canonical: `src/compiler.h`
- Compare `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/compiler.h` -> `src/compiler.h`
  - Diff (first 20 lines):
    --- src/compiler.h	2026-02-09 12:49:01.470084943 -0400
    +++ mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/compiler.h	2011-07-25 18:02:50.000000000 -0300
    @@ -1,88 +1,295 @@
     #ifndef COMPILER_H
     #define COMPILER_H
     
    -#include "vm.h"
    -#include "codegen.h"
    +#include "trees.h"
    +#include "lex.h"
    +#include "program.h"
    +
    +#define _YACC_
    +
    +#define YYMAXDEPTH    600
    +
    +/*
    + * Information for allocating a block that can grow dynamically
    + * using realloc. That means that no pointers should be kept into such
    + * an area, as it might be moved.
 - #include references:
   - src/master_object.h:4:#include "compiler.h"
   - src/compile_stubs.c:9:#include "compiler.h"
   - src/driver.c:44:#include "compiler.h"
   - src/compiler.c:1:#include "compiler.h"
   - src/program.h:4:#include "compiler.h"
   - src/simul_efun.h:4:#include "compiler.h"
   - src/program_loader.h:18:#include "compiler.h"
   - src/efun.c:15:#include "compiler.h"

**Status:** ⚠️ NEEDS MANUAL REVIEW (Red)

## 7. death.c
- Canonical: `src/death.c`
- Compare `mud-references/deadsouls/ds3.8.2/lib/domains/campus/room/death.c` -> `src/death.c`
  - Diff (first 20 lines):
    --- src/death.c	2026-02-13 10:44:55.402174536 -0400
    +++ mud-references/deadsouls/ds3.8.2/lib/domains/campus/room/death.c	2009-12-30 05:54:42.000000000 -0400
    @@ -1,96 +1,73 @@
    -#include "chargen.h"
    -#include "session_internal.h"
    -#include "room.h"
    -#include "debug.h"
    -#include <stdio.h>
    -#include <stdlib.h>
    -#include <string.h>
    -
    -/* send_to_player is defined in the UI layer (used across modules) */
    -extern void send_to_player(PlayerSession *session, const char *format, ...);
    -
    -static const char *scar_locations[] = {"left cheek", "right forearm", "chest", "back", "scalp"};
    -static const char *scar_descriptions[] = {"a jagged blade scar", "a burned patch of skin", "a long stitched wound", "a puckered scar", "a crescent-shaped mark"};
    -
    -void add_death_scar(Character *ch) {
    -    if (!ch) return;
    -    if (ch->scar_count >= MAX_SCARS) return;
- Compare `mud-references/deadsouls/ds3.8.2/lib/domains/cave/room/death.c` -> `src/death.c`
  - Diff (first 20 lines):
    --- src/death.c	2026-02-13 10:44:55.402174536 -0400
    +++ mud-references/deadsouls/ds3.8.2/lib/domains/cave/room/death.c	2009-12-30 05:54:34.000000000 -0400
    @@ -1,96 +1,72 @@
    -#include "chargen.h"
    -#include "session_internal.h"
    -#include "room.h"
    -#include "debug.h"
    -#include <stdio.h>
    -#include <stdlib.h>
    -#include <string.h>
    -
    -/* send_to_player is defined in the UI layer (used across modules) */
    -extern void send_to_player(PlayerSession *session, const char *format, ...);
    -
    -static const char *scar_locations[] = {"left cheek", "right forearm", "chest", "back", "scalp"};
    -static const char *scar_descriptions[] = {"a jagged blade scar", "a burned patch of skin", "a long stitched wound", "a puckered scar", "a crescent-shaped mark"};
    -
    -void add_death_scar(Character *ch) {
    -    if (!ch) return;
    -    if (ch->scar_count >= MAX_SCARS) return;
- Compare `mud-references/deadsouls/ds3.8.2/lib/domains/default/room/death.c` -> `src/death.c`
  - Diff (first 20 lines):
    --- src/death.c	2026-02-13 10:44:55.402174536 -0400
    +++ mud-references/deadsouls/ds3.8.2/lib/domains/default/room/death.c	2009-12-30 05:54:38.000000000 -0400
    @@ -1,96 +1,73 @@
    -#include "chargen.h"
    -#include "session_internal.h"
    -#include "room.h"
    -#include "debug.h"
    -#include <stdio.h>
    -#include <stdlib.h>
    -#include <string.h>
    -
    -/* send_to_player is defined in the UI layer (used across modules) */
    -extern void send_to_player(PlayerSession *session, const char *format, ...);
    -
    -static const char *scar_locations[] = {"left cheek", "right forearm", "chest", "back", "scalp"};
    -static const char *scar_descriptions[] = {"a jagged blade scar", "a burned patch of skin", "a long stitched wound", "a puckered scar", "a crescent-shaped mark"};
    -
    -void add_death_scar(Character *ch) {
    -    if (!ch) return;
    -    if (ch->scar_count >= MAX_SCARS) return;
- Compare `mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/death.c` -> `src/death.c`
  - Diff (first 20 lines):
    --- src/death.c	2026-02-13 10:44:55.402174536 -0400
    +++ mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/death.c	2011-08-24 22:16:32.000000000 -0300
    @@ -1,96 +1,73 @@
    -#include "chargen.h"
    -#include "session_internal.h"
    -#include "room.h"
    -#include "debug.h"
    -#include <stdio.h>
    -#include <stdlib.h>
    -#include <string.h>
    -
    -/* send_to_player is defined in the UI layer (used across modules) */
    -extern void send_to_player(PlayerSession *session, const char *format, ...);
    -
    -static const char *scar_locations[] = {"left cheek", "right forearm", "chest", "back", "scalp"};
    -static const char *scar_descriptions[] = {"a jagged blade scar", "a burned patch of skin", "a long stitched wound", "a puckered scar", "a crescent-shaped mark"};
    -
    -void add_death_scar(Character *ch) {
    -    if (!ch) return;
    -    if (ch->scar_count >= MAX_SCARS) return;
- Compare `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/death.c` -> `src/death.c`
  - Diff (first 20 lines):
    --- src/death.c	2026-02-13 10:44:55.402174536 -0400
    +++ mud-references/deadsouls/ds3.8.2/lib/domains/town/room/death.c	2009-12-30 05:54:56.000000000 -0400
    @@ -1,96 +1,72 @@
    -#include "chargen.h"
    -#include "session_internal.h"
    -#include "room.h"
    -#include "debug.h"
    -#include <stdio.h>
    -#include <stdlib.h>
    -#include <string.h>
    -
    -/* send_to_player is defined in the UI layer (used across modules) */
    -extern void send_to_player(PlayerSession *session, const char *format, ...);
    -
    -static const char *scar_locations[] = {"left cheek", "right forearm", "chest", "back", "scalp"};
    -static const char *scar_descriptions[] = {"a jagged blade scar", "a burned patch of skin", "a long stitched wound", "a puckered scar", "a crescent-shaped mark"};
    -
    -void add_death_scar(Character *ch) {
    -    if (!ch) return;
    -    if (ch->scar_count >= MAX_SCARS) return;
- Compare `mud-references/deadsouls/ds3.8.2/lib/std/death.c` -> `src/death.c`
  - Diff (first 20 lines):
    --- src/death.c	2026-02-13 10:44:55.402174536 -0400
    +++ mud-references/deadsouls/ds3.8.2/lib/std/death.c	2009-12-30 05:54:20.000000000 -0400
    @@ -1,96 +1,73 @@
    -#include "chargen.h"
    -#include "session_internal.h"
    -#include "room.h"
    -#include "debug.h"
    -#include <stdio.h>
    -#include <stdlib.h>
    -#include <string.h>
    -
    -/* send_to_player is defined in the UI layer (used across modules) */
    -extern void send_to_player(PlayerSession *session, const char *format, ...);
    -
    -static const char *scar_locations[] = {"left cheek", "right forearm", "chest", "back", "scalp"};
    -static const char *scar_descriptions[] = {"a jagged blade scar", "a burned patch of skin", "a long stitched wound", "a puckered scar", "a crescent-shaped mark"};
    -
    -void add_death_scar(Character *ch) {
    -    if (!ch) return;
    -    if (ch->scar_count >= MAX_SCARS) return;
 - References in `Makefile`:
   - 50:			  $(SRC_DIR)/ui_frames.c $(SRC_DIR)/death.c $(SRC_DIR)/npc.c

**Status:** ⚠️ NEEDS MANUAL REVIEW (Red)

## 8. debug.h
- Canonical: `src/debug.h`
- Compare `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/debug.h` -> `src/debug.h`
  - Diff (first 20 lines):
    --- src/debug.h	2026-02-05 13:29:29.583783839 -0400
    +++ mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/debug.h	2011-07-25 18:02:50.000000000 -0300
    @@ -1,80 +1,43 @@
    -#ifndef AMLP_DEBUG_H
    -#define AMLP_DEBUG_H
    +/* debug.h: added by Truilkan: 92/02/08 */
     
    -#include <stdlib.h>
    -#include <stdio.h>
    -#include <string.h>
    -
    -#ifdef __cplusplus
    -extern "C" {
    +/* this include file adds some nice debugging capabilities.  You can
    +   use -DDEBUG_MACRO in CFLAGS in the Makefile to let the debug code
    +   be compiled in.  If DEBUG_MACRO is not defined then the debug code
    +   is removed by the C preprocessor.  The global variable debug_level
    +   is defined in main.c.  The debug_level typically starts out at zero
    +   (0) and slowly grows larger over the life of the program.  The main
    +   advantage to this debug macro is that you can turn various sets of
- Compare `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/debug.h` -> `src/debug.h`
  - Diff (first 20 lines):
    --- src/debug.h	2026-02-05 13:29:29.583783839 -0400
    +++ mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/debug.h	2008-07-19 21:11:24.000000000 -0300
    @@ -1,80 +0,0 @@
    -#ifndef AMLP_DEBUG_H
    -#define AMLP_DEBUG_H
    -
    -#include <stdlib.h>
    -#include <stdio.h>
    -#include <string.h>
    -
    -#ifdef __cplusplus
    -extern "C" {
    -#endif
    -
    -/* Debug output control
    - * Can be enabled via:
    - * 1. Environment variable: export AMLP_DEBUG=1
    - * 2. Compile flag: gcc -DAMLP_DEBUG_ENABLED
    - */
    -
- Compare `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/i3router/debug.h` -> `src/debug.h`
  - Diff (first 20 lines):
    --- src/debug.h	2026-02-05 13:29:29.583783839 -0400
    +++ mud-references/deadsouls/ds3.8.2/lib/secure/daemon/i3router/debug.h	2010-06-15 20:26:02.000000000 -0300
    @@ -1,80 +1,24 @@
    -#ifndef AMLP_DEBUG_H
    -#define AMLP_DEBUG_H
    +// This file written mostly by Tim Johnson (Tim@TimMUD)
     
    -#include <stdlib.h>
    -#include <stdio.h>
    -#include <string.h>
    -
    -#ifdef __cplusplus
    -extern "C" {
    -#endif
    -
    -/* Debug output control
    - * Can be enabled via:
    - * 1. Environment variable: export AMLP_DEBUG=1
    - * 2. Compile flag: gcc -DAMLP_DEBUG_ENABLED
    - */
 - #include references:
   - src/death.c:4:#include "debug.h"
   - src/driver.c:47:#include "debug.h"
   - src/item.c:4:#include "debug.h"
   - src/chargen.c:14:#include "debug.h"
   - src/object.c:12:#include "debug.h"
   - src/skills.c:8:#include "debug.h"
   - src/efun.c:11:#include "debug.h"
   - src/vm.c:14:#include "debug.h"

**Status:** ⚠️ NEEDS MANUAL REVIEW (Red)

## 9. item.c
- Canonical: `src/item.c`
- Compare `mud-references/deadsouls/ds3.8.2/lib/lib/std/item.c` -> `src/item.c`
  - Diff (first 20 lines):
    --- src/item.c	2026-02-13 08:13:09.034697790 -0400
    +++ mud-references/deadsouls/ds3.8.2/lib/lib/std/item.c	2009-12-30 05:54:58.000000000 -0400
    @@ -1,851 +1,377 @@
    -#include "item.h"
    -#include "chargen.h"
    -#include "session_internal.h"
    -#include "debug.h"
    -#include <stdio.h>
    -#include <stdlib.h>
    -#include <string.h>
    -#include <ctype.h>
    -#include <strings.h>
    -
    -/* External function declaration */
    -extern void send_to_player(PlayerSession *sess, const char *fmt, ...);
    -
    -/* Item Template Database */
    -Item ITEM_TEMPLATES[TOTAL_ITEM_TEMPLATES];
    -
    -/* Initialize item system and database */
 - References in `Makefile`:
   - 48:			  $(SRC_DIR)/combat.c $(SRC_DIR)/item.c $(SRC_DIR)/psionics.c \

**Status:** ⚠️ NEEDS MANUAL REVIEW (Red)

## 10. item.h
- Canonical: `src/item.h`
- Compare `mud-references/deadsouls/ds3.8.2/lib/lib/include/item.h` -> `src/item.h`
  - Diff (first 20 lines):
    --- src/item.h	2026-02-13 07:01:33.803631768 -0400
    +++ mud-references/deadsouls/ds3.8.2/lib/lib/include/item.h	2006-07-04 21:01:06.000000000 -0300
    @@ -1,128 +1,52 @@
    -#ifndef ITEM_H
    -#define ITEM_H
    +#ifndef l_item_h
    +#define l_item_h
     
    -#include <stdbool.h>
    -#include <stddef.h>  // For size_t
    +static void create();
    +static void init();
    +varargs void reset(int count);
    +mixed direct_bury_obj_with_obj();
    +mixed indirect_give_liv_obj(object target);
    +mixed direct_give_obj_to_liv();
    +mixed direct_look_at_obj(string id);
    +mixed direct_look_at_obj_word_obj(string my_id, string id);
    +mixed direct_poison_obj_with_obj();
    +
 - #include references:
   - src/room.c:3:#include "item.h"
   - src/driver.c:50:#include "item.h"
   - src/chargen.h:5:#include "item.h"
   - src/item.c:1:#include "item.h"
   - src/combat.c:5:#include "item.h"
   - src/wiz_tools.c:21:#include "item.h"
   - src/room.h:6:#include "item.h"

**Status:** ⚠️ NEEDS MANUAL REVIEW (Red)

## 11. magic.c
- Canonical: `src/magic.c`
- Compare `mud-references/deadsouls/ds3.8.2/lib/lib/magic.c` -> `src/magic.c`
  - Diff (first 20 lines):
    --- src/magic.c	2026-02-15 23:41:08.683779479 -0400
    +++ mud-references/deadsouls/ds3.8.2/lib/lib/magic.c	2009-12-30 05:55:02.000000000 -0400
    @@ -1,1038 +1,194 @@
    -#include "magic.h"
    -#include "chargen.h"
    -#include "session_internal.h"
    -#include "room.h"
    -#include "npc.h"
    -#include "vm.h"
    -#include "object.h"
    -#include "efun.h"
    -#include <stdlib.h>
    -#include <string.h>
    -#include <stdio.h>
    -#include <ctype.h>
    +/*    /lib/magic.c
    + *    From Dead Souls LPMud
    + *    A module for allowing living beings to cast magic spells.
    + *    Created by Descartes of Borg 961027
    + *    Version: @(#) magic.c 1.13@(#)
 - References in `Makefile`:
   - 49:			  $(SRC_DIR)/magic.c $(SRC_DIR)/wiz_tools.c $(SRC_DIR)/race_loader.c \

**Status:** ⚠️ NEEDS MANUAL REVIEW (Red)

## 12. magic.h
- Canonical: `src/magic.h`
- Compare `mud-references/deadsouls/ds3.8.2/lib/include/magic.h` -> `src/magic.h`
  - Diff (first 20 lines):
    --- src/magic.h	2026-02-15 23:41:04.607781138 -0400
    +++ mud-references/deadsouls/ds3.8.2/lib/include/magic.h	2006-07-04 21:00:58.000000000 -0300
    @@ -1,125 +1,12 @@
    -#ifndef MAGIC_H
    -#define MAGIC_H
    +#ifndef s_magic_h
    +#define s_magic_h
     
    -#include <stdbool.h>
    -#include <time.h>
    +#define SPELL_HEALING       1
    +#define SPELL_DEFENSE       2
    +#define SPELL_COMBAT        3
    +#define SPELL_OTHER         4
     
    -/* Forward declarations */
    -typedef struct PlayerSession PlayerSession;
    -typedef struct NPC NPC;
    -struct Character;
    +#endif // s_magic_h
 - #include references:
   - src/driver.c:52:#include "magic.h"
   - src/chargen.h:7:#include "magic.h"
   - src/magic.c:1:#include "magic.h"

**Status:** ⚠️ NEEDS MANUAL REVIEW (Red)

## 13. mapping.c
- Canonical: `src/mapping.c`
- Compare `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/mapping.c` -> `src/mapping.c`
  - Diff (first 20 lines):
    --- src/mapping.c	2026-02-05 13:29:29.583783839 -0400
    +++ mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/mapping.c	2011-07-25 18:02:52.000000000 -0300
    @@ -1,172 +1,1324 @@
    -#include "mapping.h"
    -#include <stdlib.h>
    -#include <string.h>
    +/* 92/04/18 - cleaned up in accordance with ./src/style.guidelines */
     
    -static unsigned int map_hash(const char *key, size_t capacity) {
    -    unsigned int hash = 0;
    -    for (const char *p = key; *p; ++p) {
    -        hash = ((hash << 5) + hash) ^ (unsigned char)(*p);
    +#include "std.h"
    +#include "config.h"
    +#include "lpc_incl.h"
    +#include "md.h"
    +#include "efun_protos.h"
    +
    +int num_mappings = 0;
    +int total_mapping_size = 0;
- Compare `mud-references/deadsouls/ds3.8.2/lib/secure/modules/mapping.c` -> `src/mapping.c`
  - Diff (first 20 lines):
    --- src/mapping.c	2026-02-05 13:29:29.583783839 -0400
    +++ mud-references/deadsouls/ds3.8.2/lib/secure/modules/mapping.c	2009-12-30 05:54:28.000000000 -0400
    @@ -1,172 +1,348 @@
    -#include "mapping.h"
    -#include <stdlib.h>
    -#include <string.h>
    -
    -static unsigned int map_hash(const char *key, size_t capacity) {
    -    unsigned int hash = 0;
    -    for (const char *p = key; *p; ++p) {
    -        hash = ((hash << 5) + hash) ^ (unsigned char)(*p);
    +#include <lib.h>
    +#include <daemons.h>
    +#include <modules.h>
    +
    +string globaltmp, globalstr, globalstr2, func, data, temporary;
    +int automated;
    +object target;
    +mixed newval;
    +
 - References in `Makefile`:
   - 22:                      $(SRC_DIR)/mapping.c \
   - 42:              $(SRC_DIR)/mapping.c $(SRC_DIR)/compiler.c $(SRC_DIR)/program.c \
   - 176:	@for t in lexer parser vm object gc efun array mapping compiler program simul_efun vm_execution; do \

**Status:** ⚠️ NEEDS MANUAL REVIEW (Red)

## 14. mapping.h
- Canonical: `src/mapping.h`
- Compare `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/mapping.h` -> `src/mapping.h`
  - Diff (first 20 lines):
    --- src/mapping.h	2026-02-05 13:29:29.583783839 -0400
    +++ mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/mapping.h	2011-07-25 18:02:52.000000000 -0300
    @@ -1,32 +1,129 @@
    -#ifndef MAPPING_H
    -#define MAPPING_H
    +/* mapping.h - 1992/07/19 */
     
    -#include <stddef.h>
    -#include "gc.h"
    -#include "vm.h"
    -#include "array.h"
    -
    -typedef struct mapping_entry_t {
    -    char *key;
    -    VMValue value;
    -    struct mapping_entry_t *next;
    -} mapping_entry_t;
    -
    -typedef struct mapping_t {
    -    GC *gc;
 - #include references:
   - src/mapping.c:1:#include "mapping.h"
   - src/efun.c:13:#include "mapping.h"
   - src/vm.c:20:#include "mapping.h"
   - src/efun.h:16:#include "mapping.h"

**Status:** ⚠️ NEEDS MANUAL REVIEW (Red)

## 15. npc.c
- Canonical: `src/npc.c`
- Compare `mud-references/deadsouls/ds3.8.2/lib/lib/npc.c` -> `src/npc.c`
  - Diff (first 20 lines):
    --- src/npc.c	2026-02-15 23:50:55.955551607 -0400
    +++ mud-references/deadsouls/ds3.8.2/lib/lib/npc.c	2010-12-26 09:00:14.000000000 -0400
    @@ -1,449 +1,691 @@
    -/* npc.c - NPC/mob spawning, AI, and combat integration */
    +/*    /lib/npc.c
    + *    from the Dead Souls LPC Library
    + *    the standard non-player character object
    + *    created by Descartes of Borg 950323
    + *    Version: @(#) npc.c 1.11@(#)
    + *    Last Modified: 96/12/21
    + */
    +
    +#include <lib.h>
    +#include ROOMS_H
    +#include <daemons.h>
    +#include <position.h>
    +#include <armor_types.h>
    +#include <message_class.h>
    +#include <vision.h>
    +#include "include/npc.h"
- Compare `mud-references/deadsouls/ds3.8.2/lib/obj/npc.c` -> `src/npc.c`
  - Diff (first 20 lines):
    --- src/npc.c	2026-02-15 23:50:55.955551607 -0400
    +++ mud-references/deadsouls/ds3.8.2/lib/obj/npc.c	2009-12-30 05:54:32.000000000 -0400
    @@ -1,449 +1,19 @@
    -/* npc.c - NPC/mob spawning, AI, and combat integration */
    +#include <lib.h>
     
    -#include "npc.h"
    -#include "combat.h"
    -#include "room.h"
    -#include "session_internal.h"
    -#include "race_loader.h"
    -#include <stdlib.h>
    -#include <string.h>
    -#include <stdio.h>
    -#include <ctype.h>
    +inherit LIB_SENTIENT;
     
    -/* External */
    -extern void send_to_player(PlayerSession *session, const char *format, ...);
    -
 - References in `Makefile`:
   - 50:			  $(SRC_DIR)/ui_frames.c $(SRC_DIR)/death.c $(SRC_DIR)/npc.c

**Status:** ⚠️ NEEDS MANUAL REVIEW (Red)

## 16. npc.h
- Canonical: `src/npc.h`
- Compare `mud-references/deadsouls/ds3.8.2/lib/lib/include/npc.h` -> `src/npc.h`
  - Diff (first 20 lines):
    --- src/npc.h	2026-02-15 23:31:34.208005637 -0400
    +++ mud-references/deadsouls/ds3.8.2/lib/lib/include/npc.h	2006-07-04 21:01:06.000000000 -0300
    @@ -1,94 +1,72 @@
    -/* npc.h - NPC/mob system for spawnable creatures */
    +#ifndef l_npc_h
    +#define l_npc_h
     
    -#ifndef NPC_H
    -#define NPC_H
    +static void create();
    +static void init();
    +static void heart_beat();
    +void receive_message(string cl, string msg);
    +void catch_tell(string msg);
    +void restart_heart();
    +int is_living();
    +int inventory_accessible();
    +int inventory_visible();
    +
    +int cmdListen(string str);
 - #include references:
   - src/room.c:2:#include "npc.h"
   - src/driver.c:59:#include "npc.h"
   - src/combat.c:2:#include "npc.h"
   - src/chargen.c:4:#include "npc.h"
   - src/magic.c:5:#include "npc.h"
   - src/npc.c:3:#include "npc.h"

**Status:** ⚠️ NEEDS MANUAL REVIEW (Red)

## 17. object.c
- Canonical: `src/object.c`
- Compare `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/object.c` -> `src/object.c`
  - Diff (first 20 lines):
    --- src/object.c	2026-02-07 20:23:43.834132045 -0400
    +++ mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/object.c	2011-07-25 18:02:52.000000000 -0300
    @@ -1,535 +1,2195 @@
    -/**
    - * object.c - LPC Object System Implementation
    - * 
    - * Implements the object type system for the AMLP LPC driver.
    - * Provides object creation, property/method management, and inheritance.
    - * 
    - * Phase 4 Implementation - January 22, 2026
    - */
    +#include "std.h"
    +#include "lpc_incl.h"
    +#include "file_incl.h"
    +#include "otable.h"
    +#include "backend.h"
    +#include "comm.h"
    +#include "socket_efuns.h"
    +#include "call_out.h"
    +#include "port.h"
- Compare `mud-references/deadsouls/ds3.8.2/lib/lib/comp/object.c` -> `src/object.c`
  - Diff (first 20 lines):
    --- src/object.c	2026-02-07 20:23:43.834132045 -0400
    +++ mud-references/deadsouls/ds3.8.2/lib/lib/comp/object.c	2009-12-30 05:55:00.000000000 -0400
    @@ -1,535 +1,52 @@
    -/**
    - * object.c - LPC Object System Implementation
    - * 
    - * Implements the object type system for the AMLP LPC driver.
    - * Provides object creation, property/method management, and inheritance.
    - * 
    - * Phase 4 Implementation - January 22, 2026
    +/*    /lib/comp/object.c
    + *    From the Dead Souls LPC Library
    + *    Object inherited by all tangible objects (ones with environments)
    + *    Created by Descartes of Borg 940211
    + *    Version: @(#) object.c 1.10@(#)
    + *    Last Modified: 96/12/22
      */
     
    -#include "object.h"
    -#include "vm.h"
 - References in `Makefile`:
   - 19:                      $(SRC_DIR)/object.c \
   - 30:                      $(SRC_DIR)/master_object.c \
   - 39:              $(SRC_DIR)/vm.c $(SRC_DIR)/codegen.c $(SRC_DIR)/object.c \
   - 45:              $(SRC_DIR)/master_object.c $(SRC_DIR)/terminal_ui.c \

**Status:** ⚠️ NEEDS MANUAL REVIEW (Red)

## 18. object.h
- Canonical: `src/object.h`
- Compare `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/object.h` -> `src/object.h`
  - Diff (first 20 lines):
    --- src/object.h	2026-02-05 13:29:29.583783839 -0400
    +++ mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/object.h	2011-07-25 18:02:52.000000000 -0300
    @@ -1,288 +1,193 @@
    -/**
    - * object.h - LPC Object System Header
    - * 
    - * Defines the object type system for the AMLP LPC driver.
    - * Objects are the fundamental building blocks of LPC programs:
    - * - Have properties (data members stored in hash map)
    - * - Have methods (functions defined in the object)
    - * - Support inheritance (prototype chain)
    - * - Can be instantiated/cloned
    - * 
    - * Architecture:
    - *   obj_t: Core object structure
    - *   - name: Object identifier
    - *   - proto: Prototype (parent) for inheritance
    - *   - properties: Hash map of property name -> VMValue
    - *   - methods: Array of functions defined in this object
    - * 
- Compare `mud-references/deadsouls/ds3.8.2/lib/secure/include/object.h` -> `src/object.h`
  - Diff (first 20 lines):
    --- src/object.h	2026-02-05 13:29:29.583783839 -0400
    +++ mud-references/deadsouls/ds3.8.2/lib/secure/include/object.h	2006-07-04 21:01:06.000000000 -0300
    @@ -1,288 +1,4 @@
    -/**
    - * object.h - LPC Object System Header
    - * 
    - * Defines the object type system for the AMLP LPC driver.
    - * Objects are the fundamental building blocks of LPC programs:
    - * - Have properties (data members stored in hash map)
    - * - Have methods (functions defined in the object)
    - * - Support inheritance (prototype chain)
    - * - Can be instantiated/cloned
    - * 
    - * Architecture:
    - *   obj_t: Core object structure
    - *   - name: Object identifier
    - *   - proto: Prototype (parent) for inheritance
    - *   - properties: Hash map of property name -> VMValue
    - *   - methods: Array of functions defined in this object
    - * 
 - #include references:
   - src/driver.c:45:#include "master_object.h"
   - src/driver.c:55:#include "object.h"
   - src/master_object.c:1:#include "master_object.h"
   - src/wiz_tools.c:20:#include "object.h"
   - src/object.c:10:#include "object.h"
   - src/efun.c:14:#include "object.h"
   - src/efun.c:17:#include "object.h"
   - src/magic.c:7:#include "object.h"
   - src/vm.c:13:#include "object.h"

**Status:** ⚠️ NEEDS MANUAL REVIEW (Red)

## 19. parser.c
- Canonical: `src/parser.c`
- Compare `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/parser.c` -> `src/parser.c`
  - Diff (first 20 lines):
    --- src/parser.c	2026-02-09 12:57:37.885910197 -0400
    +++ mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/parser.c	2009-09-13 18:39:38.000000000 -0300
    @@ -1,1615 +1,3457 @@
     /*
    - * parser.c - Parser Implementation
    - * 
    - * This file implements a recursive descent parser for LPC source code.
    - * It consumes tokens from the lexer and builds an Abstract Syntax Tree (AST).
    + *  Parsing efuns.  Many of the concepts and algorithms here are stolen from
    + *  an earlier LPC parser written by Rust@ZorkMUD.
    + */
    +/*
    + * TODO:
    + * . he, she, it, him, her, them -> "look at tempress.  get sword.  kill her with it"
    + * . compound input -> "n. e then s."
    + * . OBS: and, all and everything (all [of] X, X except [for] Y, X and Y)
    + * . OBS in OBS
    + * . possesive: my his her its their Beek's
    + * . one, two, ...
    + * . questions.  'Take what?'
 - References in `Makefile`:
   - 33:                      $(SRC_DIR)/parser.c \
   - 38:DRIVER_SRCS = $(SRC_DIR)/driver.c $(SRC_DIR)/server.c $(SRC_DIR)/lexer.c $(SRC_DIR)/parser.c \

**Status:** ⚠️ NEEDS MANUAL REVIEW (Red)

## 20. parser.h
- Canonical: `src/parser.h`
- Compare `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/parser.h` -> `src/parser.h`
  - Diff (first 20 lines):
    --- src/parser.h	2026-02-09 12:48:33.926094193 -0400
    +++ mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/parser.h	2008-07-19 21:11:24.000000000 -0300
    @@ -1,326 +1,235 @@
    -/*
    - * parser.h - Parser Header
    - * 
    - * This header defines the Abstract Syntax Tree (AST) node structures
    - * and the Parser API for parsing LPC source code into an AST.
    - */
    -
    -#ifndef PARSER_H
    -#define PARSER_H
    +#ifndef ZORKPARSE_H
    +#define ZORKPARSE_H
     
    -#include "lexer.h"
    +#include "../include/parser_error.h"
     
    -/* ========== AST Node Type Enumeration ========== */
    +/* Token convention:
 - #include references:
   - src/compiler.c:3:#include "parser.h"
   - src/codegen.h:17:#include "parser.h"
   - src/parser.c:10:#include "parser.h"
   - src/vm.h:16:#include "parser.h"

**Status:** ⚠️ NEEDS MANUAL REVIEW (Red)

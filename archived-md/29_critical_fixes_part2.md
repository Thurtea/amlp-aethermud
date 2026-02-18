# Critical Fixes — Part 2

Date: 2026-02-16

This file records exact locations and diffs for the changes applied in this work session.

Files changed
- `src/chargen.c` — removed in-chargen O.C.C. selection and added `any_saved_players()` helper
- `src/chargen.h` — removed `CHARGEN_OCC_SELECT` enum entry; added prototype `int any_saved_players(void);`
- `src/driver.c` — adjusted first-player admin promotion to check for existing save files
- `lib/cmds/selectocc.lpc` (new) — in-game post-login O.C.C. selection command
- `lib/data/help/systems/selectocc.txt` (new) — help topic for `selectocc`
- `lib/obj/wiztools/crystal.lpc`, `handbook.lpc`, `staff.lpc` — small keyword additions

1) src/chargen.c

Exact pre-change locations (original file lines):
- `case CHARGEN_OCC_SELECT:` began at line 923
- `case CHARGEN_STATS_CONFIRM:` began at line 1002
- Save/load helper area began around line 1271 (helper inserted nearby).

Summary of change:
- Removed the CHARGEN_OCC_SELECT case (UI and selection logic) so the C-side chargen no longer forces O.C.C. selection.
- Added a helper function `any_saved_players()` that scans `lib/save/players` for `*.dat` files and returns 1 if any exist.

Diff summary (human-readable):
  - Removed block: approx lines 923-1001 (pagination + OCC choice UI and transition to CHARGEN_STATS_CONFIRM).
  - Added block (helper) at the save/load area:

      int any_saved_players(void) {
          DIR *dir = opendir("lib/save/players");
          if (!dir) return 0;
          struct dirent *entry;
          while ((entry = readdir(dir)) != NULL) {
              const char *dot = strrchr(entry->d_name, '.');
              if (!dot) continue;
              if (strcmp(dot, ".dat") == 0) {
                  closedir(dir);
                  return 1;
              }
          }
          closedir(dir);
          return 0;
      }

2) src/chargen.h

Exact pre-change note: `ChargenState` enum contained `CHARGEN_OCC_SELECT` after `CHARGEN_RACE_SELECT`.

What changed:
- Removed `CHARGEN_OCC_SELECT` from the enum.
- Added prototype: `int any_saved_players(void);`

Representation of the change:
  *Before* (enum excerpt):
      CHARGEN_INIT = 0,
      CHARGEN_RACE_SELECT,
      CHARGEN_OCC_SELECT,
      CHARGEN_STATS_ROLL,
  *After*:
      CHARGEN_INIT = 0,
      CHARGEN_RACE_SELECT,
      CHARGEN_STATS_ROLL,
      CHARGEN_STATS_CONFIRM,
      CHARGEN_ALIGNMENT_SELECT,

And appended prototype:
  int any_saved_players(void);

3) src/driver.c

Exact pre-change location: first-player admin branch around original line ~4240.

What changed:
- Previously: the code promoted the first-created (in-memory flag) player to admin solely based on `first_player_created` being false.
- Now: it promotes only if `first_player_created` is false AND `any_saved_players()` returns false — preserving expected behavior across restores/imports.

Human-readable change:
  - Old behavior: if (!first_player_created) { promotetoadmin... }
  - New behavior: if (!first_player_created && !any_saved_players()) { promotetoadmin... }

4) lib/cmds/selectocc.lpc (NEW)

File added to allow post-login O.C.C. selection. Full contents (copied from workspace):

    /* selectocc - allow a logged-in player to choose their O.C.C. */
    inherit "/cmds/base_command";

    int cmd(string arg) {
        object me = this_player();
        if (!me) return notify_fail("No player context.\n");
        if (!arg || arg == "") return notify_fail("Usage: selectocc <occ_id>\n");

        if (me->query_occ_id()) {
            write("You have already selected an O.C.C.\n");
            return 1;
        }

        string occ_path = "/occs/" + arg + ".c";
        if (!file_exists(occ_path)) {
            write("No such O.C.C.: " + arg + "\n");
            return 1;
        }

        object occ = load_object(occ_path);
        if (!occ) {
            write("Unable to load that O.C.C. right now.\n");
            return 1;
        }

        if (functionp(occ->race_can_select) && !occ->race_can_select(me->query_race())) {
            write("Your race cannot select that O.C.C.\n");
            return 1;
        }

        if (functionp(occ->meets_stat_requirements) && !occ->meets_stat_requirements(me)) {
            write("You do not meet the stat requirements for that O.C.C.\n");
            return 1;
        }

        me->set_occ_id(arg);
        if (functionp(occ->apply_to_player)) occ->apply_to_player(me);

        if (arrayp(occ->primary_skills())) {
            foreach(string sk in occ->primary_skills()) {
                me->add_skill(sk, 1);
            }
        }

        me->save_player();
        write("O.C.C. '" + arg + "' selected and applied. Your character has been saved.\n");
        return 1;
    }

    string help() {
        return "Usage: selectocc <occ_id>\nSelect an O.C.C. for your character after creation.\n";
    }

5) lib/data/help/systems/selectocc.txt (NEW)

Contents (copied into workspace):

    SelectOCC
    =========

    Syntax: selectocc <occ_id>

    Allows a newly-created character to choose an O.C.C. (occupational class) after logging in. Use the O.C.C. ID (the file name in /occs without extension). This command validates race compatibility and stat requirements, applies O.C.C. benefits, and saves your character.

    Examples:
      selectocc warrior
      selectocc mystic

    Notes:
    - You can only select an O.C.C. once; contact staff if you need a reset.
    - If you get an error, ensure the O.C.C. file exists and is compatible with your race.

6) lib/obj/wiztools keyword additions

What changed: three wiztool files had a small `keywords` array added to improve object lookup:

    crystal.lpc:  string *keywords = ({ "crystal", "viewing crystal" });
    handbook.lpc: string *keywords = ({ "handbook", "wizard's handbook" });
    staff.lpc:    string *keywords = ({ "staff", "wizard's staff" });

Rationale summary
- Moving optional choices (like O.C.C.) into LPC lets the mudlib perform richer validation (race, stats, special rules) and keeps the C driver focused on the minimal login/character-creation flow.
- Checking for persisted save files prevents accidental admin grants when the server is restored or migrated.

Next steps you might want:
- Run a build/compile to verify the C changes (I can run `make` / `gcc` if you want).
- Review any specific file's exact context or ask me to produce a smaller, true unified patch for `git apply` if needed.

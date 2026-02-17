**Get/Drop "all" Implementation Analysis**

- **Current command locations**
  - `lib/cmds/get.lpc`
  - `lib/cmds/drop.lpc`

- **Does "all" already exist?**
  - Yes. Both `get.lpc` and `drop.lpc` contain explicit handling for the literal `"all"` argument and provide user feedback. `get.lpc` loops room inventory and attempts to pick up non-living, gettable objects; `drop.lpc` loops the player's inventory and moves items to the room.

- **Observed behavior summary**
  - `get all`:
    - Collects `all_inventory(room)` and for each non-living object that exposes a `get` function, calls `obj->get(user)` and counts successes.
    - Skips living things.
    - Respects objects that implement `get()`; uses `query_no_get()` check for specific items elsewhere.
    - Emits summary message showing number of items picked up.
  - `drop all`:
    - Iterates `all_inventory(user)` and moves each object to the room (using `move` if available), counting total moved.
    - Does not check `query_no_drop()` for each object when dropping all (note: individual `drop` path checks `query_no_drop` — see below).

- **Edge cases / gaps to consider (recommended improvements)**
  - `get all` currently uses `function_exists("get", obj)` and `obj->get(user)` — ensure consistent semantics: many objects use move()/query_no_get() instead of `get()`; prefer checking `query_no_get()` and attempting a standard move to player when permitted.
  - `get all` should respect weight limits incrementally: currently it checks per-item weight only when picking a single named item; for `get all` it should stop when the player reaches carry limit and report how many were picked.
  - `drop all` currently moves all inventory items without checking `query_no_drop()`; this may allow dropping protected/quest items. Update `drop all` to skip items that return true from `query_no_drop()` and notify the user which items were not dropped.
  - Both commands should avoid dropping/moving sensitive control objects (player body, living puppets, equipped/worn items if intended) — consider skipping items flagged as `worn` or `wielded` (or check `query_worn()`/`query_wielded()` if present).

- **Pseudocode for a robust `get all` implementation**

  - For each candidate in `all_inventory(room)` ordered by sensible priority:
    - If `living(candidate)`: continue
    - If `candidate->query_no_get()` truthy: continue
    - If candidate is not visible to `viewer` (e.g., invisibility): continue
    - item_weight = candidate->query_weight() or 0
    - if current_carry + item_weight > viewer->query_max_carry_weight(): stop (or continue but report)
    - if candidate has `get()` and calling it returns truthy: count++ and continue
    - else attempt to move candidate to viewer (use `candidate->move(viewer)` if available, else `move_object`), and count on success
    - report per-item failures optionally to the player

- **Pseudocode for a safer `drop all` implementation**

  - For each item in `all_inventory(player)`:
    - If `item->query_no_drop()` truthy: skip and record for report
    - If `item->query_worn()` or `item->query_wielded()` truthy: skip (or attempt to unwield/unwear if intended)
    - Attempt to move item to room (use `item->move(room)` or `move_object`); on success count++
    - After loop, show summary and list skipped items with reasons

- **Files likely needing modification to harden behavior**
  - `lib/cmds/get.lpc` — refine `all` loop to use `query_no_get()`, weight checks, visibility, and fallback moves.
  - `lib/cmds/drop.lpc` — refine `all` loop to skip `query_no_drop()` and respect equipped state.
  - `lib/std/living.lpc` or `lib/std/object.lpc` (if present) — consider adding helper hooks such as `CanBePickedUp(object who)` or `CanBeDropped(object who)` to centralize checks and avoid duplicating logic across commands.
  - Tests: `tests/commands/test_get_drop_all.*` (create new test files) to validate behavior for normal items, heavy items, non-droppable items, worn/wielded items, and items with custom `get()` behavior.

- **Quick implementation plan**
  1. Create unit/manual tests describing expected behavior in edge cases.
  2. Update `lib/cmds/get.lpc` with incremental weight checks and unified `CanBePickedUp()` helper usage.
  3. Update `lib/cmds/drop.lpc` to skip `query_no_drop()` and respect equipped state.
  4. Add helper functions to `lib/std/*` if repeated logic emerges.
  5. Run build and smoke tests, then restart server and verify in-game.

No files were modified by this analysis. If you want, I can implement the safer behavior in a small patch and run the build/tests next.

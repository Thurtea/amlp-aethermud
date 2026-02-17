**Staff Castle — Status Report**

Generated: 2026-02-16

**1) Files discovered**
- `lib/domains/staff_castle/npc/spike.lpc`
- Rooms (all under `lib/domains/staff_castle/room/`):
  - `courtyard.lpc`
  - `main_hall.lpc`
  - `stairs.lpc`
  - `upper_hall.lpc`
  - `throne_room.lpc`
  - `dining_hall.lpc`
  - `kitchen.lpc`
  - `library.lpc`
  - `observatory.lpc`
  - `war_room.lpc`
  - `stables.lpc`
  - `garden.lpc`
  - `hedge_maze.lpc`
  - `maze_center.lpc`
  - `maze_west.lpc`
  - `maze_east.lpc`

**2) Spike NPC — quick code inspection**
- Location: `lib/domains/staff_castle/npc/spike.lpc` (file exists and is readable).
- Spike is spawned in `courtyard.lpc` via `new("/domains/staff_castle/npc/spike")->move(this_object());` inside `setup()`.
- The NPC defines behavior: `create()`, `init()` (adds player-facing actions), `heart_beat()`, and several action handlers: `pet_spike`, `talk_to_spike`, `feed_spike`, `play_with_spike`, plus `die()` and `query_no_kill()`.

Potential issues / missing/incorrect APIs observed:
- `force_me` usage: the file repeatedly calls `force_me("emote", "<text>")` (e.g. `force_me("emote", "wags his tail happily");`). In this codebase the typical `force_me()` call takes a single command string (e.g. `force_me("emote wags his tail")`). The two-argument form is not used elsewhere and likely causes runtime errors when the heartbeat runs. Fix: change calls to a single string, e.g. `force_me("emote wags his tail happily");` or use `tell_room()`/`this_object()->eventEmote()` depending on driver API.
- `add_action` in NPC `init()`: the NPC installs `add_action("pet_spike", "pet");` etc. This pattern can work (many libs implement `init()` on living objects such that player input can trigger NPC-handlers), but it depends on driver/lib semantics — verify in-game that the player commands reach the NPC functions. If it doesn't work, the usual alternative is to handle interaction via `init()` in the room, or create player-facing command objects under `/cmds/` that detect the target (spike) and forward to the NPC.
- Strict string matching in action handlers: handlers check exact strings (`if (!str || (str != "spike" && str != "dog")) return 0;`). This misses common variants (`the spike`, `at spike`, etc.). Consider using `member_array()` on a normalized token list or parsing with `sscanf()` to accept common natural forms.
- `die()` uses `remove()` — confirm the driver/lib's proper destruct pattern (some use `destruct(this_object())` or `this_object()->remove()`); `remove()` may be fine but check that it doesn't leave residual references.

Conclusion: Spike is largely implemented but likely broken at runtime due to incorrect `force_me` usage and possibly brittle command parsing. Marking status: PARTIALLY BROKEN — needs small API fixes and runtime testing.

**3) Room connectivity (are exits defined?)**
- All rooms under `lib/domains/staff_castle/room/` contain `add_exit(...)` calls; grep shows consistent bi-directional-style links for the main circulation (courtyard <-> main_hall <-> stairs/upper_hall; main_hall <-> throne_room/dining_hall; dining_hall <-> kitchen/library; hedge_maze connections, etc.).
- The courtyard `out` exit points to `/domains/start/room/welcome` which exists.
- No missing target files were found for the `add_exit()` targets within the staff_castle set.

Conclusion: Room graph appears complete and connected. Basic navigation should work (verify in-game to be certain of one-way vs two-way expectations).

**4) TODO / FIXME / error comments**
- No `TODO`, `FIXME`, or `error` comment markers found in `lib/domains/staff_castle/**` files.

**5) What needs to be completed / fixed (actionable list)**
1. Fix `force_me` calls in `lib/domains/staff_castle/npc/spike.lpc` to provide a single command string, or replace with `tell_room()`/API-correct emote functions: change all occurrences like

   - From: `force_me("emote", "wags his tail happily");`
   - To:   `force_me("emote wags his tail happily");`

2. Validate `add_action` semantics for NPC `init()` in this codebase. If player commands are not reaching the NPC handlers, either:
   - Move the action wiring into the room's `init()` so the player receives the command and forwards it to the NPC, or
   - Implement dedicated `/cmds/` player commands that identify the NPC and call a public method on the NPC object.

3. Relax input matching in each handler to accept common variants (use `sscanf`, `explode`, `member_array` or regex-style checks) so commands like `pet the dog`, `talk to spike`, `feed spike with food` behave understandably.

4. Confirm `die()` / `remove()` semantics with driver/lib conventions and ensure Spike is cleaned up properly and respawnable via `courtyard`'s `setup()`.

5. Run an in-server smoke test: start the MUD, go to the courtyard, verify Spike spawns and that the `pet`, `talk`, `feed`, and `play` commands produce expected results and do not crash the driver. Check `lib/log/server.log` for any runtime errors referencing `spike.lpc` (stack traces, runtime errors, or `bad function call` messages).

6. (Optional) Harden action safety: ensure `feed_spike` checks food `query_food()` or `is_food()` to avoid accidental removal of non-food items; avoid `food->remove()` unless intended.

**6) Next steps I can take (if you want me to proceed)**
- Implement the fixes in a small patch branch (fix `force_me` calls + relax handler parsing), run the build, and perform a runtime smoke test.
- If you prefer, I can produce a minimal patch containing only `force_me` fixes first and run the server smoke test.

If you want me to implement changes now, say which fixes to apply first (I recommend `force_me` fixes and a quick parsing relaxation), and I will produce a patch and run build + smoke tests.

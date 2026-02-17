**Room Display Analysis**

- **Files:** [lib/std/room.lpc](lib/std/room.lpc), [lib/cmds/look.lpc](lib/cmds/look.lpc), [lib/std/living.lpc](lib/std/living.lpc), [lib/std/player.lpc](lib/std/player.lpc), [lib/clone/user.lpc](lib/clone/user.lpc)

- **Symptoms:**
  - **Verbose Name:** players in verbose mode sometimes see the room name/short when they should only see the long description.
  - **Missing Articles:** item lines in room listings show capitalized short text without an indefinite article (e.g. "Viewing crystal" instead of "A viewing crystal.").

- **Root Cause (observed):**
  - **Unconditional short/long emission:** `look` code (command and room `look()` implementation) unconditionally appends `query_short()` and `query_long()`; this produces duplicate or unexpected room-name output depending on mode.
  - **Item listing uses raw `query_short()`:** item loops format entries by calling `item->query_short()` then `capitalize(...)` (no article insertion). Living objects have `query_introduction_name()` which can include an article, but ordinary items do not.

- **Proposed changes (analysis-only; no edits applied):**
  - **Respect brief/verbose mode when rendering room header:** modify the `look` command and/or `room->look()` to consult the viewer's brief/verbose setting (e.g. `this_player()->GetBriefMode()` / `GetVerboseMode()`), and only emit `query_short()` when appropriate. Suggested logic: if viewer is in brief mode show `query_short()`; if in verbose mode show `query_long()` (or avoid duplicating the short if `query_long()` already includes the name).
  - **Centralize item rendering with article support:** add a helper (suggested name `render_item_description(object item, object viewer)`) in a common location (e.g., `lib/std/object.c` or `lib/std/living.lpc`) that returns a properly-phrased line. Behavior:
    - If `viewer` requests verbose and item provides a `query_long()`, prefer the long description.
    - If the item is a living, use `query_introduction_name()` (existing) to get article-aware output.
    - Otherwise, if `item->query_short()` lacks an article, prepend an indefinite article inferred from the short (simple vowel rule) or allow objects to provide `query_article()` to override.
    - Return a single string already capitalized and punctuated for the room listing.
  - **Replace inline capitalization calls with helper usage:** update item loops in [lib/std/room.lpc](lib/std/room.lpc) and [lib/cmds/look.lpc](lib/cmds/look.lpc) to call the helper instead of `capitalize(item->query_short())`.

- **Testing plan:**
  - Implement changes in a feature branch.
  - Build (`make`) and restart the driver; run quick smoke tests: `look`, `look <obj>`, walk between rooms with brief/verbose toggles, and verify in-server logs for command handling.
  - Verify living introductions still show articles and that non-living items show the expected indefinite article where appropriate.

- **Risks & notes:**
  - Some area descriptions may expect the old behavior (short + long). Maintain backward compatibility by defaulting to current behavior unless the viewer's mode requests otherwise.
  - The article-inference rule should be conservative; prefer object-provided article hooks when present.

If you'd like, I can implement the changes as a small, test-covered patch in a branch and run the build + smoke tests next. Otherwise this document is ready for review.

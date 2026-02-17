Comparison: /lib/cmds/ls.lpc (top-level) vs /lib/cmds/creator/ls.lpc (creator)

Overview
--------
I compared the two implementations present in the tree. They are different in scope, UX, and expected caller:

1) /lib/cmds/ls.lpc (top-level)
- Purpose: A multi-column `ls` intended for general use (prototype implemented at top-level).
- Features:
  - Flag parsing: supports `-l`, `-a`, `-1`, `-t`, `-r`.
  - Uses efuns `get_dir`, `file_size`, `file_mtime`, `file_mode` (driver efuns added earlier).
  - Multi-column output via `/secure/formatting->format_columns(display, termw)` with fallback simple columns.
  - `-l` long listing prints mode, size, mtime (uses `ctime()`), and appends `/` to directories.
  - Honors terminal width via `query_terminal_width()`.
  - Intended to be usable by creators and possibly players (depends on caller checks).
- Notes:
  - No explicit privilege checks; calls `this_player()` and will run under invoking user context.
  - Well-suited for modern, terminal-aware UX and for other commands to consume (formatting library).

2) /lib/cmds/creator/ls.lpc (creator)
- Purpose: Creator/wizard-oriented `ls` with boxed UI and builder-friendly behavior.
- Features:
  - Uses `previous_object()` and `player->resolve_path()` to respect creator cwd and resolution.
  - Builds a boxed header/footer and separates directories vs files.
  - Uses helper `list_items_horizontal()` which pads items into fixed-width columns (hardcoded col_width and cols_per_row).
  - Provides a `help()` function and explicit `tell_object(player, ...)` style usage.
- Notes:
  - Creator-focused: resolves paths against the creator's cwd and assumes wizard privileges.
  - Boxed UI has fixed width assumptions and doesn't use the new formatting library or terminal width efuns.

Differences Summary
-------------------
- Caller/context:
  - Top-level `ls.lpc` uses `this_player()` (general). Creator `ls` uses `previous_object()` and creator helpers.
- UX/formatting:
  - Top-level: terminal-aware, uses `/secure/formatting`, supports flags (long, sort, reverse).
  - Creator: boxed UI, fixed column widths, no `-l`/`-t` flags, more decorative layout.
- Feature parity:
  - Top-level has more `ls`-like flags; creator has builder conveniences (cwd resolution, boxed header).
- Privilege handling:
  - Creator version assumes creator privileges and uses `resolve_path()`; top-level lacks explicit checks.

Recommendation
--------------
I recommend the following approach to consolidate features safely and cleanly:

1. Canonical location: keep `/lib/cmds/creators/ls.lpc` as the canonical file (creators/ is the correct home for filesystem/dev tools).

2. Merge strategy (preferred):
   - Replace the body of `/lib/cmds/creators/ls.lpc` with a merged implementation that:
     - Retains creator-friendly path resolution (`resolved = player->resolve_path(arg)` / `player->query_cwd()` fallback).
     - Uses the terminal-aware multi-column and `-l,-a,-t,-r,-1` flag support from the top-level `ls.lpc` implementation.
     - Preserves boxed header/footer if desired, but make it adapt to `query_terminal_width()` instead of hardcoded widths.
     - Keeps `help()` and creator invocation style (`previous_object()` / `tell_object()` calls) for consistency.

3. Steps to implement merge safely:
   - Move the current top-level implementation into `/lib/cmds/creators/ls.lpc` (overwrite or merge).
   - Add path resolution and use `previous_object()` to get `player` in creators context.
   - Replace hardcoded formatting and `repeat_string()` usage with calls to `/secure/formatting` where appropriate.
   - Keep a short shim at `/lib/cmds/ls.lpc` that either delegates to `/lib/cmds/creators/ls.lpc` (if you want backward compatibility) or remove the top-level file once confirmed.

4. Immediate action recommendation:
   - Move `/lib/cmds/ls.lpc` into `/lib/cmds/creators/ls.lpc` only after merging or after confirming which implementation to keep.
   - Until merge is complete, leave both in place and mark `/lib/cmds/ls.lpc` as the new implementation to be integrated.

Rationale
---------
- Putting the canonical implementation in `creators/` keeps filesystem tools in the developer space and prevents accidental exposure to normal players.
- Merging gives creators the most useful functionality (flags, correct path resolution) while maintaining the creator UX (help, boxed headers if desired).

If you want, I can perform the merge now: produce a merged `/lib/cmds/creators/ls.lpc` that combines the top-level `ls.lpc` features with creator path resolution and an adaptive boxed header. Confirm and I'll apply the change and run the dry-run script afterwards.

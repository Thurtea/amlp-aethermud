**Editor & LPC Pathing — Findings**

Generated: 2026-02-16

Summary:
- There is a built-in `ed` command route exposed via the wizard tool (`wiz ed`), but it is not implemented. The `wiztool` provides many file/objects utilities and contains a `cmd_ed()` stub that replies: "Ed editor not yet implemented. Edit files externally and use 'update' to reload." So in-game editing is not available.

Details:

- Does `ed` command exist and where:
  - `wiztool` is implemented at `lib/std/wiztool.lpc` (provides developer commands for attached wizards).
  - `wiztool` maps the `ed` verb to `cmd_ed(args)` (see `case "ed": cmd_ed(args); return 1;`).
  - The implementation of `cmd_ed` is a stub:

    ```c
    void cmd_ed(string file) {
        tell_object(owner, "Ed editor not yet implemented.");
        tell_object(owner, "Edit files externally and use 'update' to reload.");
    }
    ```

- How it works (current):
  - `wiztool` supports many filesystem and object operations (`cd`, `ls`, `cat`, `more`, `update`, `load`, `clone`, `destruct`, `goto`, etc.).
  - `ed` is intentionally unimplemented — the codebase expects developers to edit files using external tools and then use `update`/`load`/`clone` to reload or test changes in-game.

- File path convention (observed):
  - Repository source files use the `.lpc` extension (example: `lib/domains/wizard/thurtea/workroom.lpc`).
  - The runtime/object-loading commands often work with object paths without explicit source-file extensions. For example, `cmd_load`, `cmd_update`, and `cmd_clone` attempt to remove a `.c` suffix before calling `load_object`/`clone_object`. They do not strip `.lpc` in the `wiztool` helper, so the conventional usage is to supply an object path (no `.c`) when loading/updating objects. `cmd_cat` and `cmd_more` read raw filesystem paths and therefore need the actual filename (including `.lpc`) if you want to read source files directly.
  - Practical rules from inspection:
    - To view a file's contents via `wiztool`: use the filesystem name, e.g. `cat /lib/domains/wizard/thurtea/workroom.lpc` (includes `.lpc`).
    - To reload an in-memory object: prefer `update /domains/wizard/thurtea/workroom` (object path without `.c`), then `update` will call `load_object` on that path.
    - The system strips `.c` suffixes, not `.lpc` — so avoid giving `.c` explicitly; `.lpc` is the on-disk source suffix here.

- Can `ed` edit LPC files in-game?
  - No — the `cmd_ed()` is a placeholder that tells the user to edit externally and use `update`. There is no in-game line editor available at present.

- Quick check of wizard workroom path (commands executed against workspace files):
  - Directory listing shows `lib/domains/wizard/thurtea/workroom.lpc` exists (file present).
  - There is no bare `workroom` file (without extension) on disk; the object path for runtime use is `/domains/wizard/thurtea/workroom` (used with `load`/`update`).

Observed files used in checks:
- `lib/std/wiztool.lpc` — contains `cmd_ed` stub and many developer utilities.
- `lib/domains/wizard/thurtea/workroom.lpc` — example wizard workroom source file present on disk.

Recommendations:
- If you want an in-game editor, implement `cmd_ed()` in `lib/std/wiztool.lpc` or add a separate editor module (respecting line-editing, multi-line input, and save semantics). Until then, edit `.lpc` files externally and use `wiz update /path/to/object` (object path without `.c`) to reload.
- Prefer using object paths without extensions when calling `update`/`load`/`clone`, and use `.lpc` when reading or editing files on disk.

*** End of file

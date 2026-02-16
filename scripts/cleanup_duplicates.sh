#!/usr/bin/env bash
# cleanup_duplicates.sh
# Commented `git mv` / `git rm` commands for the top high-priority duplicates.
# Usage (dry-run):
#   bash scripts/cleanup_duplicates.sh --dry-run
# To actually run uncomment desired git commands after manual verification.

DRY_RUN=true
if [[ "$1" == "--apply" ]]; then
  DRY_RUN=false
fi

echo "Duplicate cleanup helper"
echo "Dry run:" $DRY_RUN

echo "\nVerification steps (run before any git operations):"
echo "  diff -u src/<file> <duplicate_path> | head"
echo "  grep -R '<symbol_or_header>' src/ lib/ Makefile"

# Top-priority candidate commands (commented). For each group:
# - If canonical exists under src/, remove other copies after diff verification.
# - If canonical missing in src/, consider moving one copy into src/ with git mv.

# 1) array.c
# Verify:
# diff -u src/array.c mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/array.c | less
# If src/array.c is canonical, remove other:
# git rm --cached "mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/array.c"

# 2) array.h
# diff -u src/array.h mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/array.h
# git rm --cached "mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/array.h"

# 3) combat.c
# diff -u src/combat.c mud-references/deadsouls/ds3.8.2/lib/lib/combat.c
# git rm --cached "mud-references/deadsouls/ds3.8.2/lib/lib/combat.c"

# 4) combat.h
# diff -u src/combat.h lib/include/combat.h
# git rm --cached "lib/include/combat.h"

# 5) compiler.c
# diff -u src/compiler.c mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/compiler.c
# git rm --cached "mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/compiler.c"

# 6) compiler.h
# diff -u src/compiler.h mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/compiler.h
# git rm --cached "mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/compiler.h"

# 7) death.c
# multiple duplicates under mud-references; verify then remove extras
# diff -u src/death.c mud-references/deadsouls/ds3.8.2/lib/std/death.c
# git rm --cached "mud-references/deadsouls/ds3.8.2/lib/std/death.c"

# 8) debug.h
# diff -u src/debug.h mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/debug.h
# git rm --cached "mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/debug.h"

# 9) item.c
# diff -u src/item.c mud-references/deadsouls/ds3.8.2/lib/lib/std/item.c
# git rm --cached "mud-references/deadsouls/ds3.8.2/lib/lib/std/item.c"

# 10) item.h
# diff -u src/item.h mud-references/deadsouls/ds3.8.2/lib/lib/include/item.h
# git rm --cached "mud-references/deadsouls/ds3.8.2/lib/lib/include/item.h"

# 11) magic.c
# diff -u src/magic.c mud-references/deadsouls/ds3.8.2/lib/lib/magic.c
# git rm --cached "mud-references/deadsouls/ds3.8.2/lib/lib/magic.c"

# 12) magic.h
# diff -u src/magic.h mud-references/deadsouls/ds3.8.2/lib/include/magic.h
# git rm --cached "mud-references/deadsouls/ds3.8.2/lib/include/magic.h"

# 13) mapping.c
# diff -u src/mapping.c mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/mapping.c
# git rm --cached "mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/mapping.c"
# OR if moving:
# git mv "mud-references/deadsouls/ds3.8.2/lib/secure/modules/mapping.c" src/mapping.c

# 14) mapping.h
# diff -u src/mapping.h mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/mapping.h
# git rm --cached "mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/mapping.h"

# 15) npc.c
# diff -u src/npc.c mud-references/deadsouls/ds3.8.2/lib/lib/npc.c
# git rm --cached "mud-references/deadsouls/ds3.8.2/lib/lib/npc.c"

# 16) npc.h
# diff -u src/npc.h mud-references/deadsouls/ds3.8.2/lib/lib/include/npc.h
# git rm --cached "mud-references/deadsouls/ds3.8.2/lib/lib/include/npc.h"

# 17) object.c
# diff -u src/object.c mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/object.c
# git rm --cached "mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/object.c"

# 18) object.h
# diff -u src/object.h mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/object.h
# git rm --cached "mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/object.h"

# 19) parser.c
# diff -u src/parser.c mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/parser.c
# git rm --cached "mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/parser.c"

# 20) parser.h
# diff -u src/parser.h mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/parser.h
# git rm --cached "mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/parser.h"

# Special: lib/master.lpc
# Verify differences and reconcile. Example:
# diff -u lib/master.lpc lib/secure/master.lpc
# If lib/master.lpc is canonical, then:
# git rm --cached "lib/secure/master.lpc"

# Special: Makefile (root is canonical)
# Review differences then remove/move secondary Makefiles if unused.
# git rm --cached lib/Makefile

echo "\nDry-run finished. All git actions are commented out. Review diffs and uncomment desired commands to apply changes."

exit 0

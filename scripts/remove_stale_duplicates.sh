#!/usr/bin/env bash
set -euo pipefail

# Safely remove older/stale duplicate files identified in Red-Drift analysis.
# For tracked files, uses `git rm`; for untracked, uses `rm -v`.
# Review the list below before running. This script will not commit changes.

TO_REMOVE=(
  "src/array.c"
  "src/array.h"
  "mud-references/deadsouls/ds3.8.2/lib/lib/combat.c"
  "lib/include/combat.h"
  "mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/compiler.c"
  "mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/compiler.h"
  "mud-references/deadsouls/ds3.8.2/lib/domains/campus/room/death.c"
  "src/debug.h"
  "mud-references/deadsouls/ds3.8.2/lib/lib/std/item.c"
  "mud-references/deadsouls/ds3.8.2/lib/lib/include/item.h"
  "mud-references/deadsouls/ds3.8.2/lib/lib/magic.c"
  "mud-references/deadsouls/ds3.8.2/lib/include/magic.h"
  "src/mapping.c"
  "src/mapping.h"
  "mud-references/deadsouls/ds3.8.2/lib/lib/npc.c"
  "mud-references/deadsouls/ds3.8.2/lib/lib/include/npc.h"
  "mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/object.c"
  "src/object.h"
  "mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/parser.c"
  "mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/parser.h"
)

echo "Files marked for safe removal (review before proceeding):"
for f in "${TO_REMOVE[@]}"; do
  echo " - $f"
done

read -p "Type YES to proceed with removal (no automatic commit): " confirm
if [ "$confirm" != "YES" ]; then
  echo "Aborting. No files removed."
  exit 0
fi

for f in "${TO_REMOVE[@]}"; do
  if [ ! -e "$f" ]; then
    echo "Missing: $f (skipping)"
    continue
  fi
  if git ls-files --error-unmatch "$f" >/dev/null 2>&1; then
    echo "git rm -- $f"
    git rm -- "$f"
  else
    echo "rm -v -- $f"
    rm -v -- "$f"
  fi
done

echo "Removal operations complete. Review `git status` and commit if desired."

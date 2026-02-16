#!/usr/bin/env bash
set -euo pipefail

# Safe cleanup script for driver (src/) vs library (lib/) duplicates.
# Default: dry-run. Use --execute to perform git operations.

DRY_RUN=true
if [[ ${1-} == "--execute" ]]; then
  DRY_RUN=false
fi

# Summary:
# - Will remove: 0 duplicate files
# - Will move: 0 misplaced files
# - Needs review: 36 files with conflicts
# - Space saved: ~0 KB

# Files to remove (git rm) - ONLY enable entries that are byte-for-byte identical and safe to delete.
declare -a REMOVE_FILES=(
)

# Moves (source:destination) - populate as pairs when a file should be relocated under src/ or lib/.
declare -a MOVE_FILES=(
)

# Files/pairs needing manual review (do NOT act automatically). Format: "pathA:pathB"
declare -a NEEDS_REVIEW=(
  "lib/cmds/admin/wiztool.lpc:lib/std/wiztool.lpc"
  "lib/cmds/cat.lpc:lib/cmds/creator/cat.lpc"
  "lib/cmds/cd.lpc:lib/cmds/creator/cd.lpc"
  "lib/cmds/clone.lpc:lib/cmds/creator/clone.lpc"
  "lib/cmds/eval.lpc:lib/cmds/creator/eval.lpc"
  "lib/cmds/goto.lpc:lib/cmds/admin/goto.lpc"
  "lib/cmds/language.lpc:lib/std/language.lpc"
  "lib/cmds/ls.lpc:lib/cmds/creator/ls.lpc"
  "lib/cmds/promote.lpc:lib/cmds/admin/promote.lpc"
  "lib/cmds/pwd.lpc:lib/cmds/creator/pwd.lpc"
  "lib/cmds/shutdown.lpc:lib/cmds/admin/shutdown.lpc"
  "lib/daemon/languages.lpc:lib/cmds/languages.lpc"
  "lib/daemon/login.lpc:lib/clone/login.lpc"
  "lib/daemon/skills.lpc:lib/cmds/skills.lpc"
  "lib/domains/castle/spike.lpc:lib/domains/staff_castle/npc/spike.lpc"
  "lib/domains/forest/rooms/void.lpc:lib/domains/start/room/void.lpc"
  "lib/domains/new_camelot/garden/fountain.lpc:lib/domains/new_camelot/garden/obj/fountain.lpc"
  "lib/domains/new_camelot/stables.lpc:lib/domains/staff_castle/room/stables.lpc"
  "lib/domains/tutorial/rooms/start.lpc:lib/cmds/start.lpc"
  "lib/master.lpc:lib/secure/master.lpc"
  "lib/psionics/physical/levitation.lpc:lib/spells/level2/levitation.lpc"
  "lib/psionics/physical/telekinesis.lpc:lib/spells/level3/telekinesis.lpc"
  "lib/psionics/super/mind_block.lpc:lib/psionics/sensitive/mind_block.lpc"
  "lib/psionics/super/psi_sword.lpc:lib/psionics/physical/psi_sword.lpc"
  "lib/races/atlantean.lpc:lib/languages/atlantean.lpc"
  "lib/races/burster.lpc:lib/occs/burster.lpc"
  "lib/races/cosmo_knight.lpc:lib/occs/cosmo_knight.lpc"
  "lib/races/goblin.lpc:lib/languages/goblin.lpc"
  "lib/races/mind_melter.lpc:lib/occs/mind_melter.lpc"
  "lib/races/psi_healer.lpc:lib/occs/psi_healer.lpc"
  "lib/races/psi_stalker.lpc:lib/occs/psi_stalker.lpc"
  "lib/single/rations.lpc:lib/objects/supplies/rations.lpc"
  "lib/single/shield.lpc:lib/objects/armor/shield.lpc"
  "lib/single/sword.lpc:lib/objects/weapons/sword.lpc"
  "lib/single/vibro_blade.lpc:lib/objects/weapons/vibro_blade.lpc"
  "src/combat.h:lib/include/combat.h"
)

echo "Dry run: ${DRY_RUN}" 

if [ ${#REMOVE_FILES[@]} -eq 0 ] && [ ${#MOVE_FILES[@]} -eq 0 ]; then
  echo "No automatic removals or moves configured.\n"
  echo "Detected duplicates (manual review required):"
  echo " - combat.h: src/combat.h  <-> lib/include/combat.h  (review and reconcile)"
  echo " - (many lib/*.lpc duplicates listed in archived-md/10_driver_lib_duplicates_only.md)"
  echo
  echo "To apply changes: edit this script, add paths to REMOVE_FILES or MOVE_FILES, then run:"
  echo "  ./scripts/cleanup_driver_lib_duplicates.sh --execute"
  exit 0
fi

run_rm() {
  local f="$1"
  if [[ "$f" != src/* && "$f" != lib/* ]]; then
    echo "Refusing to remove outside src/ or lib/: $f" >&2
    return 1
  fi
  echo "git rm -- $f"
  if [ "$DRY_RUN" = false ]; then
    git rm -- "$f"
  fi
}

run_mv() {
  local pair="$1"
  IFS=":" read -r src dst <<< "$pair"
  if [[ "$src" != src/* && "$src" != lib/* ]]; then
    echo "Refusing to move source outside src/ or lib/: $src" >&2
    return 1
  fi
  if [[ "$dst" != src/* && "$dst" != lib/* ]]; then
    echo "Refusing to move destination outside src/ or lib/: $dst" >&2
    return 1
  fi
  echo "git mv -- $src $dst"
  if [ "$DRY_RUN" = false ]; then
    mkdir -p "$(dirname "$dst")"
    git mv -- "$src" "$dst"
  fi
}

for f in "${REMOVE_FILES[@]:-}"; do
  run_rm "$f"
done

for p in "${MOVE_FILES[@]:-}"; do
  run_mv "$p"
done

echo "Done."

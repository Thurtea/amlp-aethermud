Duplicate Review Guide

Source: derived from `archived-md/12_duplicate_priority_list.md` — Category B pairs
Date: 2026-02-16

Overview
- These 8 pairs were identified as near-duplicates (minor differences). None are byte-for-byte identical; each requires a brief manual review. Below each pair includes sizes, a short diff excerpt (first 20 lines), and a recommendation.

Priority categories
- High: Files in semantically wrong locations or security-sensitive (none in this set)
- Medium: Functional duplicates in command/psionic domains (several below)
- Low: Intentional variants (single/ vs objects/) — can be reconciled with small merges

Pairs

1) lib/cmds/ls.lpc  |  lib/cmds/creator/ls.lpc
- Sizes:
  - lib/cmds/creator/ls.lpc: 4.4K
  - lib/cmds/ls.lpc: 4.2K
- Diff (first 20 lines):
  --- lib/cmds/ls.lpc
  +++ lib/cmds/creator/ls.lpc
  @@ -1,30 +1,26 @@
  -// lib/cmds/ls.lpc
  -// Multi-column ls implementation using /secure/formatting and efuns
  +/*
  + * /lib/cmds/creator/ls.lpc - Creator-aware ls using terminal-aware formatting
  + * Merged implementation: uses the multi-column ls and preserves creator path resolution
  + */
  -string usage() {
  -    return "Usage: ls [-l1atxr] [path]\n";
  -}
  +string usage() { return "Usage: ls [-l1atxr] [path]\n"; }
- Recommendation: Keep `lib/cmds/creator/ls.lpc` (more complete and creator-aware). Remove `lib/cmds/ls.lpc` after testing and updating any references.

2) lib/cmds/pwd.lpc  |  lib/cmds/creator/pwd.lpc
- Sizes:
  - lib/cmds/creator/pwd.lpc: 353
  - lib/cmds/pwd.lpc: 276
- Diff (first 20 lines):
  --- lib/cmds/pwd.lpc
  +++ lib/cmds/creator/pwd.lpc
  @@ -1,10 +1,18 @@
  -// /cmds/pwd.lpc
  -// Print working directory
  +/*
  + * /lib/cmds/creator/pwd.lpc - Show current working directory
  + *
  + * Usage:
  + *   pwd
  + */
  -int main(string args) {
  -    object player = this_player();
  -    if (!player) return 0;
  +int main(string args) {
  +    object player = previous_object();
  +    
  +    tell_object(player, "Current directory: " + player->query_cwd() + "\n");
- Recommendation: Keep `lib/cmds/creator/pwd.lpc` (functional implementation). Remove stub `lib/cmds/pwd.lpc` after ensuring no external references.

3) lib/cmds/shutdown.lpc  |  lib/cmds/admin/shutdown.lpc
- Sizes:
  - lib/cmds/admin/shutdown.lpc: 283
  - lib/cmds/shutdown.lpc: 254
- Diff (first 20 lines):
  --- lib/cmds/shutdown.lpc
  +++ lib/cmds/admin/shutdown.lpc
  @@ -1,10 +1,15 @@
  -// /cmds/shutdown.lpc
  -// Shutdown server
  +// Shutdown command
  +
  +#include <globals.h>
  +
  +int main(string arg) {
  +    object user;
  +    
  +    user = previous_object();
  +    
  +    // Should add security check here
- Recommendation: Keep `lib/cmds/admin/shutdown.lpc` (admin-qualified, includes headers). Remove shallow stub `lib/cmds/shutdown.lpc` after verifying callers.

4) lib/psionics/physical/levitation.lpc  |  lib/spells/level2/levitation.lpc
- Sizes:
  - lib/psionics/physical/levitation.lpc: 2.8K
  - lib/spells/level2/levitation.lpc: 2.1K
- Diff (first 20 lines):
  --- lib/psionics/physical/levitation.lpc
  +++ lib/spells/level2/levitation.lpc
  @@ -1,38 +1,39 @@
  -// /lib/psionics/physical/levitation.lpc
  -// Physical Psionic - Levitation (varies ISP)
  -// Fly and float using psionic power
  +// /lib/spells/level2/levitation.lpc
  +// Level 2 Spell - Levitation (5 PPE)
  +// Allows caster to float and fly
  
  -inherit "/lib/std/psionic";
  +inherit "/lib/std/spell";
- Recommendation: Prefer `lib/spells/level2/levitation.lpc` for spell implementations. If the psionic variant is intentionally different, keep both but document differences; otherwise, consolidate to `lib/spells/level2/levitation.lpc` and move or merge unique psionic behaviors into a shared helper.

5) lib/psionics/super/mind_block.lpc  |  lib/psionics/sensitive/mind_block.lpc
- Sizes:
  - lib/psionics/sensitive/mind_block.lpc: 2.1K
  - lib/psionics/super/mind_block.lpc: 1.4K
- Diff (first 20 lines):
  --- lib/psionics/super/mind_block.lpc
  +++ lib/psionics/sensitive/mind_block.lpc
  @@ -1,44 +1,68 @@
  -/*
  - * /lib/psionics/super/mind_block.lpc - Mind Block
  - *
  - * Mental defense power
  - */
  +// /lib/psionics/sensitive/mind_block.lpc
  +// Sensitive Psionic - Mind Block (4 ISP)
  +// Protects against psionic attacks and mind reading
  
  -inherit "/std/psionic";
  +inherit "/lib/std/psionic";

  void create() {
      ::create();
      
      set_power_name("Mind Block");
- Recommendation: Keep `lib/psionics/sensitive/mind_block.lpc` as the more complete variant. Merge any unique functionality from `super` file if necessary.

6) lib/psionics/super/psi_sword.lpc  |  lib/psionics/physical/psi_sword.lpc
- Sizes:
  - lib/psionics/super/psi_sword.lpc: 4.4K
  - lib/psionics/physical/psi_sword.lpc: 4.0K
- Diff (first 20 lines):
  --- lib/psionics/super/psi_sword.lpc
  +++ lib/psionics/physical/psi_sword.lpc
  @@ -1,128 +1,125 @@
  -/*
  - * /lib/psionics/super/psi_sword.lpc - Psi-Sword
  - *
  - * Creates a blade of pure psionic energy
  - */
  +// /lib/psionics/physical/psi_sword.lpc
  +// Psi-Sword - Physical Psionic Power
  +// Creates a blade of pure psionic energy (M.D.C. weapon!)

  -inherit "/std/psionic";
  +inherit "/std/psionic_power";

  void create() {
      ::create();
- Recommendation: Keep `lib/psionics/super/psi_sword.lpc` (more complete). Consolidate to the `super` variant and ensure appropriate inheritance (`psionic_power`) is used consistently.

7) lib/single/rations.lpc  |  lib/objects/supplies/rations.lpc
- Sizes:
  - lib/single/rations.lpc: 580
  - lib/objects/supplies/rations.lpc: 513
- Diff (first 20 lines):
  --- lib/single/rations.lpc
  +++ lib/objects/supplies/rations.lpc
  @@ -1,22 +1,21 @@
  -// Rations - Basic food item
  +// /lib/objects/supplies/rations.lpc
  +// Food rations
  +
   inherit "/std/object";
   
   void create() {
       ::create();
       
  -    set_name("rations");
  -    set_id("rations");
  -    set_id_alt("food");
  -    set_short("a package of rations");
  +    set_id(({"rations", "food", "supplies", "ration pack"}));
  +    set_short("a pack of rations");
- Recommendation: Prefer `lib/objects/supplies/rations.lpc` as canonical object location; keep `lib/single/rations.lpc` only if it implements a different pickup/spawn behavior. Otherwise consolidate to `lib/objects/supplies/`.

8) lib/single/vibro_blade.lpc  |  lib/objects/weapons/vibro_blade.lpc
- Sizes:
  - lib/objects/weapons/vibro_blade.lpc: 750
  - lib/single/vibro_blade.lpc: 981
- Diff (first 20 lines):
  --- lib/single/vibro_blade.lpc
  +++ lib/objects/weapons/vibro_blade.lpc
  @@ -1,30 +1,25 @@
  -// Vibro-Blade - Standard melee weapon
  +// /lib/objects/weapons/vibro_blade.lpc
  +// Standard vibro-blade weapon
  +
   inherit "/std/object";
   
   void create() {
       ::create();
       
  -    set_name("vibro-blade");
  -    set_id("blade");
  -    set_id_alt("vibro");
  -    set_short("a vibro-blade");
  +    set_id(({"vibro-blade", "blade", "sword", "vibroblade"}));
  +    set_short("a vibrating combat blade");
- Recommendation: Keep `lib/objects/weapons/vibro_blade.lpc` as canonical weapon location; merge any unique descriptions or stats from `lib/single/vibro_blade.lpc` if needed.

Review priorities
- High: none in this set.
- Medium: `ls`, `pwd`, `shutdown`, `psi_sword`, `mind_block`, `levitation` — review for functional differences and security checks.
- Low: `rations`, `vibro_blade` — object vs single variants; reconcile object placement and canonical IDs.

Commands for reviewers (do not run as part of this guide)

General diff and review
  diff -u <fileA> <fileB> | less

If you decide to keep fileB and remove fileA (example):
  # create backup archive
  tar -czf /tmp/duplicate-backup-$(date +%F_%H%M%S).tar.gz <fileA>

  # update references (search repo for references to fileA)
  grep -R --line-number -- "<fileA>" . || true

  # move fileA to archive (safer than immediate delete)
  mkdir -p archived-md/archived-duplicates
  git mv <fileA> archived-md/archived-duplicates/
  git commit -m "Archive duplicate <fileA> in favor of <fileB>"

If you prefer to merge differences manually:
  # open a 3-way or side-by-side merge tool
  vim -d <fileB> <fileA>

Final removal (after backup & repo cleanup checks):
  git rm <fileA>
  git commit -m "Remove duplicate <fileA> (kept <fileB>)"

Notes
- Always run the MUD test suite and perform sanity checks after removing or merging library files.
- For commands altering security or master behavior, test on a staging instance first.

# Stub/TODO Triage — 2026-02-26

Scanned markers: TODO, FIXME, STUB, TBD, PLACEHOLDER, UNVERIFIED, XXX
Source: repo grep across listed lib/ directories during session.

## Summary
- High concentration of stubs in `lib/occs/` and `lib/races/`.
- Many skills and psionics contain TODO:CONTENT notes (implement `perform()` / `activate()` when systems wired).
- Several command wrappers are stubbed (cd, clone, eval, promote, users, goto).

## Priority: High (review/complete before launch)
- lib/occs/* (representative files detected):
  - lib/occs/rogue_scientist.lpc — Placeholder / stub
  - lib/occs/wilderness_scout.lpc — TODO: Review and expand
  - lib/occs/mercenary.lpc — Stub
  - lib/occs/biomancer.lpc — Stub
  - lib/occs/mystic.lpc — Stub
  - lib/occs/stone_master.lpc — Stub
  - lib/occs/techno_wizard.lpc — Stub
  - lib/occs/burster.lpc — Stub
  - lib/occs/fury_beetle.lpc — Auto-populated stub
  - lib/occs/battle_magus.lpc — Stub
  - lib/occs/shifter.lpc — Stub
  - lib/occs/full_conversion_borg.lpc — Stub + TODO
  - lib/occs/psi_stalker.lpc — Auto-generated stub + TODO
  - lib/occs/mind_melter.lpc — Stub
  - lib/occs/robot_pilot.lpc — Stub + TODO
  - lib/occs/special_forces.lpc — Stub
  - lib/occs/warlock.lpc — Stub
  - lib/occs/necromancer.lpc — Stub
  - lib/occs/tattooed_man.lpc — TODO:CONTENT (tattoo mechanics)
  - lib/occs/pending.lpc — Minimal placeholder (keeps code safe)

Notes: OCC stubs often contain core gameplay definitions (stats, skills, starting kit). Mark as launch blocker until reviewed for balance and completeness.

## Priority: High (races)
- lib/races/* (representative files detected):
  - lib/races/simvan.lpc — Placeholder stub
  - lib/races/dragon_hatchling.lpc — Stub
  - lib/races/uteni.lpc — Stub
  - lib/races/eandroth.lpc — Stub
  - lib/races/noli.lpc — Stub
  - lib/races/trimadore.lpc — Stub
  - lib/races/fire_dragon.lpc — Placeholder values noted
  - lib/races/ice_dragon.lpc — Placeholder values
  - lib/races/titan.lpc — Placeholder; verify with source
  - lib/races/cat_girl.lpc — sets auto-dodge (needs review)

Notes: Races affect core mechanics; verify stats, abilities, and canonical sources.

## Priority: Medium (skills & psionics)
- Skills (many `lib/skills/rogue/*` entries): streetwise, safecracking_rogue, disguise_rogue, pick_locks_rogue, impersonation, forgery_rogue, pick_pockets_rogue, palming, prowl, concealment_rogue, gambling_rogue — contain TODO:CONTENT and "implement perform() when skill system wired".
- Weapon proficiencies in `lib/skills/wp_modern/*` (wp_rifle, wp_pistol, wp_energy_rifle, wp_explosives, etc.) — TODO notes and perform stubs.
- Medical skills (paramedic, medical_doctor, field_surgery, forensics, holistic_medicine) — TODO content placeholders.
- Pilot skills — TODO placeholders.
- Psionics powers (e.g., `lib/psionics/healing/*`, `lib/psionics/physical/*`) — many include "TODO:CONTENT — power not yet fully implemented" or missing `activate()`.

Action: schedule implementation or mark as unsupported for initial launch if time-constrained.

## Priority: Low (commands, tools, misc)
- lib/cmds: `cd.lpc`, `clone.lpc`, `eval.lpc`, `promote.lpc`, `users.lpc`, `goto.lpc` — present as stubs with user-facing stub messages. These should be implemented or clearly documented for developers.
- lib/obj/corpse.lpc — TODO: wire `call_out()` when driver supports it; commented `call_out("decay", DECAY_SECONDS);` line.
- lib/wiz: `lib/wiz/rp_skill_tool.lpc` — "RP tool command stub."; `lib/wiz/admin_orb.lpc` — has server stats stub and TODOs for shutdown/reboot.
- lib/saves: `VampireTest.save`, `CyberKnightTest.save` — placeholder text files (ensure not to ship as real saves).
- lib/tools/generate_stubs.sh — script used to generate many of the above stubs (contains template placeholders). Treat as authoritative source for auto-generated stubs.

## Triage recommendations (next steps taken now)
1. Create a tracked checklist to assign OCC and Race files to reviewers; mark each file with status: review-needed / in-progress / verified. (I will create this checklist next.)
2. For immediate safety, keep `lib/occs/pending.lpc` placeholder to avoid runtime errors; do not remove.
3. Decide which skills/psionics to postpone: if the core combat/spell/psionic systems are not yet wired, mark those skill/psionic TODOs as "deferred" and record in the checklist.
4. Remove or replace placeholder save files from `lib/saves/` if they are not intended to be source-controlled.

---

Report generated automatically from repo grep results during this session. If you want the per-file checklist created now, I will generate `/REPORTS/stub_review_checklist.csv` listing each matched file and an initial priority and status. (Proceeding now.)

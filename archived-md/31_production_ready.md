# Production Ready — Critical Fixes 29+30

Date: 2026-02-16

Status: DEPLOYMENT READY

- ✅ Chargen: Race→Alignment→Spawn (O.C.C. selection moved to post-login via `selectocc`)
- ✅ Workroom: `crystal`, `handbook`, `staff` keywords added and tested for lookup
- ✅ Admin: First-ever character ONLY (first-ever determined by absence of saved player files)
- ✅ Git: changes committed and pushed to `main`

Notes:
- `any_saved_players()` scans `lib/save/players` for `*.dat` files to detect existing players and prevents accidental admin grants on restores.
- Use `selectocc <occ_id>` after logging in to choose your O.C.C.; see help topic `selectocc`.

Deployment: Ready


# New Camelot Migration Summary

Date: 2026-02-14

## 1) Files created
- lib/domains/new_camelot/town_square.lpc
- lib/domains/new_camelot/tavern.lpc
- lib/domains/new_camelot/training_grounds.lpc
- lib/domains/new_camelot/blacksmith_forge.lpc
- lib/domains/new_camelot/chapel.lpc
- lib/domains/new_camelot/stables.lpc
- lib/domains/new_camelot/gate.lpc

## 2) Final exit map (ASCII)

            Tavern
              |
 Blacksmith - Town Square - Training - Stables
                |  \
             Connector  Gate
                       |
                     Chapel

Legend:
- Connector = /domains/new_camelot/connect/connector_south (south of Town Square)
- Gate is reachable from Town Square via `southeast` and has `northwest` back to Town Square

Detailed (directional):
- Town Square: north→Tavern, east→Training Grounds, west→Blacksmith, south→Connector, southeast→Gate
- Tavern: south→Town Square
- Training Grounds: west→Town Square, east→Stables
- Stables: west→Training Grounds
- Blacksmith: east→Town Square
- Gate: northwest→Town Square, north→Chapel
- Chapel: south→Gate
- Connector: north→Town Square

## 3) What to remove/update in `src/room.c`
- Remove the hardcoded `init_room` calls for room IDs 4 through 10 (New Camelot block):
  - `init_room(4, "New Camelot - Town Square", ...);` through `init_room(10, "New Camelot Gate", ...);`
- Remove or adapt the flex-exit population block that sets `world_rooms[4].flex_exits` and the `direction`/`target_path` for the connector (the C-side connector setup). If you prefer to keep the connector as a C flex-exit, keep the logic but avoid duplicating exits already defined in LPC.
- Replace the removed init blocks with a registration/loading mechanism mapping numeric room IDs (4–10) to the LPC file paths, or with minimal stubs that allow the driver to delegate to LPC loaders at runtime.

## 4) Next steps for testing
1. Build and run the driver in a dev environment and watch startup logs for LPC load errors.
2. From an admin session, `goto` each LPC path and verify exits: town_square, tavern, training_grounds, blacksmith_forge, stables, gate, chapel, plus the connector.
3. Verify reciprocity by following each exit and confirming the returned exit goes back as expected.
4. If the driver supports hot-loading, test unloading/reloading the LPC files. Otherwise, restart the driver between tests.
5. After verification, remove the C `init_room` blocks and run the same checks to ensure nothing regresses.

---

Stop: awaiting further instructions.

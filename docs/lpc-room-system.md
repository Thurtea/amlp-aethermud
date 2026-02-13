# LPC Room System

## Overview
The AMLP driver supports loading rooms from LPC files at runtime without recompiling. Rooms are cached on first access and resolved by LPC path (e.g. `/domains/foo/room/bar`). The loader text-scrapes common `set_*()` calls from LPC source to populate runtime `Room` structures.

## Creating LPC Rooms

### Basic Structure
```lpc
inherit "/std/room";

void create() {
    ::create();
    set_short("Room Name");
    set_long("Full description of the room. This is what players see when they 'look'.");
}
```

### Adding Exits
```lpc
// Style A: Individual exits
add_exit("north", "/lib/domains/myarea/room/north_room");
add_exit("south", "/lib/domains/myarea/room/south_room");

// Style B: Mapping (batch)
set_exits(([ 
    "north": "/lib/domains/myarea/room/north_room",
    "east":  "/lib/domains/myarea/room/east_room",
    "out":   "/lib/domains/start/room/welcome"
]));
```

### Room Properties
The loader recognizes simple `set_property("key", value)` calls. Supported keys:

- `set_property("light", <0-3>)` — light level (0=dark,1=dim,2=normal,3=bright)
- `set_property("indoors", 0|1)` — indoors flag
- `set_property("no_magic", 0|1)` — block magic
- `set_property("no_combat", 0|1)` — safe/no-combat area
- `set_property("start_room", 1)` — (planned) mark room as a candidate start location

Example:
```lpc
set_property("light", 0);
set_property("indoors", 1);
set_property("no_combat", 1);
```

### Examinable Details
Use `set_items()` to provide keywords players can `examine`:
```lpc
set_items(([ 
    "statue": "A marble statue of a warrior.",
    "fountain": "A bubbling fountain with crystal-clear water.",
    "sign": "The sign reads: 'Welcome to AetherMUD!'"
]));
```

## Adding Starting Zones (Chargen)

For now the chargen menu supports a small, hard-coded set of LPC starting paths. To add a new one:

1. Create your room file in `lib/domains/<area>/room/<name>.lpc`.
2. Add the path to `src/chargen.c`'s `chargen_show_zones()` menu and handle it in the `CHARGEN_ZONE_SELECT` switch branch.
3. Rebuild the driver: `make clean && make driver`.

Future work: server-side scanning for `set_property("start_room", 1)` will make this dynamic.

## Limitations

- The loader is text-scraping only: it does not execute LPC code or perform inheritance resolution.
- `add_action()` and runtime `init()` or `reset()` logic are not executed — interactive behaviors and spawns are not available yet.
- NPC and item spawns triggered by `reset()` are not handled.

## File Locations

- LPC rooms: `lib/domains/<area>/room/`
- Room loader: `src/room.c::room_load_from_lpc()`
- Bootstrap C rooms: `src/room.c` (first 24 fallback rooms)

## Testing

Use a wizard session to test LPC rooms:
```
goto /lib/domains/myarea/room/myroom
look
examine <detail>
n (or north) to move
```

## Future Enhancements

- Dynamic discovery of `start_room` flagged rooms
- Support for synthesizing `set_items()` from common `add_action()` patterns
- NPC spawn/reset handling and weak LPC execution sandbox for common lifecycle hooks

---

Short dev note: see `src/room.c` for the loader implementation and `src/chargen.c` for the current, hard-coded chargen hooks.

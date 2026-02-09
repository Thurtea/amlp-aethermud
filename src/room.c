#include "room.h"
#include "session_internal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#define MAX_ROOMS 100

/* World data */
static Room world_rooms[MAX_ROOMS];
static int num_rooms = 0;

/* External function from session.c */
extern void send_to_player(PlayerSession *session, const char *format, ...);

/* Helper to initialize a room */
static void init_room(int id, const char *name, const char *desc,
                      int n, int s, int e, int w, int u, int d) {
    Room *r = &world_rooms[id];
    r->id = id;
    r->name = strdup(name);
    r->description = strdup(desc);
    r->exits.north = n;
    r->exits.south = s;
    r->exits.east = e;
    r->exits.west = w;
    r->exits.up = u;
    r->exits.down = d;
    r->items = NULL;
    r->players = calloc(10, sizeof(PlayerSession*));
    r->num_players = 0;
    r->max_players = 10;
}

/* Initialize the game world */
void room_init_world(void) {
    /* Room 0: The Void (starting room) */
    Room *void_room = &world_rooms[0];
    void_room->id = 0;
    void_room->name = strdup("The Void");
    void_room->description = strdup(
        "You stand in an endless expanse of swirling energy and mist.\n"
        "This liminal space exists between worlds, a nexus of possibilities.\n"
        "To the north, you sense the pull of civilization."
    );
    void_room->exits.north = 1;
    void_room->exits.south = -1;
    void_room->exits.east = -1;
    void_room->exits.west = -1;
    void_room->exits.up = -1;
    void_room->exits.down = -1;
    void_room->items = NULL;
    void_room->players = calloc(10, sizeof(PlayerSession*));
    void_room->num_players = 0;
    void_room->max_players = 10;
    
    /* Room 1: Town Plaza */
    Room *plaza = &world_rooms[1];
    plaza->id = 1;
    plaza->name = strdup("Chi-Town Plaza");
    plaza->description = strdup(
        "A bustling town square in the heart of Chi-Town. Coalition troops patrol\n"
        "the perimeter while traders hawk their wares from makeshift stalls.\n"
        "The towering spires of Coalition headquarters rise to the east.\n"
        "To the west lies the merchant district, and south returns to the void."
    );
    plaza->exits.north = 18;
    plaza->exits.south = 0;
    plaza->exits.east = 2;
    plaza->exits.west = 3;
    plaza->exits.up = -1;
    plaza->exits.down = -1;
    plaza->items = NULL;
    plaza->players = calloc(10, sizeof(PlayerSession*));
    plaza->num_players = 0;
    plaza->max_players = 10;
    
    /* Room 2: Coalition HQ Entrance */
    Room *hq = &world_rooms[2];
    hq->id = 2;
    hq->name = strdup("Coalition Headquarters - Entrance");
    hq->description = strdup(
        "Massive adamantium doors loom before you, flanked by heavily armed\n"
        "SAMAS power armor suits. This is the nerve center of Coalition authority.\n"
        "Only the plaza to the west offers escape."
    );
    hq->exits.north = -1;
    hq->exits.south = -1;
    hq->exits.east = -1;
    hq->exits.west = 1;
    hq->exits.up = -1;
    hq->exits.down = -1;
    hq->items = NULL;
    hq->players = calloc(10, sizeof(PlayerSession*));
    hq->num_players = 0;
    hq->max_players = 10;
    
    /* Room 3: Merchant District */
    Room *market = &world_rooms[3];
    market->id = 3;
    market->name = strdup("Merchant District");
    market->description = strdup(
        "A narrow street lined with shops selling everything from energy weapons\n"
        "to magical trinkets. The air smells of oil and ozone. Merchants call out,\n"
        "trying to attract customers. The plaza lies to the east."
    );
    market->exits.north = -1;
    market->exits.south = -1;
    market->exits.east = 1;
    market->exits.west = -1;
    market->exits.up = -1;
    market->exits.down = -1;
    market->items = NULL;
    market->players = calloc(10, sizeof(PlayerSession*));
    market->num_players = 0;
    market->max_players = 10;
    
    /* ============================================================ */
    /* NEW CAMELOT (Rooms 4-10)                                     */
    /* Layout:                                                      */
    /*                [5: Tavern]                                    */
    /*                    |                                          */
    /* [7: Blacksmith]--[4: Town Square]--[6: Training]--[9: Stables]*/
    /*                    |                                          */
    /*                [8: Chapel]                                    */
    /*                    |                                          */
    /*                [10: Gate]                                     */
    /* ============================================================ */

    init_room(4, "New Camelot - Town Square",
        "The central square of New Camelot, a human kingdom built on the\n"
        "ideals of chivalry and honor. Stone buildings surround a marble\n"
        "fountain. Knights in gleaming armor patrol the cobblestone streets.\n"
        "A shimmering figure -- the Moxim -- stands near the fountain,\n"
        "offering passage to distant lands.",
        5, 8, 6, 7, -1, -1);

    init_room(5, "The Silver Unicorn Tavern",
        "A warm tavern with heavy wooden beams and a roaring fireplace.\n"
        "Travelers from across AetherMUD share tales of adventure over\n"
        "mugs of ale. A bard plays softly in the corner. The barkeep\n"
        "nods a greeting from behind the counter.",
        -1, 4, -1, -1, -1, -1);

    init_room(6, "Training Grounds",
        "An open dirt yard where knights and warriors practice their combat\n"
        "skills. Wooden training dummies stand in rows and weapon racks line\n"
        "the edges. The clash of practice swords echoes off the stone walls.\n"
        "The town square is to the west, and stables lie to the east.",
        -1, -1, 9, 4, -1, -1);

    init_room(7, "Blacksmith's Forge",
        "The heat of the forge washes over you as bellows pump air into\n"
        "glowing coals. An old blacksmith hammers away at a blade on the\n"
        "anvil. Finished weapons and armor hang from hooks on the walls.\n"
        "The town square lies to the east.",
        -1, -1, 4, -1, -1, -1);

    init_room(8, "Chapel of Light",
        "A quiet stone chapel with stained glass windows depicting heroes\n"
        "of ages past. Candles flicker on a simple altar. The air carries\n"
        "a faint scent of incense. Wooden pews face the front, worn smooth\n"
        "by years of use. The town square is north, the gate south.",
        4, 10, -1, -1, -1, -1);

    init_room(9, "Stables",
        "A large barn housing horses and other riding animals. Hay bales\n"
        "are stacked against the walls and the smell of leather and feed\n"
        "fills the air. A stable hand tends to a warhorse in the far stall.\n"
        "The training grounds are to the west.",
        -1, -1, -1, 6, -1, -1);

    init_room(10, "New Camelot Gate",
        "The southern gate of New Camelot. Heavy iron-banded doors stand\n"
        "open, flanked by guards in plate armor. A dirt road leads south\n"
        "into the wilderness beyond the kingdom walls. The chapel is north.",
        8, -1, -1, -1, -1, -1);

    /* ============================================================ */
    /* SPLYNN (Rooms 11-17)                                         */
    /* Layout:                                                      */
    /* [17: Temple]--[15: Bazaar]--[11: Market]--[13: Bio-Wizard]   */
    /*                    |             |                            */
    /*                [16: Docks]  [12: Slaves]--[14: Arena]        */
    /* ============================================================ */

    init_room(11, "Splynn - Market Center",
        "The heart of Splynn, a dimensional market city ruled by the\n"
        "Splugorth. Alien beings of every description crowd the streets.\n"
        "The air crackles with residual magical energy and the babble of\n"
        "a hundred languages fills the air. A shimmering Moxim figure\n"
        "stands in the center of the chaos, offering passage elsewhere.",
        12, -1, 13, 15, -1, -1);

    init_room(12, "Slave Market",
        "Rows of cages and pens hold beings of every species. Slavers\n"
        "call out prices while buyers inspect the merchandise with cold\n"
        "eyes. Kittani overseers watch the proceedings with whips coiled\n"
        "at their sides. The market center is to the south.",
        -1, 11, 14, -1, -1, -1);

    init_room(13, "Bio-Wizard Shop",
        "Shelves of living organisms and bio-magical creations line the\n"
        "walls. Jars of glowing fluid hold specimens that twitch and pulse.\n"
        "The proprietor, a Kittani bio-wizard, tends to writhing specimens\n"
        "on a stone table. The market center is to the west.",
        -1, -1, -1, 11, -1, -1);

    init_room(14, "Arena Entrance",
        "The gates to Splynn's gladiatorial arena. The roar of the crowd\n"
        "echoes from within as combatants fight for survival and glory.\n"
        "Blood stains mark the stone floor. Bookmakers take wagers near\n"
        "the entrance. The slave market is to the west.",
        -1, -1, -1, 12, -1, -1);

    init_room(15, "Dimensional Bazaar",
        "Merchants from a hundred dimensions hawk exotic wares from stalls\n"
        "that seem to shift and change. Portal energy crackles in the air.\n"
        "Strange artifacts, alien weapons, and magical items of unknown\n"
        "origin fill every surface. The market is east, docks south.",
        -1, 16, 11, 17, -1, -1);

    init_room(16, "Splynn Docks",
        "Wooden docks extend over dark waters that seem to swirl with\n"
        "unnatural currents. Strange ships from other dimensions bob at\n"
        "anchor. Longshoremen of various alien species load and unload\n"
        "cargo. The dimensional bazaar lies to the north.",
        15, -1, -1, -1, -1, -1);

    init_room(17, "Temple of the Splugorth",
        "A towering structure of alien architecture that defies geometry.\n"
        "The walls seem to breathe and the floor pulses with a slow rhythm.\n"
        "The oppressive presence of the Splugorth intelligence weighs on\n"
        "your mind. Few come here willingly. The bazaar is to the east.",
        -1, -1, 15, -1, -1, -1);

    /* ============================================================ */
    /* CHI-TOWN EXPANSION (Rooms 18-23)                             */
    /* Layout:                                                      */
    /*                [23: Transit Hub (Moxim)]                     */
    /*                    |                                          */
    /*                [22: Medical Center]                           */
    /*                    |                                          */
    /* [20: Underground]--[21: Residential]                          */
    /*                    |                                          */
    /*                [19: Recruitment]                              */
    /*                    |                                          */
    /*                [18: Barracks]                                 */
    /*                    |                                          */
    /*                [1: Plaza] (existing)                          */
    /* ============================================================ */

    init_room(18, "Chi-Town Barracks",
        "Coalition military barracks. Rows of bunks line the walls and\n"
        "soldiers clean their weapons and gear. The smell of gun oil\n"
        "and boot polish fills the air. Discipline is strict here and\n"
        "conversation is kept to low murmurs. The plaza is to the south.",
        19, 1, -1, -1, -1, -1);

    init_room(19, "Recruitment Center",
        "A Coalition recruitment office. Posters on the walls encourage\n"
        "citizens to join the fight against supernatural threats. A bored\n"
        "sergeant sits behind a desk piled with paperwork. Eager young\n"
        "recruits wait on benches along the wall.",
        21, 18, -1, -1, -1, -1);

    init_room(20, "Underground Market",
        "A dimly lit black market hidden beneath the streets of Chi-Town.\n"
        "Goods the Coalition would consider contraband change hands here\n"
        "in whispered deals. Magic items, alien artifacts, and illegal\n"
        "weapons can be found if you know who to ask.",
        -1, -1, 21, -1, -1, -1);

    init_room(21, "Residential Block",
        "A residential area of Chi-Town. Families go about their daily\n"
        "lives in cramped but orderly apartments. Children play in the\n"
        "corridors under the watchful eye of Coalition security cameras.\n"
        "The recruitment center is south, medical center north.",
        22, 19, -1, 20, -1, -1);

    init_room(22, "Medical Center",
        "A Coalition medical facility with white walls and harsh lighting.\n"
        "Nurses and doctors tend to the sick and wounded. The smell of\n"
        "antiseptic hangs heavy in the air. Gurneys line the corridors\n"
        "and medical equipment hums quietly.",
        23, 21, -1, -1, -1, -1);

    init_room(23, "Chi-Town Transit Hub",
        "A large transit hub with arrivals and departures boards displaying\n"
        "routes across the Coalition States. The constant flow of travelers\n"
        "and soldiers creates a steady hum of activity. A shimmering Moxim\n"
        "figure stands near the main platform, offering passage to distant\n"
        "lands. The medical center is to the south.",
        -1, 22, -1, -1, -1, -1);

    num_rooms = 24;

    fprintf(stderr, "[Room] Initialized %d rooms\n", num_rooms);
}

/* Cleanup world */
void room_cleanup_world(void) {
    for (int i = 0; i < num_rooms; i++) {
        if (world_rooms[i].name) free(world_rooms[i].name);
        if (world_rooms[i].description) free(world_rooms[i].description);
        if (world_rooms[i].players) free(world_rooms[i].players);
    }
}

/* Get room by ID */
Room* room_get_by_id(int id) {
    if (id < 0 || id >= num_rooms) return NULL;
    return &world_rooms[id];
}

/* Get starting room */
Room* room_get_start(void) {
    return &world_rooms[0];
}

/* Add player to room */
void room_add_player(Room *room, PlayerSession *player) {
    if (!room || !player) return;
    
    /* Expand array if needed */
    if (room->num_players >= room->max_players) {
        room->max_players *= 2;
        room->players = realloc(room->players, room->max_players * sizeof(PlayerSession*));
    }
    
    room->players[room->num_players++] = player;
}

/* Remove player from room */
void room_remove_player(Room *room, PlayerSession *player) {
    if (!room || !player) return;
    
    for (int i = 0; i < room->num_players; i++) {
        if (room->players[i] == player) {
            /* Shift remaining players */
            for (int j = i; j < room->num_players - 1; j++) {
                room->players[j] = room->players[j + 1];
            }
            room->num_players--;
            return;
        }
    }
}

/* Add item to room */
void room_add_item(Room *room, InventoryItem *item) {
    (void)room; (void)item;
    /* TODO: implement when room items are fully wired */
}

/* Find item in room by name */
InventoryItem* room_find_item(Room *room, const char *name) {
    (void)room; (void)name;
    /* TODO: implement when room items are fully wired */
    return NULL;
}

/* Remove item from room */
void room_remove_item(Room *room, InventoryItem *item) {
    (void)room; (void)item;
    /* TODO: implement when room items are fully wired */
}

/* Broadcast message to all players in room (optionally excluding one) */
void room_broadcast(Room *room, const char *message, PlayerSession *exclude) {
    if (!room || !message) return;
    
    for (int i = 0; i < room->num_players; i++) {
        if (room->players[i] != exclude && room->players[i]->username) {
            send_to_player(room->players[i], "%s", message);
        }
    }
}

/* Look command */
void cmd_look(PlayerSession *sess, const char *args) {
    if (!sess || !sess->current_room) {
        send_to_player(sess, "You are nowhere.\n");
        return;
    }
    
    Room *room = sess->current_room;
    
    send_to_player(sess, "\n%s\n", room->name);
    send_to_player(sess, "%s\n", room->description);
    
    /* List exits */
    int exit_count = 0;
    char *exit_dirs[6];
    
    if (room->exits.north >= 0) exit_dirs[exit_count++] = "north";
    if (room->exits.south >= 0) exit_dirs[exit_count++] = "south";
    if (room->exits.east >= 0) exit_dirs[exit_count++] = "east";
    if (room->exits.west >= 0) exit_dirs[exit_count++] = "west";
    if (room->exits.up >= 0) exit_dirs[exit_count++] = "up";
    if (room->exits.down >= 0) exit_dirs[exit_count++] = "down";
    
    if (exit_count == 0) {
        send_to_player(sess, "There are no exits.\n");
    } else if (exit_count == 1) {
        send_to_player(sess, "\033[1;32mThere is one exit: %s\033[0m\n", exit_dirs[0]);
    } else {
        send_to_player(sess, "\033[1;32mThere are %d exits: ", exit_count);
        for (int i = 0; i < exit_count; i++) {
            send_to_player(sess, "%s", exit_dirs[i]);
            if (i < exit_count - 1) {
                send_to_player(sess, ", ");
            }
        }
        send_to_player(sess, "\033[0m\n");
    }
    
    /* List other players by race (until introduced) */
    if (room->num_players > 1) {
        for (int i = 0; i < room->num_players; i++) {
            if (room->players[i] != sess && room->players[i]->character.race) {
                const char *race = room->players[i]->character.race;
                
                /* Convert race name to lowercase for display */
                char lowercase_race[128];
                int j;
                for (j = 0; race[j] && j < 127; j++) {
                    lowercase_race[j] = tolower((unsigned char)race[j]);
                }
                lowercase_race[j] = '\0';
                
                /* Determine article (a/an) based on first letter */
                char article = 'A';
                if (lowercase_race[0] == 'a' || lowercase_race[0] == 'e' || 
                    lowercase_race[0] == 'i' || lowercase_race[0] == 'o' || 
                    lowercase_race[0] == 'u') {
                    article = 'n';
                }
                
                if (article == 'n') {
                    send_to_player(sess, "An %s is standing around.\n", lowercase_race);
                } else {
                    send_to_player(sess, "A %s is standing around.\n", lowercase_race);
                }
            }
        }
    }
}

/* Move command */
void cmd_move(PlayerSession *sess, const char *direction) {
    if (!sess || !sess->current_room || !direction) {
        send_to_player(sess, "You can't move.\n");
        return;
    }
    
    Room *current = sess->current_room;
    int next_room_id = -1;
    
    /* Determine direction */
    if (strcmp(direction, "north") == 0 || strcmp(direction, "n") == 0) {
        next_room_id = current->exits.north;
    } else if (strcmp(direction, "south") == 0 || strcmp(direction, "s") == 0) {
        next_room_id = current->exits.south;
    } else if (strcmp(direction, "east") == 0 || strcmp(direction, "e") == 0) {
        next_room_id = current->exits.east;
    } else if (strcmp(direction, "west") == 0 || strcmp(direction, "w") == 0) {
        next_room_id = current->exits.west;
    } else if (strcmp(direction, "up") == 0 || strcmp(direction, "u") == 0) {
        next_room_id = current->exits.up;
    } else if (strcmp(direction, "down") == 0 || strcmp(direction, "d") == 0) {
        next_room_id = current->exits.down;
    }
    
    if (next_room_id < 0) {
        send_to_player(sess, "You can't go that way.\n");
        return;
    }
    
    Room *next_room = room_get_by_id(next_room_id);
    if (!next_room) {
        send_to_player(sess, "That room doesn't exist!\n");
        return;
    }
    
    /* Notify room of departure */
    for (int i = 0; i < current->num_players; i++) {
        if (current->players[i] != sess) {
            send_to_player(current->players[i], "%s leaves %s.\n", 
                          sess->username, direction);
        }
    }
    
    /* Move player */
    room_remove_player(current, sess);
    room_add_player(next_room, sess);
    sess->current_room = next_room;
    
    /* Notify new room of arrival */
    for (int i = 0; i < next_room->num_players; i++) {
        if (next_room->players[i] != sess) {
            send_to_player(next_room->players[i], "%s arrives.\n", sess->username);
        }
    }
    
    /* Auto-look */
    cmd_look(sess, "");
}

/* Moxim Rift Travel destinations */
/* Moxim NPCs exist in rooms 4 (New Camelot), 11 (Splynn), 23 (Chi-Town) */
#define RIFT_COST 500
#define NUM_RIFT_DESTINATIONS 3

static struct {
    int room_id;
    const char *name;
    const char *keyword;
} rift_destinations[NUM_RIFT_DESTINATIONS] = {
    { 4,  "New Camelot",      "camelot" },
    { 11, "Splynn",           "splynn"  },
    { 23, "Chi-Town Transit", "chitown" },
};

/* Check if a room has a Moxim NPC */
static int room_has_moxim(int room_id) {
    for (int i = 0; i < NUM_RIFT_DESTINATIONS; i++) {
        if (rift_destinations[i].room_id == room_id) return 1;
    }
    return 0;
}

/* Rift travel command */
void cmd_rift(PlayerSession *sess, const char *args) {
    if (!sess || !sess->current_room) {
        send_to_player(sess, "You are nowhere.\n");
        return;
    }

    int current_id = sess->current_room->id;

    /* Check if a Moxim is present */
    if (!room_has_moxim(current_id)) {
        send_to_player(sess, "There is no Moxim here to open a rift.\n");
        return;
    }

    /* No argument: list destinations */
    if (!args || !args[0]) {
        send_to_player(sess, "\nThe Moxim shimmers and speaks:\n");
        send_to_player(sess, "\"I can open a rift to the following destinations.\"\n");
        send_to_player(sess, "\"Each passage costs %d credits.\"\n\n", RIFT_COST);
        for (int i = 0; i < NUM_RIFT_DESTINATIONS; i++) {
            if (rift_destinations[i].room_id == current_id) continue;
            send_to_player(sess, "  rift %-10s - %s\n",
                rift_destinations[i].keyword, rift_destinations[i].name);
        }
        send_to_player(sess, "\nYou have %d credits.\n", sess->character.credits);
        return;
    }

    /* Find matching destination */
    int dest_idx = -1;
    for (int i = 0; i < NUM_RIFT_DESTINATIONS; i++) {
        if (rift_destinations[i].room_id == current_id) continue;
        if (strcasecmp(args, rift_destinations[i].keyword) == 0 ||
            strcasecmp(args, rift_destinations[i].name) == 0) {
            dest_idx = i;
            break;
        }
    }

    if (dest_idx < 0) {
        send_to_player(sess, "The Moxim says, \"I don't know that destination.\"\n");
        send_to_player(sess, "Type 'rift' to see available destinations.\n");
        return;
    }

    /* Check credits */
    if (sess->character.credits < RIFT_COST) {
        send_to_player(sess, "The Moxim says, \"You need %d credits. You only have %d.\"\n",
            RIFT_COST, sess->character.credits);
        return;
    }

    /* Deduct credits */
    sess->character.credits -= RIFT_COST;

    Room *dest = room_get_by_id(rift_destinations[dest_idx].room_id);
    if (!dest) {
        send_to_player(sess, "The rift flickers and collapses. Something went wrong.\n");
        sess->character.credits += RIFT_COST; /* refund */
        return;
    }

    /* Notify departure room */
    Room *current = sess->current_room;
    for (int i = 0; i < current->num_players; i++) {
        if (current->players[i] != sess) {
            send_to_player(current->players[i],
                "The Moxim opens a shimmering rift. %s steps through and vanishes.\n",
                sess->username);
        }
    }

    /* Move player */
    room_remove_player(current, sess);
    room_add_player(dest, sess);
    sess->current_room = dest;

    send_to_player(sess, "\nThe Moxim opens a shimmering rift before you.\n");
    send_to_player(sess, "You step through into blinding light...\n\n");
    send_to_player(sess, "%d credits deducted. You have %d credits remaining.\n\n",
        RIFT_COST, sess->character.credits);

    /* Notify arrival room */
    for (int i = 0; i < dest->num_players; i++) {
        if (dest->players[i] != sess) {
            send_to_player(dest->players[i],
                "A shimmering rift opens and %s steps through.\n",
                sess->username);
        }
    }

    /* Auto-look */
    cmd_look(sess, "");
}

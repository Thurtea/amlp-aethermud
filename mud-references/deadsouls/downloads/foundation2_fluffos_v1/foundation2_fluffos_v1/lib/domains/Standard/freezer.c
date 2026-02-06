#include <lib.h>
inherit LIB_ROOM;

static void create() {
    room::create();
    SetShort("the freezer");
    SetLong("You are in the freezer.");
    SetExits( ([ "out" : "/domains/Standard/center" ]) );
}

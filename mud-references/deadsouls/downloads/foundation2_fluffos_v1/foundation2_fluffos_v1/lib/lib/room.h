#ifndef __ROOM_H__
#define __ROOM_H__

static void create();
void reset();
static void init();
int id(string str);

int eventMove(mixed dest);

static void LoadInventory();

void SetShort(string str);
void SetLong(string str);
string GetShort();
varargs string GetLong(string str);
object *AddExtraLong(object ob);
string GetExtraLong();
int GetResetNumber();
string *GetId();
mapping SetInventory(mapping mp);
mapping GetInventory();

#endif /* __ROOM_H__ */

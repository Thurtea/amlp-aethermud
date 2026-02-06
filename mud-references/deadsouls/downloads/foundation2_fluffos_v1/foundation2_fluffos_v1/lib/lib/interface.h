#ifndef __INTERFACE_H__
#define __INTERFACE_H__

static void create();
static string process_input(string str);
static void terminal_type(string str);
static void window_size(int width, int height);
void receive_message(string msg_class, string msg);
static void receive_snoop(string msg);

static string cache_commands(string str);
int Setup();

int SetBlocked(string type);
int GetBlocked(string type);
string SetClient(string str);
string GetClient();
int SetLogHarass(int x);
int GetLogHarass();
int *SetScreen(int width, int height);
int *GetScreen();
string SetTerminal(string terminal);
string GetTerminal();
string GetKeyName();

#endif /* __TERMINAL_H__ */

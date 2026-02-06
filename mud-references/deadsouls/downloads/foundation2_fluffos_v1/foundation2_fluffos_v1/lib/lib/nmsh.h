#ifndef __NMSH_H
#define __NMSH_H

int Setup();
nomask static int cmd_alias(string str);
nomask static int cmd_cd(string str);
nomask static int cmd_history(string str);
nomask static int cmd_nickname(string str);
nomask static int cmd_nmsh(string str);
nomask static int cmd_pushd(string str);
nomask static int cmd_popd(string str);
nomask string write_prompt();
nomask string process_input(string str);
nomask static void process_request(string request, string xtra);
static int request_vis(object ob);
static string user_name(object ob);
static private int set_cwd(string str);
static private void pushd(string str);
static private string popd();
nomask static private string do_nickname(string str);
nomask static private string do_alias(string str);
nomask static private string do_history(string str);
nomask static string replace_null(string str);
nomask static private void add_history_cmd(string str);
nomask static string replace_nickname(string str);
void reset_history();
void reset_prompt();
string query_cwd();
int query_history_size();
string GetPrompt();
string GetCapName();
string get_path();
string GetClient();
varargs int GetInvis(object ob);
string GetKeyName();
static string cache_commands(string str);

#endif /* __NMSH_H */

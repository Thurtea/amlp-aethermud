/*    /lib/command.c
 *    from the Foundation II LPC Library
 *    handles commands of living objects
 *    created by Descartes of Borg 950323
 */

#include <lib.h>
#include <daemons.h>
#include "command.h"

private static int Forced;
private static string *SearchPath;

/*  ***************  /lib/command.c driver applies  ***************  */

static void create() {
    SearchPath = ({ DIR_PLAYER_CMDS, DIR_SECURE_PLAYER_CMDS, DIR_MAGIC_CMDS });
}

static string process_input(string cmd) { return cmd; }

/*  ***************  /lib/command.c command lfuns  ***************  */

static int cmdAll(string cmd) {
    string file, verb;
    mixed tmp;

    verb = query_verb();
    if( !(file = (string)CMD_D->GetCommand(verb, SearchPath)) ) {
        if( !((int)SOUL_D->do_cmd(verb, cmd)) ) { 
            if(GetClient()) receive("<error>");
            return 0;
        }
        else return 1;
    }
    if( !(tmp = (mixed)call_other(file, "cmd", cmd)) ) {
        if(GetClient()) receive("<error>");
        return 0;
    }
    else if( stringp(tmp) ) {
        message("error", tmp, this_object());
        return 1;
    }
    else return 1;
}

/*  ***************  /lib/command.c lfuns  ***************  */

int Setup() {
    enable_commands();
    add_action( (: cmdAll :), "", 1);
}

int eventForce(string cmd) {
    string err;
    int res;

    cmd = process_input(cmd);
    Forced = 1;
    err = catch(res = command(cmd));
    Forced = 0;
    if(err) error(err);
    return res;
}

/*  **********  /lib/command.c data manipulation functions  ********** */

string *AddSearchPath(mixed val) {
    if(stringp(val)) val = ({ val });
    else if(!pointerp(val)) error("Bad argument 1 to AddSearchPath()\n");
    return (SearchPath = distinct_array(SearchPath + val));
}

string *RemoveSearchPath(mixed val) {
    if(stringp(val)) val = ({ val });
    else if(!pointerp(val)) error("Bad argument 1 to RemoveSearchPath()\n");
    return (SearchPath -= val);
}

string *GetSearchPath() { return SearchPath; }

int GetForced() { return Forced; }

string GetClient() { return 0; }

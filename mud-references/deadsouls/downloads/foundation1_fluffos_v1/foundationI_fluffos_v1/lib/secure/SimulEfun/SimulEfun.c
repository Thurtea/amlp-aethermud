/*    /secure/obj/SimulEfun.c
 *    from Nightmare IV
 *    the mud SimulEfun object
 *    created by Descartes of Borg 940213
 */

#include <objects.h>
#include <localtime.h>
#include "SimulEfun.h"

#include "/secure/SimulEfun/absolute_value.c"
#include "/secure/SimulEfun/alignment.c"
#include "/secure/SimulEfun/base_name.c"
#include "/secure/SimulEfun/communications.c"
#include "/secure/SimulEfun/convert_name.c"
#include "/secure/SimulEfun/copy.c"
#include "/secure/SimulEfun/distinct_array.c"
#include "/secure/SimulEfun/domains.c"
#include "/secure/SimulEfun/english.c"
#include "/secure/SimulEfun/events.c"
#include "/secure/SimulEfun/exclude_array.c"
#include "/secure/SimulEfun/files.c"
#include "/secure/SimulEfun/format_page.c"
#include "/secure/SimulEfun/format_string.c"
#include "/secure/SimulEfun/get_object.c"
#include "/secure/SimulEfun/identify.c"
#include "/secure/SimulEfun/idle.c"
#include "/secure/SimulEfun/interact.c"
#include "/secure/SimulEfun/interface.c"
#include "/secure/SimulEfun/light.c"
#include "/secure/SimulEfun/load_object.c"
#include "/secure/SimulEfun/log_file.c"
#include "/secure/SimulEfun/mud_info.c"
#include "/secure/SimulEfun/ordinal.c"
#include "/secure/SimulEfun/parse_objects.c"
#include "/secure/SimulEfun/path_file.c"
#include "/secure/SimulEfun/percent.c"
#include "/secure/SimulEfun/pointers.c"
#include "/secure/SimulEfun/read_database.c"
#include "/secure/SimulEfun/absolute_path.c"
#include "/secure/SimulEfun/security.c"
#include "/secure/SimulEfun/strings.c"
#include "/secure/SimulEfun/substr.c"
#include "/secure/SimulEfun/time.c"
#include "/secure/SimulEfun/to_object.c"
#include "/secure/SimulEfun/translate.c"
#include "/secure/SimulEfun/user_exists.c"
#include "/secure/SimulEfun/user_path.c"
#include "/secure/SimulEfun/visible.c"

int tail(string file) {
    string str;
    int diff;

    diff = file_size(file);
    if (diff < 0) return 0;

    diff -= 1024;
    if (diff < 0) diff = 0;
    str = read_bytes(file, diff, 1024);
    if (!str) return 0;
    if (diff) str = str[strsrch(str, "\n")+1..];

    write(str);

    return 1;
}

string timestamp(){
    string rawtz;
    int *t, gmtoff, offset;

    gmtoff = localtime(time())[LT_GMTOFF];

    t = localtime(time());
    return sprintf("%04d.%02d.%02d-%02d.%02d", t[LT_YEAR], (t[LT_MON])+1, t[LT_MDAY], t[LT_HOUR], t[LT_MIN]);
}

varargs string get_stack( int x) {
    int i, s;
    string list = "";
    string *stack0 = call_stack(0);
    string *stack1 = call_stack(1);
    string *stack2 = call_stack(2);
    for(i = 0, s = sizeof(stack1); i < s; i++){
        list +="\n"+i+":"+identify(stack2[i])+"."+identify(stack1[i])+"."+identify(stack2[i]);
    }

    if(x){
        list += "\n"+ identify(previous_object(-1));
    }

    return list;
}

void tc(string mess){
    object crat = find_player("god");
    string sauce = base_name((previous_object() || this_object()));
    if(crat) tell_object(crat, sauce +": "+mess+"\n");
    //if(crat) crat->receive_private_msg(sauce+": "+mess, PRIVATE_MSG);
    debug_message(sauce +": "+mess);
    flush_messages();
}

string dump_socket_status() {
    string ret;
    string *finalsocks, *sock_array = ({});
    int i, quant = sizeof(socket_status());
    for(i = 0; i < quant; i++){
        sock_array += ({ socket_status(i) });
    }
    finalsocks = sock_array;

    ret = @END
Fd    State      Mode       Local Address          Remote Address
--  ---------  --------  ---------------------  ---------------------
END;

    foreach (mixed *item in finalsocks) {
        int memb = member_array(item, finalsocks);
        ret += sprintf("%2d  %|9s  %|8s  %-21s  %-21s\n", memb, item[1], item[2], item[3], item[4]);
    }

    return ret;
}

int destruct(object ob) {
    string *privs;
    string tmp;
   
    if(previous_object(0) == ob) return efun::destruct(ob);
    if(!(tmp = query_privs(previous_object(0)))) return 0;
    if(member_array(PRIV_SECURE, explode(tmp, ":")) != -1)
      return efun::destruct(ob);
    privs = ({ file_privs(file_name(ob)) });
    if((int)master()->valid_apply(({ "assist" }) + privs))
      return efun::destruct(ob);
    else return 0;
}
    
varargs void shutdown(int code) {
    if(!((int)master()->valid_apply(({})))) return;
    if(this_player())
      log_file("shutdowns", (string)this_player()->query_CapName()+
        " shutdown "+mud_name()+" at "+ctime(time())+"\n");
    else log_file("shutdowns", "Game shutdown by "+
      file_name(previous_object(0))+" at "+ctime(time())+"\n");
    catch(NETWORK_D->send_shutdown());
    efun::shutdown(code);
}

varargs object snoop(object who, object target) {
    if(!target) return efun::snoop(who);
    if(!creatorp(who)) return 0;
    if(!((int)master()->valid_apply(({ "assist" })))) {
        if(!((int)target->query_snoopable())) return 0;
        else return efun::snoop(who, target);
    }
    else if(member_group(target, PRIV_SECURE)) {
        message("system", (string)who->query_CapName()+" is now snooping "
          "you.", target);
        return efun::snoop(who, target);
    }
    else return efun::snoop(who, target);
}

object query_snoop(object ob) {
    if(!userp(previous_object(0))) return 0;
    return efun::query_snoop(ob);
}

object query_snooping(object ob) {
    if(!((int)master()->valid_apply(({})))) return 0;
    else return efun::query_snooping(ob);
}

int exec(object target, object src) {
    if(base_name(previous_object(0)) != OB_LOGIN) return 0;
    return efun::exec(target, src);
}

void write(string str) {
    if(this_player()) message("my_action", str, this_player());
    else efun::write(str);
}

object *livings() {
    return efun::livings() - (efun::livings() - objects());
}

void set_privs(object ob, string str) { return; }

void set_eval_limit(int x) {
    if(previous_object() != master()) return;
    efun::set_eval_limit(x);
}

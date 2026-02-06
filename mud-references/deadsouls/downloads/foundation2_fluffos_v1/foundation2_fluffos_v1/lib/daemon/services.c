/*    /daemon/services.c
 *    from the Nightmare IV LPC Library
 *    handles intermud services
 *    created by Descartes of Borg 950523
 */

#ifndef __PACKAGE_SOCKETS__
#error You should not try to load /daemon/services.c without the sockets package
#else

#include <lib.h>
#include <network.h>

inherit LIB_DAEMON;

mapping GetServices();

static void create() {
    daemon::create();
    SetNoClean(1);
}

#include "/daemon/services/channel.c"
#include "/daemon/services/emoteto.c"
#include "/daemon/services/error.c"
#include "/daemon/services/finger.c"
#include "/daemon/services/locate.c"
#include "/daemon/services/tell.c"
#include "/daemon/services/who.c"

mapping GetServices() {
    return ([
#ifdef SERVICE_AUTH
	     "auth" : 1,
#endif
#ifdef SERVICE_CHANNEL
	     "channel" : 1,
#endif
#ifdef SERVICE_EMOTETO
	     "emoteto" : 1,
#endif
#ifdef SERVICE_FILE
	     "file" : 1,
#endif
#ifdef SERVICE_FINGER
	     "finger" : 1,
#endif
#ifdef SERVICE_LOCATE
	     "locate" : 1,
#endif
#ifdef SERVICE_MAIL
	     "mail" : 1,
#endif
#ifdef SERVICE_NEWS
	     "news" : 1,
#endif
#ifdef SERVICE_TELL
	     "tell" : 1,
#endif
#ifdef SERVICE_UCACHE
	     "ucache" : 1,
#endif
#ifdef SERVICE_WHO
	     "who" : 1,
#endif
#ifdef PORT_FTP
	     "ftp" : PORT_FTP,
#endif
#ifdef PORT_HTTP
	     "http" : PORT_HTTP,
#endif
#ifdef PORT_NNTP
	     "nntp" : PORT_NNTP,
#endif
#ifdef PORT_RCP
	     "rcp" : PORT_RCP,
#endif
#ifdef PORT_SMTP
	     "smtp" : PORT_SMTP,
#endif
	     ]);
}

#endif /* __PACKAGE_SOCKETS__ */

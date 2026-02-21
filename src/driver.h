/* driver.h - shared driver symbols exposed to other modules */
#ifndef DRIVER_H
#define DRIVER_H

#include <signal.h>
#include <time.h>

/* Server control flag (defined in driver.c) */
extern int server_running;

/* Callout scheduler ------------------------------------------------------- */

#define MAX_CALLOUTS 256
#define MAX_CALLOUT_FUNC_NAME 128

typedef struct {
    int      active;                       /* 1 if slot in use */
    time_t   fire_at;                      /* absolute time to fire */
    char     func_name[MAX_CALLOUT_FUNC_NAME]; /* function to call */
    int      handle;                       /* unique handle returned to LPC */
} Callout;

/* Schedule a callout. Returns a positive handle, or -1 on failure. */
int callout_schedule(const char *func_name, double delay_seconds);

/* Cancel a callout by handle. Returns 0 on success, -1 if not found. */
int callout_cancel(int handle);

#endif /* DRIVER_H */

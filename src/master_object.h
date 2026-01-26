#ifndef MASTER_OBJECT_H
#define MASTER_OBJECT_H

#include "compiler.h"

/* Initialize master object from file and set up VM */
int master_object_init(const char *path, VirtualMachine *vm);

/* Register master object callbacks with the driver */
int master_register_callbacks(void);

/* Callback functions - invoked by driver, implemented by master object */
void master_callback_compile_object(const char *filename);
void master_callback_log_error(const char *filename, const char *message);
void master_callback_query_version(void);

/* Cleanup function - call at server shutdown */
void master_object_cleanup(void);

#endif /* MASTER_OBJECT_H */

#ifndef AMLP_DEBUG_H
#define AMLP_DEBUG_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Debug output control
 * Can be enabled via:
 * 1. Environment variable: export AMLP_DEBUG=1
 * 2. Compile flag: gcc -DAMLP_DEBUG_ENABLED
 */

#define AMLP_DEBUG_VERBOSE() (getenv("AMLP_DEBUG") != NULL)

/* Debug logging macros - only output if debug enabled */
#define DEBUG_LOG(fmt, ...) \
    do { \
        if (AMLP_DEBUG_VERBOSE()) { \
            fprintf(stderr, "[DEBUG] " fmt "\n", ##__VA_ARGS__); \
        } \
    } while(0)

#define DEBUG_LOG_VM(fmt, ...) \
    do { \
        if (AMLP_DEBUG_VERBOSE()) { \
            fprintf(stderr, "[VM] " fmt "\n", ##__VA_ARGS__); \
        } \
    } while(0)

#define DEBUG_LOG_STACK(fmt, ...) \
    do { \
        if (AMLP_DEBUG_VERBOSE()) { \
            fprintf(stderr, "[STACK] " fmt "\n", ##__VA_ARGS__); \
        } \
    } while(0)

#define DEBUG_LOG_OBJ(fmt, ...) \
    do { \
        if (AMLP_DEBUG_VERBOSE()) { \
            fprintf(stderr, "[Object] " fmt "\n", ##__VA_ARGS__); \
        } \
    } while(0)

#define DEBUG_LOG_PARAM(fmt, ...) \
    do { \
        if (AMLP_DEBUG_VERBOSE()) { \
            fprintf(stderr, "[Param] " fmt "\n", ##__VA_ARGS__); \
        } \
    } while(0)

#define DEBUG_LOG_EFUN(fmt, ...) \
    do { \
        if (AMLP_DEBUG_VERBOSE()) { \
            fprintf(stderr, "[Efun] " fmt "\n", ##__VA_ARGS__); \
        } \
    } while(0)

/* Important errors and warnings - ALWAYS shown */
#define WARN_LOG(fmt, ...) \
    fprintf(stderr, "[WARNING] " fmt "\n", ##__VA_ARGS__)

#define ERROR_LOG(fmt, ...) \
    fprintf(stderr, "[ERROR] " fmt "\n", ##__VA_ARGS__)

#define FATAL_LOG(fmt, ...) \
    fprintf(stderr, "[FATAL] " fmt "\n", ##__VA_ARGS__)

#define INFO_LOG(fmt, ...) \
    fprintf(stderr, "[INFO] " fmt "\n", ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif /* AMLP_DEBUG_H */

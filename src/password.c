#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <crypt.h>

#include "password.h"

const char *hash_password(const char *plaintext) {
    static char buf[128];
    if (!plaintext) { buf[0] = '\0'; return buf; }

    /* Read 16 bytes of entropy for the bcrypt salt */
    unsigned char raw[16] = {0};
    FILE *urnd = fopen("/dev/urandom", "rb");
    if (urnd) {
        (void)fread(raw, 1, sizeof(raw), urnd);
        fclose(urnd);
    } else {
        /* Fallback: LCG seeded from time (only if /dev/urandom unavailable) */
        unsigned int s = (unsigned int)time(NULL);
        for (int i = 0; i < 16; i++) { s = s * 1664525u + 1013904223u; raw[i] = (unsigned char)(s >> 16); }
    }

    /* Encode 16 bytes → 22 bcrypt-base64 chars (./A-Za-z0-9 alphabet) */
    static const char B64[] = "./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    char salt[30];
    memcpy(salt, "$2b$10$", 7);
    int j = 7;
    for (int i = 0; i + 2 < 16; i += 3) {
        unsigned c1 = raw[i], c2 = raw[i+1], c3 = raw[i+2];
        salt[j++] = B64[c1 >> 2];
        salt[j++] = B64[((c1 & 3) << 4) | (c2 >> 4)];
        salt[j++] = B64[((c2 & 0xf) << 2) | (c3 >> 6)];
        salt[j++] = B64[c3 & 0x3f];
    }
    /* one remaining byte (raw[15]) */
    salt[j++] = B64[raw[15] >> 2];
    salt[j++] = B64[(raw[15] & 3) << 4];
    salt[j]   = '\0'; /* salt is now "$2b$10$<22 chars>" */

    static struct crypt_data cd;
    const char *h = crypt_r(plaintext, salt, &cd);
    if (!h) { buf[0] = '\0'; return buf; }
    strncpy(buf, h, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';
    return buf;
}

int verify_password(const char *plaintext, const char *stored_hash) {
    if (!plaintext || !stored_hash || !stored_hash[0]) return 0;
    static struct crypt_data cd;
    const char *h = crypt_r(plaintext, stored_hash, &cd);
    if (!h) return 0;
    return strcmp(h, stored_hash) == 0;
}

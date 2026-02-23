#ifndef PASSWORD_H
#define PASSWORD_H

/* hash_password - bcrypt-hash plaintext with cost 10.
 * Returns pointer to a static buffer (≤60 chars + NUL).
 * Valid until the next call to hash_password(). */
const char *hash_password(const char *plaintext);

/* verify_password - verify plaintext against a stored bcrypt hash.
 * Returns 1 on match, 0 on mismatch or error. */
int verify_password(const char *plaintext, const char *stored_hash);

#endif /* PASSWORD_H */

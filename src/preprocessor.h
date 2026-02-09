/**
 * preprocessor.h - LPC Preprocessor
 *
 * Handles #include, #define, #ifdef/#ifndef/#else/#endif,
 * and macro expansion for LPC source files.
 */

#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

/**
 * Preprocess LPC source code.
 *
 * Processes all preprocessor directives and expands macros.
 * Returns a newly allocated string with preprocessed source.
 * Caller must free() the result.
 *
 * @param source   Raw LPC source code
 * @param filename Filesystem path to the source file (for resolving includes)
 * @return         Preprocessed source, or NULL on error
 */
char* preprocess_lpc(const char *source, const char *filename);

#endif /* PREPROCESSOR_H */

/**
 * General kernel utilities. Must be accessed via the KUTILS() macro.
 *
 * Utilities in this header:
 * oct2bin
 * memeq
 * strlen
 */

#ifndef APRICOT_KUTILS_H
#define APRICOT_KUTILS_H

#include <spec.h>
#include <stdbool.h>
#include <stddef.h>

#define KUTILS(x) concat(k, x)

/**
 * Converts an ASCII octal number to binary.
 */
int KUTILS(oct2bin)(const char *str, size_t size);

/**
 * Checks if two given blocks of memory are equal.
 */
bool KUTILS(memeq)(const void *mem1, const void *mem2, size_t size);

/**
 * Returns the length of the specified NULL-terminated string.
 */
size_t KUTILS(strlen)(const char *str);

#endif //APRICOT_KUTILS_H

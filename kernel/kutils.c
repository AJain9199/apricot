/**
 * Implementation of general kernel utilities.
 */

#include <apricot/kutils.h>
#include <stdint.h>

int KUTILS(oct2bin) (const char *str, size_t size) {
    int n = 0;
    const char *c = str;
    while (size-- > 0) {
        n *= 8;
        n += *c - '0';
        c++;
    }
    return n;
}

bool KUTILS(memeq) (const void *mem1, const void *mem2, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (((uint8_t *)mem1)[i] != ((uint8_t*)mem2)[i]) {
            return false;
        }
    }

    return true;
}

size_t KUTILS(strlen) (const char *str) {
    const char *s;
    for (s = str; *s; ++s);
    return (s - str);
}
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

void *KUTILS(memmove)(void *to, void *from, size_t count) {
    void *ret = from;
    uint8_t *t = (uint8_t *) to;
    uint8_t *f = (uint8_t *) from;

    if (f > t) {
        for ( ; count > 0; count--) {
            *(t++)= *(f++);
        }
    } else {
        for (t+= count-1, f+= count-1; count > 0; count--) {
            *(t--)= *(f--);
        }
    }

    return ret;
}

void *KUTILS(memset32)(void *target, uint32_t value, size_t count) {
    uint32_t *t = (uint32_t *) target;
    for (int i = 0; i < count; i++) {
        *t = value;
        t++;
    }
    return target;
}
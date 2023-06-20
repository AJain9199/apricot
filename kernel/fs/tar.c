/**
 * Implementation of various utility functions for the (US)TAR filesystem. Must be accessed via the TAR() macro.
 */

#include <apricot/fs.h>
#include <apricot/kutils.h>

int TAR(getfile)(uint8_t *tar, char *filename, uint8_t **OUT(file)) {
    uint8_t *tar_ptr = tar;
    while (KUTILS(memeq)(tar_ptr + 257, "ustar", 5)) {
        int fsize = KUTILS(oct2bin)((char *) tar_ptr + 0x7C, 11);
        if (KUTILS(memeq)(tar_ptr, filename, KUTILS(strlen)(filename))) {
            *file = tar_ptr + 512;
            return fsize;
        }

        tar_ptr += (((fsize + 511) / 512) + 1) * 512;
    }
    return 0;
}

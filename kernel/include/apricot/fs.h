/**
 * A header with prototype declarations for all filesystem-related functions implemented by source files in the
 * kernel/fs directory. Must be accessed by the specific macro of the filesystem.
 *
 * Supported filesystems:
 * (US)TAR
 */

#ifndef APRICOT_FS_H
#define APRICOT_FS_H

#include <stdint.h>
#include <spec.h>

// add a "tar_" prefix to all functions related to the TAR filesystem
#define TAR(x)     concat(tar_, x)

/**
 * Searches for a returns a pointer to a file in the TAR filesystem
 * @param tar Pointer to the TAR archive
 * @param filename Name of the desired file
 * @param file Is set to a pointer to the requested file if found, NULL otherwise
 * @return Size of the requested file if found, -1 otherwise
 */
int TAR(getfile)(uint8_t *tar, char *filename, uint8_t **OUT(file));

#endif //APRICOT_FS_H

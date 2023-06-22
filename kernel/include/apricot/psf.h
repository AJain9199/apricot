/**
 * Facilitates handling of PC Screen Fonts (PSFs).
 */

#ifndef APRICOT_PSF_H
#define APRICOT_PSF_H

#include <stdint.h>
#include <apricot/color.h>

#define PSF2_MAGIC 0x864ab572  // First 4 bytes of a valid PSF2 header

#define DEFAULT_FONT "Tamsyn8x16r.psf"
#define CHAR_HEIGHT 16
#define CHAR_WIDTH 9

/**
 * Represents a PSF2 font.
 */
typedef struct {
    uint32_t magic;
    uint32_t version;
    uint32_t header_size;
    uint32_t flags;
    uint32_t num_glyphs;
    uint32_t glyph_size;  // bytes per glyph
    uint32_t glyph_height;
    uint32_t glyph_width;
} PSF2_t;

/**
 * Initialize the PC Screen Font for global use by the kernel.
 * @param initrd Pointer to the kernel's initrd
 */
void psf_init(uint8_t *initrd);

/**
 * Output a character to the screen.
 * @param c The character to display.
 * @param cx The X-coordinate of the character to display (in characters, not pixels).
 * @param cy The X-coordinate of the character to display (in characters, not pixels).
 * @param fg The color in which the character will be displayed.
 */
void psf_putc(char c, int cx, int cy, color fg);

#endif //APRICOT_PSF_H

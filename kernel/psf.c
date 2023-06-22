#include <apricot/psf.h>
#include <apricot/fs.h>
#include <stddef.h>
#include <spec.h>
#include "bootboot.h"

static unsigned int bytes_per_line; // no of bytes that encode one line
PSF2_t *font;
extern BOOTBOOT bootboot;

void psf_init(uint8_t *initrd) {
    uint8_t *psf = NULL;
    TAR(getfile) (initrd, DEFAULT_FONT, &psf);
    font = (PSF2_t *)psf;

    bytes_per_line = (font->glyph_width + 7) / 8;
}

void psf_putc(char c, int cx, int cy, color fg) {
    uint8_t *glyph = ((uint8_t *) font) + font->header_size + (c > 0 && c < font->num_glyphs ? c : 0) * font->glyph_size;

    uint offset = (cy * font->glyph_height * bootboot.fb_scanline) + (cx * (font->glyph_width + 1) * 4); // + 1 to ensure 1 pixel gap between characters
    for (int i = 0; i < font->glyph_height; i++) {
        uint line = offset;
        uint mask = 1 << (font->glyph_width - 1);

        for (int j = 0; j < font->glyph_width; j++) {
            if (*((uint32_t *) glyph) & mask) {
                *((color *)(bootboot.fb_ptr + line)) = fg;
            }
            mask >>= 1;
            line += 4;
        }

        glyph += bytes_per_line;
        offset += bootboot.fb_scanline;
    }
}
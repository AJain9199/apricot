/**
 * Utilities to represent colors for a display agnostic interface.
 */

#include <apricot/color.h>
#include <bootboot.h>

extern BOOTBOOT bootboot;

color gen_color(uint8_t r, uint8_t g, uint8_t b) {
    switch (bootboot.fb_type) {
        case FB_ARGB:
            return (color)(r << 16 | g << 8 | b);
        case FB_RGBA:
            return (color)(r << 24 | g << 16 | b << 8);
        case FB_ABGR:
            return (color)(b << 16 | g << 8 | r);
        case FB_BGRA:
            return (color)(b << 24 | g << 16 | r << 8);
        default:
            return 0;
    }
}
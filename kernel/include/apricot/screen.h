/**
 * Basic utilities relating to the screen
 */

#ifndef APRICOT_SCREEN_H
#define APRICOT_SCREEN_H

#include <apricot/color.h>
#include <stdint.h>
#include <bootboot.h>

typedef uint32_t pixel;

typedef struct {
    pixel *fb;
    uint32_t size;
    uint32_t width;
    uint32_t height;
    uint32_t scanline;
} screen_t;

/**
 * Initializes the screen for use by the kernel by initializing the screen_t structure.
 * @param fb Virtual address of the framebuffer.
 * @param boot_info The boot information structure.
 */
void init_screen(uint8_t *fb, BOOTBOOT boot_info);

/**
 * Fill the entire screen with the specified color
 * @param fill The color values to fill.
 */
void fill_screen(pixel fill);

/**
 * Fill a specified rectangle with the specified color.
 * @param x X-coordinate of the top-left corner of the rectangle (in pixels).
 * @param y Y-coordinate of the top-left corner of the rectangle (in pixels).
 * @param width Width of the rectangle (in pixels).
 * @param height Height of the rectangle (in pixels).
 * @param fill The color to fill.
 */
void fill_rect(int x, int y, int width, int height, color fill);

/**
 * Scroll the screen by the number of rows specified.
 *
 * Scrolls the screen by the specified pixel rows by moving the existing rows upwards,
 * while "deleting" the top n rows of pixels.
 * @param num_rows The number of pixel rows to scroll.
 */
void scroll_screen(int num_rows);

/**
 * Fully functional wrapper for psf.h's psf_putc.
 *
 * Implements proper sequential printing, complete with '\n' functionality and scrolling the screen when text reaches the bottom-most row.
 * @param c The character to print.
 */
void putc(char c);

#endif //APRICOT_SCREEN_H

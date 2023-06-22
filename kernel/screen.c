#include <apricot/screen.h>
#include <apricot/kutils.h>
#include <bootboot.h>
#include <apricot/screen.h>
#include <apricot/psf.h>

screen_t screen;

void init_screen(uint8_t *fb, BOOTBOOT boot_info) {
    screen.fb = (pixel *)fb;
    screen.size = boot_info.size;
    screen.height = boot_info.fb_height;
    screen.width = boot_info.fb_width;
    screen.scanline = boot_info.fb_scanline / 4;
}

void fill_screen(color fill) {
    pixel *target_fb = (pixel *)screen.fb;

    for (int y = 0; y < screen.height; y++) {
        for (int x = 0; x < screen.width; x++) {
            *((target_fb + x)) = fill;
        }
        target_fb += screen.scanline;
    }
}

void scroll_screen(int num_rows) {
    KUTILS(memmove)(screen.fb, screen.fb + num_rows * screen.scanline, screen.height * screen.scanline - num_rows * screen.width);
    for (int i = 0; i <= num_rows; i++) {
        KUTILS(memset32)(screen.fb + (screen.height - num_rows + i) * screen.scanline, gen_color(BG), screen.width);
    }
}

void fill_rect(int x, int y, int width, int height, color fill) {
    pixel *target_fb = (pixel *) screen.fb + x + y * screen.scanline;
    for (int iy = 0; iy < height; iy++) {
        for (int ix = 0; ix < width; ix++) {
            *(target_fb + ix) = fill;
        }
        target_fb += screen.scanline;
    }
}

/**
 * Helper function for incrementing the y-axis in putc, and scrolls the screen if y exceeds the screen limit.
 */
static int inc_y(int y) {
    if (y > (screen.height / CHAR_HEIGHT)) {
        scroll_screen(CHAR_HEIGHT);
        return y-1;
    }

    return y+1;
}

void putc(char c) {
    static int x = 0;
    static int y = 0;

    if (c == '\n') {
        x = 0;
        y = inc_y(y);
        return;
    }

    if (x > (screen.width / CHAR_WIDTH)) {
        x = 0;
        y = inc_y(y);
    }


    psf_putc(c, x, y, gen_color(FG));
    x++;
}

#include <stdint.h>
#include <bootboot.h>
#include <C17.h>
#include <apricot/psf.h>
#include <apricot/screen.h>
#include <apricot/printf.h>

#include <apricot/arch.h>

extern BOOTBOOT bootboot;
extern unsigned char environment[4096];
extern uint8_t fb;
extern void _init();

noreturn void apricot_main() {
    _init();
    arch_init();
    init_screen(&fb, bootboot);
    psf_init((uint8_t *)bootboot.initrd_ptr);
    fill_screen(gen_color(BG));
    printf("Hello from %s!\n");
    printf("Framebuffer initialized at 0x%llx", &fb);
    while (1) {

    }
}
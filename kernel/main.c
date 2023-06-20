
#include <stdint.h>
#include <bootboot.h>
#include <C17.h>

extern BOOTBOOT boot_info;
extern unsigned char environment[4096];
extern uint8_t fb;


noreturn void apricot_main() {
    *((uint32_t *) &fb) = 0xFFFFFF;
    while (1) {

    }
}
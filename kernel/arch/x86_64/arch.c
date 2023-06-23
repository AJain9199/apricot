#include <apricot/arch.h>
#include <apricot/gdt.h>

void arch_init() {
    gdt_init();
}
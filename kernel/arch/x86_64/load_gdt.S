.section .text

.tss_flush:
    mov $0x28, %ax
    ltr %ax
    ret

/**
 * Loads the GDT into the GDTR register, and then reloads segment registers. CS is reloaded via a far return. The TSS
 * descriptor is also loaded.
*/
.global setGDT
.type setGDT, @function
setGDT:
    lgdt (%rdi)
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss

    push $0x08
    lea .tss_flush(%rip), %rax
    pushq %rax
    lretq
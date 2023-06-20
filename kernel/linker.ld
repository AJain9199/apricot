ENTRY(apricot_main)

mmio        = 0xfffffffff8000000;              /* these are configurable for level 2 loaders */
fb          = 0xfffffffffc000000;
bootboot    = 0xffffffffffe00000;
environment = 0xffffffffffe01000;

PHDRS {
  boot PT_LOAD;                                /* one single loadable segment */
}

SECTIONS {
    . = 0xffffffffffe02000;
    .text : {
        KEEP(*(.text.boot)) *(.text .text.*)
        *(.rodata .rodata.*)
        *(.data .data.*)
    } :boot

    .bss (NOLOAD) : {
        . = ALIGN(16);
        *(.bss .bss.*)
        *(COMMON)
    } :boot

    /DISCARD/ : { *(.eh_frame) *(.comment) }
}
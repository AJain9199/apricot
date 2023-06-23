#ifndef APRICOT_GDT_H
#define APRICOT_GDT_H

#include <stdint.h>
#include <C17.h>

/**
 * Internal representation of the GDTR register that points to the GDT. Loaded by LGDT instruction.
 */
typedef struct {
    uint16_t size;
    uint64_t offset;
} packed gdtr_t;

/**
 * Internal representation of a segment descriptor in the GDT.
 */
typedef struct {
    uint16_t limit_lo;
    uint32_t base_lo : 24;
    uint8_t access;
    uint8_t limit_hi : 4;
    uint8_t flags: 4;
    uint8_t base_hi;
} packed gdte_t;

/*
 * Flags for the access byte in the segment descriptor.
 */
#define ACCESS(x) ((1 << 7) | x)
#define DPL(x) (x << 5)
#define CODE_DATA_SEG (1 << 4)
#define EXEC (1 << 3)
#define CONFORM (1 << 2)
#define READABLE_CODE_SEG (1 << 1)
#define WRITABLE_DATA_SEG (1 << 1)

/*
 * Flags in the segment descriptor.
 */
#define PAGE_GRAN (1 << 3)
#define CODE (1 << 1)
#define DATA (1 << 2)

#define NUM_ENTRIES 5

/**
 * Internal representation of a system descriptor in the GDT.
 */
typedef struct {
    uint16_t limit_lo;
    uint32_t base_lo : 24;
    uint8_t access;
    uint8_t limit_hi : 4;
    uint8_t flags: 4;
    uint64_t base_hi : 40;
    uint32_t reserved;
} packed gdte_sys_t;

/*
 * Type field in the access byte of the system descriptor
 */
#define TYPE_TSS (0x9)

#define NUM_SYS_ENTRIES (1)
#define SIZE_SYS_ENTRY (2) // a system descriptor is twice the size of a segment descriptor


/**
 * Initialize the GDT as well as the TSS.
 */
 void gdt_init();

#endif //APRICOT_GDT_H

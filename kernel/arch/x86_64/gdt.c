/**
* Implements handling of the Global Descriptor Table on x86_64
*/

#include <apricot/gdt.h>
#include <spec.h>
#include <apricot/tss.h>

static gdte_t GDT[NUM_ENTRIES + NUM_SYS_ENTRIES * SIZE_SYS_ENTRY] = {0};
static tss_t TSS;

extern void setGDT(gdtr_t *);

/**
 * Initializes a GDT segment entry.
 * @param idx 0-base index of the entry.
 * @param base Base value of the segment (always 0 on x86_64).
 * @param limit Limit value of the segment (always 0xFFFFF on x86_64, except the null descriptor).
 * @param access Access byte of the segment.
 * @param flags Flags of the segment.
 */
static void gdt_entry(uint idx, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);

/**
 * Initializes a system descriptor entry in the GDT/
 * @param idx 0-base index of the entry. The entry will occupy the given index and also idx+1, since a system descriptor occupies twice the space as a segment descriptor
 * @param base Pointer to the system descriptor structure (TSS or LDT).
 * @param size Size of the system descriptor structure (TSS or LDT).
 * @param access Access byte of the system descriptor.
 * @param flags Flags of the system descriptor.
 */
static void gdt_sysentry(uint idx, uint64_t base, uint32_t size, uint8_t access, uint8_t flags);

void gdt_init() {
    gdt_entry(0, 0, 0, 0, 0); // NULL descriptor
    gdt_entry(1, 0, 0xFFFFF, ACCESS((DPL(0) | CODE_DATA_SEG | EXEC | READABLE_CODE_SEG)), PAGE_GRAN | CODE); // Kernel code
    gdt_entry(2, 0, 0xFFFFF, ACCESS((DPL(0) | CODE_DATA_SEG | WRITABLE_DATA_SEG)), PAGE_GRAN | DATA); // Kernel data
    gdt_entry(3, 0, 0xFFFFF, ACCESS((DPL(3) | CODE_DATA_SEG | EXEC | READABLE_CODE_SEG)), PAGE_GRAN | CODE); // User code
    gdt_entry(4, 0, 0xFFFFF, ACCESS((DPL(3) | CODE_DATA_SEG | WRITABLE_DATA_SEG)), PAGE_GRAN | DATA); // User data
    gdt_sysentry(5, (uint64_t)(&TSS), sizeof(tss_t), ACCESS((DPL(0) | TYPE_TSS)), 0); // TSS

    gdtr_t GDTR = (gdtr_t) {.offset = (uint64_t)(&(GDT[0])), .size = (sizeof(gdte_t) * (NUM_ENTRIES + NUM_SYS_ENTRIES * SIZE_SYS_ENTRY)) - 1};
    setGDT(&GDTR);
}

void gdt_entry(uint idx, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    gdte_t *entry = &(GDT[idx]);
    entry->limit_lo = limit & 0xFFFF;
    entry->base_lo = base & 0xFFFFFF;
    entry->access = access;
    entry->limit_hi = (limit >> 16) & 0xF;
    entry->flags = flags & 0xF;
    entry->base_hi = (base >> 24) & 0xFF;
}

void gdt_sysentry(uint idx, uint64_t base, uint32_t size, uint8_t access, uint8_t flags) {
    gdte_sys_t *entry = (gdte_sys_t *) &(GDT[idx]);
    entry->base_lo = base & 0xFFFFFF;
    entry->base_hi = (base >> 24) & 0xFFFFFFFFFF;
    entry->limit_lo = size & 0xFFFF;
    entry->limit_hi = (size >> 16) & 0xF;
    entry->access = access;
    entry->flags = flags;
}
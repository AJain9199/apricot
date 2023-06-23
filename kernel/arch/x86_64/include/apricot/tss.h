/**
 * Internal representation of the Task State Segment (TSS)
 */

#ifndef APRICOT_TSS_H
#define APRICOT_TSS_H

#include <stdint.h>
#include <spec.h>

typedef struct {
    uint32_t res;
    uint64_t rsp[3];
    uint64_t res1;
    uint64_t ist[7];
    uint64_t res2;
    uint16_t res3;
    uint16_t iopb;
} packed tss_t;

#endif //APRICOT_TSS_H

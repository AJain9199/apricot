/**
 * Display agnostic color representation.
 */

#ifndef APRICOT_COLOR_H
#define APRICOT_COLOR_H

#include <stdint.h>

typedef uint32_t color;
color gen_color(uint8_t r, uint8_t g, uint8_t b);

#endif //APRICOT_COLOR_H

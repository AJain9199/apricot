/**
 * @brief Small header file with macros to make the kernel code C standard agnostic. For- C17
 *
 * @details Macros in this header:
 * noreturn
 */

#ifndef APRICOT_C17_H
#define APRICOT_C17_H

#define noreturn _Noreturn
#define packed __attribute__((__packed__))

#endif //APRICOT_C17_H

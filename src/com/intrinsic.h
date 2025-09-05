/**
 * @file     intrinsic.h
 * @author   Ramadhan Kalih Sewu (rama@kaorama.com)
 * @brief    Tailored to support various arch and compiler.
 * @version  0.1
 * @date     2025-09-03
 */

#ifndef COM_INTRINSIC_H
#define COM_INTRINSIC_H

#include "isadef.h"

#define __ASM __asm__

#if X86_64 && defined(_MSC_VER)
    #undef __ASM
#elif X86 && defined(_MSC_VER)
    #undef __ASM
    #define __ASM __asm
#else
    #undef __ASM
#endif

#endif // COM_INTRINSIC_H
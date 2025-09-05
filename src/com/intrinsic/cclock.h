// clang-format off

#ifndef COM_INTRINSIC_CCLOCK_H
#define COM_INTRINSIC_CCLOCK_H

#include "../intrinsic.h"

#if X86_64 && defined(_MSC_VER)

#include <intrin.h>

#pragma intrinsic(__rdtsc)

typedef unsigned long long cclock_t;

static inline cclock_t cclock()
{
    return (cclock_t) __rdtsc();
}

#elif X86 || X86_64

typedef unsigned long long u64_t;
typedef unsigned long long cclock_t;

static inline cclock_t cclock()
{
    unsigned lo, hi;
    __ASM volatile("rdtsc" : "=a"(lo), "=d"(hi));
    return (cclock_t) ((u64_t) hi << 32) | lo;
}

#endif

#endif // COM_INTRINSIC_CCLOCK_H
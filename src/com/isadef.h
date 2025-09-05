#ifndef COM_ISADEF_H
#define COM_ISADEF_H

// Begin definition

// Arch  : x86 (CISC)
// Mode  : 32-bit
// Names : x86,80x86,i386
#define X86 0

// Arch  : x86 (CISC)
// Mode  : 64-bit,32-bit
// Names : x86_64,x64,amd64
#define X86_64 0

// Arch  : Arm (RISC)
// Mode  : 32-bit
// Names : arm,a32,aarch32
#define ARM 0

// Arch  : Arm (RISC)
// Mode  : 64-bit,32-bit
// Names : arm64,a64,aarch64
#define ARM_64 0

// End definition

// Begin resolution

#if defined(__i386__) || defined(_M_IX86)
    #undef X86
    #define X86 1
#endif

#if defined(__x86_64__) || defined(_M_X64)
    #undef X86_64
    #define X86_64 1
#endif

#if defined(__arm__) || defined(_M_ARM)
    #undef ARM
    #define ARM 1
#endif

#if defined(__aarch64__) || defined(_M_ARM64)
    #undef ARM_64
    #define ARM_64 1
#endif

// End resolution

#endif // COM_ISADEF_H

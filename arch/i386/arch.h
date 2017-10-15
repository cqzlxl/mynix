#ifndef ARCH_H
#define ARCH_H

#ifndef ASM_SOURCE

typedef signed char          s8;
typedef signed short         s16;
typedef signed               s32;
typedef signed long long     s64;

typedef unsigned char        u8;
typedef unsigned short       u16;
typedef unsigned             u32;
typedef unsigned long long   u64;

#endif


#define KERNEL_CS   0x08
#define KERNEL_DS   0x10

#define USER_CS     0x18
#define USER_DS     0x20


#endif

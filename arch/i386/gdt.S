#include "gdt.h"

.section .data
// !!!各个段的先后顺序要和gdt.h里申明的一样!!!
gdt_start:

seg_null:                   // the mandatory null descriptor
.8byte   0x0

seg_kcode:                  // the code segment descriptor
//  base = 0x0 , limit = 0xfffff ,
//  1st flags: (present)1 (privilege)00 (descriptor type)1 -> 1001
//  type flags: (code)1 (conforming)0 (readable)1 (accessed)0 -> 1010
//  2nd flags: (granularity)1 (32 - bit default)1 (64 - bit seg)0 (AVL)0 -> 1100
.2byte   0xffff                  // Limit (bits 0 -15)
.2byte   0x0                     // Base (bits 0 -15)
.byte    0x0                     // Base (bits 16 -23)
.byte    0b10011010              // 1st flags , type flags
.byte    0b11001111              // 2nd flags , Limit (bits 16 -19)
.byte    0x0                     // Base (bits 24 -31)

seg_kdata:                  // the data segment descriptor
//  Same as code segment except for the type flags:
//  type flags: (code)0 (expand down)0 (writable)1 (accessed)0 -> 0010
.2byte   0xffff                  // Limit (bits 0 -15)
.2byte   0x0                     // Base (bits 0 -15)
.byte    0x0                     // Base (bits 16 -23)
.byte    0b10010010              // 1st flags , type flags
.byte    0b11001111              // 2nd flags , Limit (bits 16 -19)
.byte    0x0                     // Base (bits 24 -31)

seg_ucode:
.2byte   0xffff
.2byte   0x0
.byte    0x0
.byte    0b11111010
.byte    0b11001111
.byte    0x0

seg_udata:
.2byte   0xffff
.2byte   0x0
.byte    0x0
.byte    0b11110010
.byte    0b11001111
.byte    0x0

gdt_limit:


gdtr:
.align 4
.2byte  gdt_limit - gdt_start - 1  // Size of our GDT , always less one
.4byte  gdt_start                  // Start address of our GDT

.section .text
.extern reloadseg
.global gdt_init
gdt_init:
    lgdt gdtr

    // switch to pm
    movl %cr0, %eax
    orl  $0x1, %eax
    movl %eax, %cr0

    // set CS
    pushl $KERNEL_CS
    pushl $reloadseg
    retf

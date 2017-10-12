#define ASM_FILE        1
#include <multiboot.h>
#include "gdt.h"

#define MULTIBOOT_HEADER_FLAGS  MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO
#define MULTIBOOT_HEADER_CHECK  -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)


.section .multiboot
.align 4
.long  MULTIBOOT_HEADER_MAGIC
.long  MULTIBOOT_HEADER_FLAGS
.long  MULTIBOOT_HEADER_CHECK


.section .text
.extern gdt_init, start_kernel, puts
.global bootstrap, reloadseg

bootstrap:
    movl    $boot_stack_top, %esp

    // clear flags
    pushl   $0
    popf

    // save multiboot info
    pushl   %ebx
    pushl   %eax

    jmp     gdt_init

reloadseg:
    movw    $KERNEL_DS, %ax
    movw    %ax, %ds
    movw    %ax, %es
    movw    %ax, %fs
    movw    %ax, %gs
    movw    %ax, %ss

    call    start_kernel
    addl    $8, %esp

    pushl   $halt_message
    call    puts

hang:
    hlt
    jmp     hang


.section .data
.align 4
halt_message:
.asciz  "Halted."


.section .bss
.align 16
boot_stack_btm:
.skip 0x4000
boot_stack_top:

#define ASM_FILE        1
#include <multiboot.h>

#define MULTIBOOT_HEADER_FLAGS  MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO
#define MULTIBOOT_HEADER_CHECK  -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)


.section .multiboot
.align 4
.long  MULTIBOOT_HEADER_MAGIC
.long  MULTIBOOT_HEADER_FLAGS
.long  MULTIBOOT_HEADER_CHECK


.section .text
.global bootstrap
bootstrap:
    movl    $boot_stack_top, %esp

    pushl   $0
    popf

    pushl   %ebx
    pushl   %eax

    call    start_kernel
    addl    $8, %esp

    pushl   $halt_message

hang:
    hlt
    jmp     hang

halt_message:
    .asciz  "Halted."


.section .bss
.align 16
boot_stack_btm:
    .skip 0x4000
boot_stack_top:

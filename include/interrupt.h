#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <def.h>


typedef struct cpu_state {
    u32 eax;
    u32 ebx;
    u32 ecx;
    u32 edx;
    u32 ds;
    u32 es;
    u32 fs;
    u32 gs;
    u32 ss;
    u32 esi;
    u32 edi;
    u32 ebp;
    u32 esp;
} __attribute__((packed)) cpu_state_t;


typedef struct stack_state {
    u32 error_code;
    u32 eip;
    u32 cs;
    u32 eflags;
} __attribute__((packed)) stack_state_t;


typedef struct idt_entry {
    u16 baselow;
    u16 selector;
    u8 always0;
    u8 flags;
    u16 basehigh;
} __attribute__((packed)) idt_entry_t;


extern void handle_interrupt(cpu_state_t cpu, unsigned num, stack_state_t stack);
extern void install_interrupt_handler(unsigned num, const idt_entry_t *info);
extern void interrupt_init(void);


#endif

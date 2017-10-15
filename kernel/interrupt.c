#include <interrupt.h>
#include <logging.h>


extern idt_entry_t idt_start;
extern idt_entry_t idt_limit;

extern void interrupt_handler_33(void);

static idt_entry_t * const pidt_start = &idt_start;
static idt_entry_t * const pidt_limit = &idt_limit;


static void dump_interrupt_context(unsigned n, const cpu_state_t *cpu, const stack_state_t *stack)
{
    log_debug(LOGGER_INT, "interrupt %i(%2x) occurred.", n, n);

    const char *cpu_formats = " registers:"
        "\n  eax = %8x"
        "\n  ebx = %8x"
        "\n  ecx = %8x"
        "\n  edx = %8x"
        "\n  ds  = %8x"
        "\n  es  = %8x"
        "\n  fs  = %8x"
        "\n  gs  = %8x"
        "\n  ss  = %8x"
        "\n  esi = %8x"
        "\n  edi = %8x"
        "\n  ebp = %8x"
        "\n  esp = %8x";

    log_debug(LOGGER_INT, cpu_formats,
              cpu->eax,
              cpu->ebx,
              cpu->ecx,
              cpu->edx,
              cpu->ds,
              cpu->es,
              cpu->fs,
              cpu->gs,
              cpu->ss,
              cpu->esi,
              cpu->edi,
              cpu->ebp,
              cpu->esp);

    const char *stk_formats = " interrupted:"
        "\n  code = %x"
        "\n  eip  = %8x"
        "\n  cs   = %8x"
        "\n  flag = %32o";

    log_debug(LOGGER_INT, stk_formats,
              stack->error_code,
              stack->eip,
              stack->cs,
              stack->eflags
        );
}


void handle_interrupt(cpu_state_t cpu, unsigned n, stack_state_t stack)
{
    dump_interrupt_context(n, &cpu, &stack);
}


void install_interrupt_handler(unsigned n, const idt_entry_t *info)
{
    idt_entry_t *e = pidt_start + n;
    if (e < pidt_limit) {
        *e = *info;
    }
}


void interrupt_init(void)
{
    u32 addr = (u32) interrupt_handler_33;
    idt_entry_t e0 = {
        addr & 0xffff,
        KERNEL_CS,
        0,
        0b10001110,
        (addr >> 16) & 0xffff
    };

    install_interrupt_handler(33, &e0);
}

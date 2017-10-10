#include <def.h>
#include <io.h>
#include <string.h>

#include "serial.h"


/** serial_configure_baud_rate:
 * Sets the speed of the data being sent. The default speed of a serial
 * port is 115200 bits/s. The argument is a divisor of that number, hence
 * the resulting speed becomes (115200 / divisor) bits/s.
 */
static void configure_baud_rate(u16 com, u16 divisor)
{
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}


/** serial_configure_line:
 * Configures the line of the given serial port. The port is set to have a
 * data length of 8 bits, no parity bits, one stop bit and break control
 * disabled.
 */
static void configure_line(u16 com)
{
    /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
     * Content: | d | b | prty  | s | dl  |
     * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
     */
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

/** serial_configure_fifo:
 * Enables FIFO
 * Clear both receiver and transmission FIFO queues
 * Use 14 bytes as size of queue
 */
static void configure_fifo(u16 com)
{
    /* Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
     * Content: | lvl | bs | r | dma | clt | clr | e |
     * Value:   | 1 1 | 0  | 0 | 0   | 1   | 1   | 1 | = 0xC7
     */
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

/** serial_configure_modem:
 * We don’t need to enable interrupts, because we won’t handle any received da.
 * Therefore we use the configuration value 0x03 = 00000011 (RTS = 1 and DTS = 1),
 * which means that we are ready to send data.
 */
static void configure_modem(u16 com)
{
    /* Bit:     | 7 | 6 | 5  | 4  | 3   | 2   | 1   | 0   |
     * Content: | r | r | af | lb | ao2 | ao1 | rts | dtr |
     * Value:   | 0 | 0 | 0  | 0  | 0   | 0   | 1   | 1   |
     */
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

static int is_transmit_fifo_empty(u16 com)
{
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}


static int writeb(u8 b)
{
    while (! is_transmit_fifo_empty(SERIAL_COM1_BASE));
    outb(SERIAL_DATA_PORT(SERIAL_COM1_BASE), b);
    return 1;
}


void serial_init()
{
    u16 com = SERIAL_COM1_BASE;

    configure_baud_rate(com, 200);
    configure_line(com);
    configure_fifo(com);
    configure_modem(com);
}

int serial_writec(file_t *f, char c)
{
    char s[2] = {c};
    return serial_writes(f, s);
}

int serial_writes(file_t *f, const char *s)
{
    unsigned n = str_length(s);
    return serial_writem(f, s, n);
}

int serial_writem(file_t* UNUSED(f), const void *m, unsigned n)
{
    const u8 *p = m;
    for (unsigned i = 0; i < n; ++i) {
        writeb(p[i]);
    }
    return n;
}

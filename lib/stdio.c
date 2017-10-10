#include <arg.h>
#include <drivers.h>
#include <file.h>
#include <printf.h>
#include <stdio.h>


static file_t odevice;
static file_t *device;


void stdio_init()
{
    vga_init();

    odevice.magic = FILE_FRAMEBUFFER;
    odevice.writec = vga_writec;
    odevice.writes = vga_writes;
    odevice.data = NULL;
    device = &odevice;
}

int printf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    int n = printf_v(device, format, ap);

    va_end(ap);

    return n;
}

int puts(const char *string)
{
    return printf("%s\n", string);
}

int putc(char c)
{
    return printf("%c", c);
}

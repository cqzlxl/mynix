#include <printf.h>

#include "printf.common.h"
#include "printf.format.h"
#include "printf.printf.h"


int printf_e(file_t *file, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    int n = printf_v(file, format, ap);

    va_end(ap);

    return n;
}


int printf_v(file_t *file, const char *format, va_list ap)
{
    if (! format) {
        return -1;
    }

    if (! *format) {
        return 0;
    }

    int count = 0;

    stream_t istream = {
        format,
        stream_getc,
        stream_putc,
        stream_hasmore
    };
    stream_t *s = &istream;

    while (s->hasmore(s)) {
        context_t ctx = {};
        context_t *c = &ctx;
        fptd_t d = {
            c,
            s,
            S_HALTED,
            fptd_init,
            fptd_start,
            fptd_trans,
            fptd_enter
        };

        d.start(&d);

        int n;
        switch (d.state) {
            default:
                n = -1;
                break;

            case S_CFLUSH:
                n = printc(file, c->c);
                break;

            case S_FFOUND:
                n = printf(file, &c->f, &ap);
                break;
        }

        if (n == -1) {
            count = -1;
            break;
        } else {
            count += n;
            continue;
        }
    }

    return count;
}

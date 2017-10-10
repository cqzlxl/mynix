#ifndef PRINTF_PRINTF_H
#define PRINTF_PRINTF_H


#include "printf.common.h"


static int printc(file_t *file, char c)
{
    return file->writec(file, c);
}


static int prints(file_t *file, const char *string)
{
    return file->writes(file, string);
}


static int printf(file_t *file, const format_t *f, va_list *p)
{
    const char *s;

    va_list ap;
    va_copy(*p, ap);

    switch(f->class) {
        default:
            va_end(ap);
            s = NULL;
            break;

        case F_CLS_O: {
            unsigned v = va_arg(ap, unsigned);
            char buffer[36] = {};
            itoa(v, buffer, 2);
            s = buffer;
            break;
        }

        case F_CLS_B: {
            int v = va_arg(ap, int);
            const char *buffer;
            if (v == 0) {
                buffer = "false";
            } else {
                buffer = "true";
            }
            s = buffer;
            break;
        }

        case F_CLS_I: {
            int v = va_arg(ap, int);
            char buffer[16] = {};
            itoa(v, buffer, 10);
            s = buffer;
            break;
        }

        case F_CLS_L:
            s = NULL;
            break;

        case F_CLS_P:
            // go through, no break
        case F_CLS_X: {
            unsigned v = va_arg(ap, unsigned);
            char buffer[16] = {};
            itoa(v, buffer, 16);
            s = buffer;
            break;
        }

        case F_CLS_F:
            s = NULL;
            break;

        case F_CLS_C: {
            char v = va_arg(ap, char);
            char buffer[2] = {v};
            s = buffer;
            break;
        }

        case F_CLS_S: {
            const char *v = va_arg(ap, const char *);
            s = v;
            break;
        }
    }

    va_copy(ap, *p);

    if (! s) {
        return -1;
    }

    int m = f->width;
    int n = str_length(s);
    if (m > n) {
        if (f->paddir == F_PAD_L) {
            for (int i = 0; i < m - n; ++i) {
                printc(file, f->padchr);
            }
        }

        prints(file, s);

        if (f->paddir == F_PAD_R) {
            for (int i = 0; i < m - n; ++i) {
                printc(file, f->padchr);
            }
        }

        return m;
    } else {
        prints(file, s);
        return n;
    }
}


#endif

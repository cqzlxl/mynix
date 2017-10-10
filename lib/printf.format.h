#ifndef PRINTF_FORMAT_H
#define PRINTF_FORMAT_H


#include "printf.common.h"


#if 0
static int str_format_t(const format_t *f, char *buffer)
{
    char f1[16] = {};
    itoa(f->paddir, f1, 10);

    char f2[2] = {f->padchr};

    char f3[16] = {};
    itoa(f->width, f3, 10);

    char f4[16] = {};
    itoa(f->class, f4, 10);

    return str_join(buffer, ":", f1, f2, f3, f4, NULL);
}
#endif

static int stream_hasmore(const stream_t *this)
{
    return this->s && *this->s;
}


static char stream_getc(stream_t *this)
{
    char c = *this->s;
    ++this->s;
    return c;
}


static void stream_putc(stream_t *this, char UNUSED(c))
{
    --this->s;
}


static void fptd_init(fptd_t *this)
{
    this->state = S_BOOTED;
}


static void fptd_start(fptd_t *this)
{
    this->init(this);

    stream_t *input = this->cstream;
    while (input->hasmore(input)) {
        char c = input->getc(input);
        this->trans(this, c);
        this->enter(this, c);

        int s = this->state;

        if (s == S_BOOTED || s == S_HALTED) {
            break;
        }

        if (s == S_ERRORG || s == S_ERRORF) {
            break;
        }

        if (s == S_CFLUSH || s == S_FFOUND) {
            break;
        }
    }
}


static int is_class_flag(char c)
{
    int f = 0;

    switch (c) {
        default:
            f = 0;
            break;

        case F_CLS_B:
        case F_CLS_O:
        case F_CLS_I:
        case F_CLS_L:
        case F_CLS_F:
        case F_CLS_C:
        case F_CLS_S:
        case F_CLS_X:
        case F_CLS_P:
            f = 1;
            break;
    }

    return f;
}


static void fptd_trans(fptd_t *this, char c)
{
    int *s = &this->state;
    switch (*s) {
        case S_BOOTED:
            if (c == '%') {
                *s = S_FPARSE;
            } else {
                *s = S_CFLUSH;
            }
            break;

        case S_FPARSE:
            if (c == '%') {
                *s = S_CFLUSH;
            } else if (c == '+' || c == '-') {
                *s = S_FPADDR;
            } else if (c == '0' || c == ' ') {
                *s = S_FPADCH;
            } else if (c >= '1' && c <= '9') {
                *s = S_FWIDTH;
            } else if (is_class_flag(c)) {
                *s = S_FFOUND;
            } else {
                *s = S_ERRORF;
            }
            break;

        case S_FPADDR:
            if (c == '0' || c == ' ') {
                *s = S_FPADCH;
            } else if (c >= '1' && c <= '9') {
                *s = S_FWIDTH;
            } else if (is_class_flag(c)) {
                *s = S_FFOUND;
            } else {
                *s = S_ERRORF;
            }
            break;

        case S_FPADCH:
            if (c >= '1' && c <= '9') {
                *s = S_FWIDTH;
            } else if (is_class_flag(c)) {
                *s = S_FFOUND;
            } else {
                *s = S_ERRORF;
            }
            break;

        case S_FWIDTH:
            if (c >= '0' && c <= '9') {
                *s = S_FWIDTH;
            } else if (is_class_flag(c)) {
                *s = S_FFOUND;
            } else {
                *s = S_ERRORF;
            }
            break;

        case S_ERRORG:
        case S_ERRORF:
        case S_HALTED:
        case S_CFLUSH:
        case S_FFOUND:
            // 这些都是终态，不接受输入
            *s = S_ERRORG;
            break;

        default:
            // bug
            // error log
            break;
    }
}


// 一致性检查：format_t的各方面是分阶段解析的，其'语意'不一定有意义。
// 严格地讲，这块儿工作应该是在format生成后，使用前。
static format_t* format_regulate(format_t *f)
{
    if (f->width) {
        if (f->class == F_CLS_C || f->class == F_CLS_S) {
            if (f->paddir == 0) {
                f->paddir = F_PAD_R;
            }
            if (f->padchr == 0) {
                f->padchr = ' ';
            }
        } else {
            if (f->paddir == 0) {
                f->paddir = F_PAD_L;
            }
            if (f->padchr == 0) {
                f->padchr = '0';
            }
        }
    }

    if (!f->width && f->class == F_CLS_P) {
        f->width = 8;
    }

    return f;
}


static void fptd_enter(fptd_t *this, char c)
{
    format_t *cf = &this->context->f;
    char *cc = &this->context->c;

    int *s = &this->state;
    switch (*s) {
        case S_CFLUSH:
            *cc = c;
            break;

        case S_FPARSE:
            cf->paddir = 0;
            cf->padchr = 0;
            cf->width = 0;
            cf->class = 0;
            break;

        case S_FPADDR:
            if (c == '-') {
                cf->paddir = F_PAD_L;
            } else {
                cf->paddir = F_PAD_R;
            }
            break;

        case S_FPADCH:
            cf->padchr = c;
            break;

        case S_FWIDTH:
            cf->width = cf->width * 10 + (c - '0');
            break;

        case S_FFOUND:
            cf->class = c;
            format_regulate(cf);
            break;

        case S_ERRORG:
        case S_ERRORF:
            // error log
            break;

        case S_BOOTED:
        case S_HALTED:
            // error log
            break;

        default:
            // bug
            // error log
            break;
    }
}


#endif

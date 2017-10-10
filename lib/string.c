#include <arg.h>
#include <string.h>


static void do_reverse(char *head, char *tail)
{
    while(head < tail) {
        *head ^= *tail;
        *tail ^= *head;
        *head ^= *tail;

        ++head;
        --tail;
    }
}


unsigned str_length(const char *string)
{
    if (! string) {
        return 0;
    }

    unsigned count = 0;
    while (*string) {
        ++string;
        ++count;
    }

    return count;
}


// do it in-place
char* str_reverse(char *string)
{
    if (string && *string) {
        char *lastp = string;
        while (*lastp) ++lastp;
        --lastp;

        do_reverse(string, lastp);
    }

    return string;
}


int str_copy(const char *src, char *dst)
{
    int count = 0;

    if (src && dst) {
        while (*src) {
            *dst++ = *src++;
            ++count;
        }
        *dst = 0;
        ++count;
    }

    return count;
}


int str_join(char *buffer, const char *sep, ...)
{
    int count = 0;

    int first = 1;
    va_list ap;
    va_start(ap, sep);
    char *p = buffer;

    while (1) {
        const char *s = va_arg(ap, const char *);
        if (! s) {
            break;
        }

        if (first) {
            first = 0;
        } else {
            int n = str_copy(sep, p + count);
            if (n > 1) {
                count += n - 1;
            }
        }

        int n = str_copy(s, p + count);
        if (n > 1) {
            count += n - 1;
        }
    }

    return count;
}


char* itoa(int value, char *result, unsigned base)
{
    if (! result) {
        return result;
    }

    if (base < 2 || base > 36) {
        *result = '\0';
        return result;
    }

    const char *digits = "0123456789abcdefghijklmnopqrstuvwxyz";

    int negative = base == 10 && value < 0;
    unsigned v = negative ? -value : value;

    char *p = result;
    do {
        *p++ = digits[v % base];
        v /= base;
    } while (v > 0);

    if (negative) {
        *p++ = '-';
    }

    *p-- = 0;
    // 至此，整数-12345 将导至结果串被转换成 54321-，恰好逆序。
    // 其中result 指向 '5'，p指向 '-'

    // 再倒回来
    do_reverse(result, p);

    return result;
}

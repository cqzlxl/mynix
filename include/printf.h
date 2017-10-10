#ifndef PRINTF_H
#define PRINTF_H


#include <arg.h>
#include <file.h>


extern int printf_e(file_t *file, const char *format, ...);

extern int printf_v(file_t *file, const char *format, va_list ap);


#endif

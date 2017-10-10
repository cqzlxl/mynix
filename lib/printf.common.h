#ifndef PRINTF_COMMON_H
#define PRINTF_COMMON_H

#include <def.h>
#include <file.h>
#include <printf.h>
#include <string.h>

#define S_HALTED        -1
#define S_BOOTED        0
#define S_CFLUSH        1
#define S_FPARSE        2
#define S_FPADDR        3
#define S_FPADCH        4
#define S_FWIDTH        5
#define S_FCLASS        6
#define S_FFOUND        7
#define S_ERRORF        8
#define S_ERRORG        -9

#define F_PAD_L         -1
#define F_PAD_M         0
#define F_PAD_R         1

// 一些用于指示数据类型，一些却用于指示展示方式
// 其实挺混乱的
// 将一个s32 打印为true/false
#define F_CLS_B         'b'
// 将一个u32 以二进制形式打印出来：从左至右，从高到低
#define F_CLS_O         'o'
// 将一个s32 打印出来
#define F_CLS_I         'i'
// 将一个u64 打印出来
#define F_CLS_L         'l'
// 尚不支持
#define F_CLS_F         'f'
// 将一个char打印出来
#define F_CLS_C         'c'
// 将一个char *打印出来
#define F_CLS_S         's'
// 将一个u32 以十六进制形式打印出来
#define F_CLS_X         'x'
// 将一个u32 以十六进制形式打印出来
#define F_CLS_P         'p'


typedef struct {
    int paddir;
    char padchr;
    int width;
    int class;
} format_t;


typedef union {
    format_t f;
    char c;
} context_t;


typedef struct stream {
    const char *s;
    char (*getc)(struct stream *this);
    void (*putc)(struct stream *this, char c);
    int (*hasmore)(const struct stream *this);
} stream_t;


// Format Parsing Transition Diagram
typedef struct fptd {
    context_t *context;
    stream_t *cstream;
    int state;

    void (*init)(struct fptd *this);
    void (*start)(struct fptd *this);
    void (*trans)(struct fptd *this, char c);
    void (*enter)(struct fptd *this, char c);
} fptd_t;


#endif

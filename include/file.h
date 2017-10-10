#ifndef FILE_H
#define FILE_H


#define FILE_BLOCK        0
#define FILE_BYTES        10
#define FILE_FRAMEBUFFER  20
#define FILE_SERIAL       30

typedef struct file {
    int magic;
    int (*writec)(struct file *f, char c);
    int (*writes)(struct file *f, const char *s);
    int (*writem)(struct file *f, const void *m, unsigned n);
    void *data;
} file_t;


#endif

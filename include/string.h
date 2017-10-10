#ifndef STRING_H
#define STRING_H


unsigned str_length(const char *string);

char* str_reverse(char *string);

int str_copy(const char *src, char *dst);

int str_join(char *buffer, const char *sep, ...);

char* itoa(int value, char *buffer, unsigned base);

static inline int isdigit(char c)
{
    return c >= '0' && c <= '9';
}


#endif

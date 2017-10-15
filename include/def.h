#ifndef DEF_H
#define DEF_H

#define arch_header(A) <arch/A/arch.h>

#include arch_header(ARCH)


#define NULL  ((void *) 0)

typedef u64 size_t;
typedef s64 ssize_t;

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *) 0)->MEMBER)


#ifdef __GNUC__
#define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#else
#define UNUSED(x) UNUSED_ ## x
#endif

#ifdef __GNUC__
#define UNUSED_FUNCTION(x) __attribute__((__unused__)) UNUSED_ ## x
#else
#define UNUSED_FUNCTION(x) UNUSED_ ## x
#endif


#endif

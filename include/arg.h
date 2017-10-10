#ifndef ARG_H
#define ARG_H


typedef int acpi_native_int;
#define  _AUPBND                (sizeof (acpi_native_int) - 1)
#define  _ADNBND                (sizeof (acpi_native_int) - 1)

#define _bnd(X, bnd)            (((sizeof (X)) + (bnd)) & (~(bnd)))

typedef unsigned char* va_list;
#define va_arg(ap, T)           (* (T *) (((ap) += (_bnd (T, _AUPBND))) - (_bnd (T,_ADNBND))))
#define va_end(ap)              (void) 0
#define va_start(ap, A)         (void) ((ap) = (((unsigned char *) &(A)) + (_bnd (A,_AUPBND))))
#define va_copy(src, dst)       (void) ((dst) = (src))


#endif

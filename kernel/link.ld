ENTRY(bootstrap)                            /* the name of the entry label */


SECTIONS {
    . = 1M;                                 /* the code should be loaded at 1 MiB */

    .text ALIGN(4K):                        /* align at 4 KiB */
    {
        *(.multiboot)                       /* multiboot header comes early */
        *(.text)                            /* all text sections from all files */
    }

    .rodata ALIGN(4K):                      /* align at 4 KiB */
    {
        *(.rodata*)                         /* all read-only data sections from all files */
    }

    .data ALIGN(4K):                        /* align at 4 KiB */
    {
        *(.data)                            /* all data sections from all files */
    }

    .bss ALIGN(4K):                         /* align at 4 KiB */
    {
        *(COMMON)                           /* all COMMON sections from all files */
        *(.bss)                             /* all bss sections from all files */
    }
}

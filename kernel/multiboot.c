#include <multiboot.h>
#include <stdio.h>


/* Check if the bit BIT in FLAGS is set. */
#define CHECK_FLAG(flags, bit)   ((flags) & (1 << (bit)))


void dump_multiboot_info(unsigned magic, const multiboot_info_t *mbi)
{
    puts("multiboot information dump:");

    /* Am I booted by a Multiboot-compliant boot loader? */
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        printf("Invalid magic number: %32o\n", magic);
        return;
    }

    /* Print out the flags. */
    printf("flags = %32o\n", mbi->flags);

    /* Are mem_* valid? */
    if (CHECK_FLAG(mbi->flags, 0)) {
        printf("mem_lower = %iKB, mem_upper = %iKB\n", mbi->mem_lower, mbi->mem_upper);
    }

    /* Is boot_device valid? */
    if (CHECK_FLAG(mbi->flags, 1)) {
        printf("boot_device = 0x%x\n", mbi->boot_device);
    }

    /* Is the command line passed? */
    if (CHECK_FLAG(mbi->flags, 2)) {
        printf("cmdline = %s\n", (const char *) mbi->cmdline);
    }

    /* Are mods_* valid? */
    if (CHECK_FLAG(mbi->flags, 3)) {
        int n = mbi->mods_count;
        multiboot_module_t *start = (multiboot_module_t *) mbi->mods_addr;
        multiboot_module_t *limit = start + n;

        printf("mods_count = %i, mods_addr = %p\n", n, start);
        for (multiboot_module_t *m = start; m < limit; ++m) {
            printf(" mod_start = %p, mod_end = %p, cmdline = %s\n",
                   m->mod_start, m->mod_end, m->cmdline);
        }
    }

    /* Bits 4 and 5 are mutually exclusive! */
    if (CHECK_FLAG(mbi->flags, 4) && CHECK_FLAG(mbi->flags, 5)) {
        printf("Both bits 4 and 5 are set.\n");
        return;
    }

    /* Is the symbol table of a.out valid? */
    if (CHECK_FLAG(mbi->flags, 4)) {
        const multiboot_aout_symbol_table_t *sym = &(mbi->u.aout_sym);
        printf("multiboot_aout_symbol_table: tabsize = %12d, strsize = %12d, addr = %p\n",
               sym->tabsize, sym->strsize, sym->addr);
    }

    /* Is the section header table of ELF valid? */
    if (CHECK_FLAG(mbi->flags, 5)) {
        const multiboot_elf_section_header_table_t *sec = &(mbi->u.elf_sec);
        printf("multiboot_elf_sec: num = %i, size = %i, addr = %p, shndx = 0x%x\n",
               sec->num, sec->size, sec->addr, sec->shndx);
    }

    /* Are mmap_* valid? */
    if (CHECK_FLAG(mbi->flags, 6)) {
        printf("mmap_addr = 0x%x, mmap_length = 0x%x\n", mbi->mmap_addr, mbi->mmap_length);

        for (
            multiboot_memory_map_t *mmap = (multiboot_memory_map_t *) mbi->mmap_addr;
            (unsigned long) mmap < mbi->mmap_addr + mbi->mmap_length;
            mmap = (multiboot_memory_map_t *) ((unsigned long) mmap + mmap->size + sizeof (mmap->size))
            )
            printf(" size = %i, base_addr = 0x%x%08x, length = 0x%x%08x, type = 0x%x\n",
                   mmap->size,
                   (unsigned) (mmap->addr >> 32), (unsigned) (mmap->addr & 0xffffffff),
                   (unsigned) (mmap->len >> 32), (unsigned) (mmap->len & 0xffffffff),
                   mmap->type
                );
    }
}

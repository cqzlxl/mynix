#include <logging.h>
#include <multiboot.h>
#include <stdio.h>


static void init()
{
    stdio_init();
    logging_init();
}


void start_kernel(unsigned magic, const multiboot_info_t *info)
{
    init();

    dump_multiboot_info(magic, info);

    printf("\nHello, %s World!\n", "OS");

    log_info(LOGGER_MAIN, "Can you see this %s?", "message");
    log_warn(LOGGER_MAIN, "A warning log through serial line.");
}

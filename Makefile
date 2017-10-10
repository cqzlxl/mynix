ARCH = i386

module_driver  = drivers
module_kernel  = kernel
module_libk    = lib
module_test    = tests


newimg  = os.img
isodir  = isodir

driver_sources = $(wildcard $(module_driver)/*.c)
driver_objs    = $(driver_sources:.c=.o)

arch_sources = $(wildcard arch/$(ARCH)/*.S)
krnl_sources = $(wildcard $(module_kernel)/*.c)
kernel_file  = kernel.elf
kernel_objs  = $(arch_sources:.S=.o) $(krnl_sources:.c=.o)

lib_archive  = libk.a
lib_sources  = $(wildcard $(module_libk)/*.c)
lib_objs     = $(lib_sources:.c=.o)


CPPFLAGS = -I. -Iinclude -DARCH=$(ARCH)

CFLAGS   = -std=c99 \
		   -m32 \
		   -static \
		   -nostdinc -nostdlib \
		   -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs \
		   -Wall -Wextra -Werror

ASFLAGS  = -m32

LDFLAGS  = -melf_i386

ARFLAGS  = rvU


.PHONY: all clean tests testsclean

all: $(kernel_file)
	@echo Successfully constructed new kernel: $(kernel_file)
	@echo You may run it by typing 'make run'


run: $(newimg)
	qemu-system-$(ARCH) -curses -cdrom $(newimg) -m 8M -serial file:serial.log.txt


runclean:
	$(RM) serial.log.txt


$(newimg): $(kernel_file) iso/grub.cfg
	mkdir -p $(isodir)/boot/grub
	cp $(kernel_file) $(isodir)/boot
	cp $(filter-out $<, $^) $(isodir)/boot/grub
	grub-mkrescue -o $(newimg) $(isodir)


$(kernel_file): $(module_kernel)/link.ld $(kernel_objs) $(driver_objs) $(lib_objs)
	$(LD) $(LDFLAGS) -T $< -o $@ $(filter-out $<, $^)
	grub-file --is-x86-multiboot $@


clean:
	$(RM)    $(driver_objs)
	$(RM)    $(kernel_objs)
	$(RM)    $(kernel_file)
	$(RM)    $(lib_objs)
	$(RM)    $(newimg)
	$(RM) -r $(isodir)


tests: $(lib_archive)($(lib_objs) $(driver_objs))
	$(MAKE) -C $(module_test) all


testsclean:
	$(MAKE) -C $(module_test) clean
	$(RM) $(lib_archive)

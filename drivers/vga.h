#ifndef VGA_H
#define VGA_H

#include <def.h>
#include <file.h>


#define VGA_COLOR_BLACK         0
#define VGA_COLOR_BLUE          1
#define VGA_COLOR_GREEN         2
#define VGA_COLOR_CYAN          3
#define VGA_COLOR_RED           4
#define VGA_COLOR_MAGENTA       5
#define VGA_COLOR_BROWN         6
#define VGA_COLOR_LIGHT_GREY    7
#define VGA_COLOR_DARK_GREY     8
#define VGA_COLOR_LIGHT_BLUE    9
#define VGA_COLOR_LIGHT_GREEN   10
#define VGA_COLOR_LIGHT_CYAN    11
#define VGA_COLOR_LIGHT_RED     12
#define VGA_COLOR_LIGHT_MAGENTA 13
#define VGA_COLOR_LIGHT_BROWN   14
#define VGA_COLOR_WHITE         15

#define VGA_ROWS 25
#define VGA_COLS 80
#define VGA_BASE 0xb8000

/* The I/O ports */
#define VGA_CMD_PORT 0x03D4
#define VGA_DAT_PORT 0x03D5
/* The I/O port commands */
#define VGA_HBYTE_CMD 0x0E
#define VGA_LBYTE_CMD 0x0F


extern void vga_init();

extern int vga_writec(file_t *file, char c);
extern int vga_writes(file_t *file, const char *s);
extern int vga_writem(file_t *file, const void *m, unsigned n);

extern u8 vga_current_color();
extern u8 vga_set_color(u8 fgcolor, u8 bgcolor);
extern u8 vga_reset_color();

extern u16 vga_current_cursor();
extern u16 vga_set_cursor(unsigned row, unsigned col);
extern u16 vga_reset_cursor();


#endif

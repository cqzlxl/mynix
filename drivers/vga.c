#include <def.h>
#include <io.h>
#include <memory.h>
#include <string.h>

#include "vga.h"


#ifndef VGA_DEFAULT_FGCOLOR
#define VGA_DEFAULT_FGCOLOR VGA_COLOR_WHITE
#endif

#ifndef VGA_DEFAULT_BGCOLOR
#define VGA_DEFAULT_BGCOLOR VGA_COLOR_BLACK
#endif

typedef struct point {
    u8 character;
    u8 color;
} __attribute__((packed)) point_t;

typedef struct screen {
    u8 clear_c;
    u8 fgcolor;
    u8 bgcolor;
    point_t *buffer;
} screen_t;

static screen_t s = {};


static u16 index(u16 row, u16 col)
{
    return row * VGA_COLS + col;
}

static u16 index_limit()
{
    return VGA_ROWS * VGA_COLS;
}

static u16 index_row(u16 i)
{
    return i / VGA_COLS;
}

static u16 index_col(u16 i)
{
    return i % VGA_COLS;
}

static u8 color(u8 fgcolor, u8 bgcolor)
{
    return ((bgcolor & 0x0F) << 4) + (fgcolor & 0x0F);
}

static void do_write(char c, u8 fgcolor, u8 bgcolor, u16 i, u16 j)
{
    u16 x = index(i, j);
    u8 clr = color(fgcolor, bgcolor);
    point_t p = {
        c,
        clr
    };
    s.buffer[x] = p;
}

static void clear_line(unsigned n) {
    for (unsigned c = 0; c < VGA_COLS; ++c) {
        do_write(s.clear_c, s.fgcolor, s.bgcolor, n, c);
    }
}

static void clear()
{
    for (unsigned r = 0; r < VGA_ROWS; ++r) {
        clear_line(r);
    }
    vga_reset_cursor();
}

static void scroll(unsigned n)
{
    point_t *f = s.buffer + index(n, 0);
    point_t *t = s.buffer;
    unsigned c = (VGA_ROWS - n) * VGA_COLS;
    mem_move(f, sizeof(point_t), c, t);
    for (unsigned i = VGA_ROWS - n; i < VGA_ROWS; ++i) {
        clear_line(i);
    }
}

static u16 next_cursor(u16 r, u16 c)
{
    u16 n = index(r, c) + 1;
    if (n >= index_limit()) {
        scroll(1);
        n = index(VGA_ROWS-1, 0);
    }

    u16 row = index_row(n);
    u16 col = index_col(n);
    vga_set_cursor(row, col);
    return n;
}


void vga_init()
{
    s.clear_c = ' ';
    s.buffer = (point_t *)(unsigned char *) VGA_BASE;
    vga_reset_color();
    clear();
}

u8 vga_current_color()
{
    return color(s.fgcolor, s.bgcolor);
}

u8 vga_set_color(u8 fgcolor, u8 bgcolor)
{
    u8 previous = color(s.fgcolor, s.bgcolor);
    s.fgcolor = fgcolor & 0x0F;
    s.bgcolor = bgcolor & 0x0F;
    return previous;
}

u8 vga_reset_color()
{
    return vga_set_color(VGA_DEFAULT_FGCOLOR, VGA_DEFAULT_BGCOLOR);
}

u16 vga_current_cursor()
{
    outb(VGA_CMD_PORT, VGA_HBYTE_CMD);
    u8 hbyte = inb(VGA_DAT_PORT);
    outb(VGA_CMD_PORT, VGA_LBYTE_CMD);
    u8 lbyte = inb(VGA_DAT_PORT);
    return (hbyte << 8) + lbyte;
}

u16 vga_set_cursor(unsigned row, unsigned col)
{
    u16 previous = vga_current_cursor();
    u16 position = index(row, col);
    u8 hbyte = (position >> 8) & 0xFF;
    outb(VGA_CMD_PORT, VGA_HBYTE_CMD);
    outb(VGA_DAT_PORT, hbyte);
    u8 lbyte = position & 0xFF;
    outb(VGA_CMD_PORT, VGA_LBYTE_CMD);
    outb(VGA_DAT_PORT, lbyte);
    return previous;
}

u16 vga_reset_cursor()
{
    return vga_set_cursor(0, 0);
}


int vga_writec(file_t *UNUSED(file), char c)
{
    u16 position = vga_current_cursor();
    u16 i = index_row(position);
    u16 j = index_col(position);
    if (c == '\r' || c == '\n') {
        // no need to write anything, just move cursor to start of next line
        next_cursor(i, VGA_COLS-1);
    } else {
        do_write(c, s.fgcolor, s.bgcolor, i, j);
        next_cursor(i, j);
    }

    return 1;
}

int vga_writes(file_t *file, const char *s)
{
    unsigned n = str_length(s);
    return vga_writem(file, s, n);
}

int vga_writem(file_t *file, const void *m, unsigned n)
{
    const unsigned char *p = m;

    for (unsigned i = 0; i < n; ++i) {
        vga_writec(file, p[i]);
    }

    return n;
}

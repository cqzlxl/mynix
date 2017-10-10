#include <def.h>
#include <memory.h>


// possible layouts:
//
// 1) <-----s----->                 start at end of s
//                  <-----d----->
//
//
// 2) <-----s----->                 start at end of s
//             <-----d----->
//
//
// 3) <-----s----->                 no action
//    <-----d----->
//
//
// 4)          <-----s----->        start at beginning of s
//    <-----d----->
//
//
// 5)               <-----s----->   start at beginning of s
//    <-----d----->
void mem_move(const void *from, unsigned size, unsigned n, void *to)
{
    const u8 *ss = from;
    const u8 *se = ss + n;
    u8 *ds = to;
    u8 *de = ds + n;

    if (ss == ds && se == de) {
        return;
    }

    if (se < ds || ss > de || (ds < ss && ss < de)) {
        // Layout 1, 5, 4
        mem_copy(from, size, n, to);
    } else {
        // Layout 2
        for (unsigned i = 0; i < size * n; ++i) {
            *de-- = *se--;
        }
    }
}


// 简单粗暴的实现，不能处理区域重叠的问题
void mem_copy(const void *from, unsigned size, unsigned n, void *to)
{
    const u8 *s = from;
    u8 *d = to;

    for (unsigned i = 0; i < size * n; ++i) {
        d[i] = s[i];
    }
}

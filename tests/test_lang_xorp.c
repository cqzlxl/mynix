#include <assert.h>


void test_xorp()
{
    int x = 1;
    int y = 5;

    int *p = &x;
    int *q = &y;
    assert(*p == 1 && *q == 5);

    *p ^= *q;
    *q ^= *p;
    *p ^= *q;
    assert(x==5 && y==1);
}

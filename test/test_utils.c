#include "chat.h"
#include <assert.h>

int main(void)
{
    assert(stu_strlen("Test") == 4);
    assert(stu_strlen("") == 0);
    assert(stu_strlen("A B") == 3);

    assert(stu_strcmp("A", "A") == 0);
    assert(stu_strcmp("A", "B") != 0);
    assert(stu_strcmp("Test", "Tes") != 0);
    assert(stu_strcmp("", "") == 0);

    assert(stu_atoi("123") == 123);
    assert(stu_atoi("0") == 0);
    assert(stu_atoi("-1") == -1);

    return 0;
}

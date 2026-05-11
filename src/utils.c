#include "chat.h"

int stu_strcmp(const char *s1, const char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s1[i] == s2[i]) {
        i += 1;
    }
    return (s1[i] - s2[i]);
}

int stu_atoi(const char *str)
{
    int res;
    int i;

    res = 0;
    i = 0;
    while (str[i] >= '0' && str[i] <= '9') {
        res = res * 10 + (str[i] - '0');
        i += 1;
    }
    return (res);
}

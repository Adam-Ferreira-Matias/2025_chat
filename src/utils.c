#include "chat.h"
#include <stdlib.h>

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

int stu_strncmp(const char *s1, const char *s2, int n)
{
    int i;

    if (n == 0) {
        return (0);
    }
    i = 0;
    while (i < n - 1 && s1[i] && s1[i] == s2[i]) {
        i += 1;
    }
    return (s1[i] - s2[i]);
}

unsigned int stu_strlen(const char *str)
{
    unsigned int i;

    i = 0;
    while (str[i] != '\0') {
        i = i + 1;
    }
    return i;
}

char *stu_strdup(char *str)
{
    char *str_copy;
    unsigned int size;
    unsigned int i;

    size = 0;
    i = 0;
    while (str[size] != '\0') {
        size += 1;
    }
    size += 1;
    str_copy = malloc(sizeof (int) * size);
    while (i < size) {
        str_copy[i] = str[i];
        i += 1;
    }
    return str_copy;
}

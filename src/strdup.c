/*
 * E89 Pedagogical & Technical Lab
 * project: strdup.c
 * created on:  2025-11-09 - 16:35 +0100
 * 1st author:  adam.ferreira
 * description: function of strdup.c
 */

#include <stdlib.h>

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

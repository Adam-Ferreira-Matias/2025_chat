/*
 * E89 Pedagogical & Technical Lab
 * project: strlen.c
 * created on:  2025-10-29 - 17:11 +0100
 * 1st author:  adam.ferreira
 * description: function of strlen.c
 */


unsigned int stu_strlen(const char *str)
{
    unsigned int i;

    i = 0;
    while (str[i] != '\0') {
        i = i + 1;
    }
    return i;
}

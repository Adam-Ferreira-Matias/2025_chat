/*
 * E89 Pedagogical & Technical Lab
 * project: print_base10
 * created on:  2026-01-29 - 17:58 +0100
 * 1st author:  adam.ferreira
 * description: change int to char for write it
 */

#include <unistd.h>
#include <stdlib.h>

static int nb_len(int nb);
static int get_digit(int nb, int index);

void tc_putchar(char c)
{
    write(1, &c, 1);
}

char *base10_to_char(int nb)
{
    int i;
    int nb_write;
    char *buf;

    buf = malloc(11);
    if (!buf) {
        return NULL;
    }
    if (nb < 0) {
        tc_putchar('-');
        nb *= -1;
    }
    i = nb_len(nb) - 1;
    while (i >= 0) {
        nb_write = get_digit(nb, i);
        buf[i] += (nb_write + '0');
        i -= 1;
    }
    buf[10] = '\0';
    return buf;
}

static int nb_len(int nb)
{
    int i;

    i = 0;
    if (nb < 0) {
        nb *= -1;
    }
    while (nb >= 1) {
        nb /= 10;
        i += 1;
    }
    return i;
}

static int get_digit(int nb, int index)
{
    int i;
    int modulo;

    i = 0;
    modulo = 1;
    while (i < (index + 1)) {
        modulo *= 10;
        i += 1;
    }
    nb = nb % modulo;
    nb /= (modulo / 10);
    return nb;
}

#include "chat.h"
#include <criterion/criterion.h>

Test(parse, valid_args) {
    struct config cfg;
    char *a1[] = {"./srv", "-p", "80", "-l", "5"};
    char *a2[] = {"./srv", "-p", "80", "-f", "-l", "5"};

    cr_assert_eq(parse_args(5, a1, &cfg), 0);
    cr_assert_eq(cfg.port, 80);
    cr_assert_eq(cfg.limit, 5);
    cr_assert_eq(cfg.fallback, 0);

    cr_assert_eq(parse_args(6, a2, &cfg), 0);
    cr_assert_eq(cfg.port, 80);
    cr_assert_eq(cfg.limit, 5);
    cr_assert_eq(cfg.fallback, 1);
}

Test(parse, invalid_args) {
    struct config cfg;
    char *e1[] = {"./srv", "-p"};
    char *e2[] = {"./srv", "-x"};
    char *e3[] = {"./srv", "-p", "80", "-l"};

    cr_assert_eq(parse_args(2, e1, &cfg), 1);
    cr_assert_eq(parse_args(2, e2, &cfg), 1);
    cr_assert_eq(parse_args(4, e3, &cfg), 1);
}

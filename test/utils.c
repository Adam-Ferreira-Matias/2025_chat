#include "chat.h"
#include <criterion/criterion.h>

Test(utils, stu_strlen) {
    cr_assert_eq(stu_strlen("Test"), 4);
    cr_assert_eq(stu_strlen(""), 0);
    cr_assert_eq(stu_strlen("A B"), 3);
}

Test(utils, stu_strcmp) {
    cr_assert_eq(stu_strcmp("A", "A"), 0);
    cr_assert_neq(stu_strcmp("A", "B"), 0);
    cr_assert_neq(stu_strcmp("Test", "Tes"), 0);
    cr_assert_eq(stu_strcmp("", ""), 0);
}


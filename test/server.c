#include "chat.h"
#include <criterion/criterion.h>
#include <unistd.h>

Test(server, init_valid) {
    struct config cfg;
    int fd;

    cfg.port = 55555;
    cfg.limit = 5;
    cfg.fallback = 1;

    fd = init_server(&cfg);
    cr_assert_neq(fd, -1);
    close(fd);
}


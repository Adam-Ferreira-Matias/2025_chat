#include "chat.h"
#include <criterion/criterion.h>

Test(env, init_and_free) {
    struct chat_env env;
    struct config cfg;

    cfg.limit = 5;
    cr_assert_eq(init_env(&env, &cfg, 42), 0);

    cr_assert_eq(env.server_fd, 42);
    cr_assert_eq(env.max_clients, 5);
    cr_assert_eq(env.fds[0].fd, 42);
    cr_assert_eq(env.fds[1].fd, -1);
    cr_assert_eq(env.clients[0].fd, -1);

    free_env(&env);
}

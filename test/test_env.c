#include "chat.h"
#include <assert.h>

int main(void)
{
    struct chat_env env;
    struct config cfg;

    cfg.limit = 5;
    assert(init_env(&env, &cfg, 42) == 0);

    assert(env.server_fd == 42);
    assert(env.max_clients == 5);
    assert(env.fds[0].fd == 42);
    assert(env.fds[1].fd == -1);
    assert(env.clients[0].fd == -1);

    free_env(&env);

    return 0;
}

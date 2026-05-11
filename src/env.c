#include "chat.h"
#include <stdlib.h>

int init_env(struct chat_env *env, struct config *cfg, int server_fd)
{
    int i;

    env->server_fd = server_fd;
    env->max_clients = cfg->limit;
    env->fds = malloc(sizeof(struct pollfd) * (size_t) (cfg->limit + 1));
    env->clients = malloc(sizeof(struct client) * (size_t) cfg->limit);
    if (!env->fds || !env->clients) {
        return (1);
    }
    env->fds[0].fd = server_fd;
    env->fds[0].events = POLLIN;
    i = 1;
    while (i <= cfg->limit) {
        env->fds[i].fd = -1;
        env->fds[i].events = POLLIN;
        env->clients[i - 1].fd = -1;
        i += 1;
    }
    return (0);
}

void free_env(struct chat_env *env)
{
    if (env->fds) {
        free(env->fds);
    }
    if (env->clients) {
        free(env->clients);
    }
}

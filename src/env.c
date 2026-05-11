#include "chat.h"
#include <stdlib.h>

int init_env(struct chat_env *env, struct config *settings, int server_fd)
{
    int i;

    env->server_fd = server_fd;
    env->max_clients = settings->limit;
    env->fds = malloc(sizeof(struct pollfd) * (size_t) (settings->limit + 1));
    env->clients = malloc(sizeof(struct client) * (size_t) settings->limit);
    if (!env->fds || !env->clients) {
        return (1);
    }
    env->fds[0].fd = server_fd;
    env->fds[0].events = POLLIN;
    i = 1;
    while (i <= settings->limit) {
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

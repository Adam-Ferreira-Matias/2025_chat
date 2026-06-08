/*
 * E89 Pedagogical & Technical Lab
 * project: env file
 * created on:  2026-06-08 - 09:03 +0200
 * 1st author:  bastien.goodall
 * description: file for env (free and init)
 */

#include "chat.h"
#include <stdlib.h>

int init_env(struct chat_env *env, struct config *settings, int server_fd)
{
    int i;

    env->server_fd = server_fd;
    env->max_clients = settings->limit;
    env->fds = malloc(sizeof(struct pollfd) * (size_t) (settings->limit + 2));
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
    env->fds[settings->limit + 1].fd = 0;
    env->fds[settings->limit + 1].events = POLLIN;
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


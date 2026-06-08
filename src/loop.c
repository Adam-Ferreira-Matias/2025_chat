/*
 * E89 Pedagogical & Technical Lab
 * project: loop file
 * created on:  2026-06-08 - 09:04 +0200
 * 1st author:  bastien.goodall
 * description: file for loop function
 */

#include "chat.h"

void run_chat(struct chat_env *env)
{
    int i;

    env->fds[0].events = POLLIN;
    while (1) {
        poll(env->fds, (nfds_t) (env->max_clients + 2), -1);
        if (env->fds[0].revents & POLLIN) {
            accept_client(env);
        }
        if (env->fds[env->max_clients + 1].revents & POLLIN) {
            handle_admin(env);
        }
        i = 1;
        while (i <= env->max_clients) {
            if (env->fds[i].fd != -1) {
                if (env->fds[i].revents & (POLLIN | POLLHUP | POLLERR)) {
                    handle_client(env, i);
                }
            }
            i += 1;
        }
    }
}


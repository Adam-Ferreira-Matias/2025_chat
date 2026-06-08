/*
 * E89 Pedagogical & Technical Lab
 * project: clavardage
 * created on:  2026-06-08 - 09:36 +0200
 * 1st author:  adam.ferreira
 * description: command to send an private message
 */

#include "chat.h"
#include <unistd.h>
#include <stddef.h>

static int wisp_find_target(struct chat_env *env, char *buf)
{
    int k;

    k = 1;
    while (k <= env->max_clients) {
        if (env->fds[k].fd != -1 && env->clients[k - 1].nick != NULL) {
            if (stu_strncmp(env->clients[k - 1].nick, buf + 6,
    stu_strlen(env->clients[k - 1].nick)) == 0) {
                return (k);
            }
        }
        k += 1;
    }
    return (-1);
}

static int wisp_get_msg_index(char *buf)
{
    int j;

    j = 6;
    while (buf[j] != '\0' && buf[j] != ' ' && buf[j] != '\n') {
        j += 1;
    }
    if (buf[j] != ' ' || buf[j + 1] == '\0' || buf[j + 1] == '\n') {
        return (-1);
    }
    return (j + 1);
}

static void wisp_send(struct chat_env *env, int target, char *prefix, char *msg)
{
    write(env->fds[target].fd, "[Wisp of ", 9);
    write(env->fds[target].fd, prefix, stu_strlen(prefix));
    write(env->fds[target].fd, "]: ", 3);
    write(env->fds[target].fd, msg, stu_strlen(msg));
}

void wisp(struct chat_env *env, int i)
{
    char *buf;
    int  target_index;
    int j;
    char *sender_prefix;

    buf = env->clients[i - 1].buf;
    target_index = wisp_find_target(env, buf);
    if (target_index == -1) {
        write(env->fds[i].fd, "Error: User not found or not logged in.\n", 40);
        return ;
    }
    j = wisp_get_msg_index(buf);
    if (j == -1) {
        write(env->fds[i].fd, "Erreur : Message vide.\n", 23);
        return ;
    }
    sender_prefix = "Guest";
    if (env->clients[i - 1].nick != NULL) {
        sender_prefix = env->clients[i - 1].nick;
    }
    wisp_send(env, target_index, sender_prefix, &buf[j]);
}

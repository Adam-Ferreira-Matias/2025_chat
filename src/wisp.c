#include "chat.h"
#include <unistd.h>
#include <stddef.h>

void wisp(struct chat_env *env, int i)
{
    char *buf;
    int k;
    int j;
    int target_index;
    unsigned int msg_len;
    char *sender_prefix;

    buf = env->clients[i - 1].buf;
    target_index = -1;

    k = 1;
    while (k <= env->max_clients) {
        if (env->fds[k].fd != -1 && env->clients[k - 1].nick != NULL) {
            if (stu_strcmp_space(env->clients[k - 1].nick, buf + 6) == 0) {
                target_index = k;
                break;
            }
        }
        k += 1;
    }

    if (target_index == -1) {
        write(env->fds[i].fd,
              "Erreur : Utilisateur introuvable ou non connecte.\n", 50);
        return;
    }

    j = 6;
    while (buf[j] != '\0' && buf[j] != ' ' && buf[j] != '\n') {
        j += 1;
    }

    if (buf[j] != ' ' || buf[j + 1] == '\0' || buf[j + 1] == '\n') {
        write(env->fds[i].fd, "Erreur : Message vide.\n", 23);
        return;
    }
    j += 1;

    sender_prefix = "Guest";
    if (env->clients[i - 1].nick != NULL) {
        sender_prefix = env->clients[i - 1].nick;
    }

    msg_len = stu_strlen(&buf[j]);

    write(env->fds[target_index].fd, "[Wisp de ", 9);
    write(env->fds[target_index].fd, sender_prefix, (size_t)stu_strlen(sender_prefix));
    write(env->fds[target_index].fd, "] : ", 4);
    write(env->fds[target_index].fd, &buf[j], (size_t)msg_len);
}

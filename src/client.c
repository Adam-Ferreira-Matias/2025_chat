#include "chat.h"
#include <sys/socket.h>
#include <unistd.h>

void accept_client(struct chat_env *env)
{
    int fd;
    int i;

    fd = accept(env->server_fd, (struct sockaddr *) 0, (socklen_t *) 0);
    if (fd < 0) {
        return;
    }
    i = 1;
    while (i <= env->max_clients) {
        if (env->fds[i].fd == -1) {
            env->fds[i].fd = fd;
            env->clients[i - 1].fd = fd;
            return;
        }
        i += 1;
    }
    close(fd);
}

void broadcast_msg(struct chat_env *env, int sender_fd, char *msg, int len)
{
    int i;
    int fd;

    i = 1;
    while (i <= env->max_clients) {
        fd = env->fds[i].fd;
        if (fd != -1 && fd != sender_fd) {
            write(fd, msg, (size_t) len);
        }
        i += 1;
    }
}

void disconnect_client(struct chat_env *env, int i)
{
    close(env->fds[i].fd);
    env->fds[i].fd = -1;
    env->clients[i - 1].fd = -1;
}

void handle_client(struct chat_env *env, int i)
{
    char buf[1024];
    int len;

    len = read(env->fds[i].fd, buf, 1024);
    if (len <= 0) {
        disconnect_client(env, i);
        return;
    }
    if (len >= 7 && stu_strncmp(buf, "/logout", 7) == 0) {
        broadcast_msg(env, env->fds[i].fd, "Someone leave\n", 14);
        disconnect_client(env, i);
        return;
    }
    broadcast_msg(env, env->fds[i].fd, buf, len);
}

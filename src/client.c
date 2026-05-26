#include "chat.h"
#include <sys/socket.h>
#include <unistd.h>

void cmd_logout(struct chat_env *env, int i)
{
    broadcast_msg(env, env->fds[i].fd, "Someone leave\n", 14);
    disconnect_client(env, i);
}

struct chat OP_TABLE[] = {
    {"/logout", cmd_logout},
};

const int OP_TABLE_LEN = sizeof(OP_TABLE) / sizeof(struct chat);

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
    int j;

    j = 0;
    len = read(env->fds[i].fd, buf, 1024);
    if (len <= 0) {
        disconnect_client(env, i);
        return;
    }
    if (buf[0] == '/') {
        while (j < OP_TABLE_LEN) {
            if (stu_strcmp_space(OP_TABLE[j].symbol, buf) == 0) {
                OP_TABLE[j].fptr(env, i);
                return;
            }
            j += 1;
        }
    } else {
        broadcast_msg(env, env->fds[i].fd, buf, len);
    }
}

int stu_strcmp_space(const char *s1, const char *s2)
{
    int i;

    i = 0;
    while (s1[i] != '\0' && s2[i] != ' ' && s2[i] != '\0' && s2[i] != '\n') {
        if (s1[i] != s2[i]) {
            return 1;
        }
        i = i + 1;
    }
    return 0;
}
/*void nick (struct chat_env *env, int i)
{
    return ;
}*/

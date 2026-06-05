#include "chat.h"
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void cmd_logout(struct chat_env *env, int i)
{
    broadcast_msg(env, env->fds[i].fd, "Someone leave\n", 14);
    disconnect_client(env, i);
}

struct chat OP_TABLE[] = {
    {"/nick", nick},
    {"/logout", cmd_logout},
    {"/shrek", shrek},
    {"/among_us", among_us},
    {"/list", cmd_list},
    {"/help", help},
    {"/wisp", wisp},
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
            env->clients[i - 1].nick = NULL;
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
    char *prefix;

    prefix = "Guest";
    i = 1;
    while (i <= env->max_clients) {
        if (env->fds[i].fd == sender_fd) {
            if (env->clients[i - 1].nick != NULL) {
                prefix = env->clients[i - 1].nick;
            }
            break;
        }
        i += 1;
    }
    i = 1;
    while (i <= env->max_clients) {
        fd = env->fds[i].fd;
        if (fd != -1 && fd != sender_fd) {
            write(fd, prefix, stu_strlen(prefix));
            write(fd, " : ", 3);
            write(fd, msg, (size_t)len);
        }
        i += 1;
    }
}

void disconnect_client(struct chat_env *env, int i)
{
    close(env->fds[i].fd);
    env->fds[i].fd = -1;
    env->clients[i - 1].fd = -1;
    free(env->clients[i - 1].nick);
    env->clients[i - 1].nick = NULL;
}

void handle_client(struct chat_env *env, int i)
{
    char buf[1024];
    int len;
    int j;

    j = 0;
    len = read(env->fds[i].fd, buf, 1024);
    buf[len] = '\0';
    if (len <= 0) {
        disconnect_client(env, i);
        return;
    }
    if (buf[0] == '/') {
        while (j < OP_TABLE_LEN) {
            env->clients[i - 1].buf = buf;
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

static int is_valid_nick(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '\n') {
        if (!((str[i] >= 'a' && str[i] <= 'z')
            || (str[i] >= 'A' && str[i] <= 'Z')
            || (str[i] >= '0' && str[i] <= '9')
            || str[i] == '-' || str[i] == '_')) {
            return 0;
        }
        i += 1;
    }
    return (1);
}

void nick (struct chat_env *env, int i)
{
    char *buf;

    buf = env->clients[i - 1].buf;
    if (!is_valid_nick(buf + 6)) {
        write(env->clients[i - 1].fd, "NAH HUNNNN error your pseudo aren't correct\n", 44);
        return ;
    }
    env->clients[i - 1].nick = stu_strdup(buf + 6);
    env->clients[i - 1].nick[stu_strlen(env->clients[i - 1].nick) - 1] = '\0';
}

void shrek(struct chat_env *env, int i)
{
    char buf[4096];
    int  fd;
    int  len;

    write(env->clients[i - 1].fd, "you have summon shrek!\n", 23);
    broadcast_msg(env, env->fds[i].fd, "has summon shrek!\n", 18);
    fd = open("image_ascii/shrek.txt", O_RDONLY);
    if (fd < 0) {
        return;
    }
    while ((len = read(fd, buf, sizeof(buf))) > 0) {
        i = 1;
        while (i <= env->max_clients) {
            if (env->fds[i].fd != -1) {
                write(env->fds[i].fd, buf, len);
            }
            i += 1;
        }
    }
    close(fd);
}

void among_us(struct chat_env *env, int i)
{
    char buf[4096];
    int  fd;
    int  len;

    write(env->clients[i - 1].fd, "you have summon among us!\n", 26);
    broadcast_msg(env, env->fds[i].fd, "AMOGUS !\n", 9);
    fd = open("image_ascii/among_us.txt", O_RDONLY);
    if (fd < 0) {
        return;
    }
    while ((len = read(fd, buf, sizeof(buf))) > 0) {
        i = 1;
        while (i <= env->max_clients) {
            if (env->fds[i].fd != -1) {
                write(env->fds[i].fd, buf, len);
            }
            i += 1;
        }
    }
    close(fd);
}

void cmd_list(struct chat_env *env, int i)
{
    int j;
    int requester_fd;

    requester_fd = env->clients[i - 1].fd;
    write(requester_fd, "Connected users:\n", 17);
    j = 1;
    while (j <= env->max_clients) {
        if (env->fds[j].fd != -1) {
            write(requester_fd, "- ", 2);
            if (env->clients[j - 1].nick != NULL) {
                write(requester_fd, env->clients[j - 1].nick, stu_strlen(env->clients[j - 1].nick));
            } else {
                write(requester_fd, "Guest", 5);
            }
            if (env->fds[j].fd == requester_fd) {
                write(requester_fd, " (you)", 6);
            }
            write(requester_fd, "\n", 1);
        }
        j += 1;
    }
}

void help(struct chat_env *env, int i)
{
    write(env->clients[i - 1].fd, "   /nick:         for setup your nickname\n \
  /logout:       to leave the server\n \
  /shrek:        cat an ascii of shrek\n \
  /among_us:     cat an ascii of among us\n \
  /list:         allow you to see who is connected\n \
", 215);
}

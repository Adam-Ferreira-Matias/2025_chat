/*
 * E89 Pedagogical & Technical Lab
 * project: client file
 * created on:  2026-06-08 - 09:02 +0200
 * 1st author:  bastien.goodall
 * description: file with all important function for client
 */

#include <fcntl.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include "chat.h"

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
            env->clients[i - 1].id = i;
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
    struct client *sender;

    i = 1;
    sender = NULL;
    while (i <= env->max_clients) {
        if (env->fds[i].fd == sender_fd) {
            sender = &env->clients[i - 1];
            break;
        }
        i += 1;
    }
    i = 1;
    while (i <= env->max_clients) {
        fd = env->fds[i].fd;
        if (fd != -1 && fd != sender_fd && sender != NULL) {
            write_nick_or_guest(fd, sender);
            write(fd, ": ", 2);
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

void nick(struct chat_env *env, int i)
{
    char *buf;

    buf = env->clients[i - 1].buf;
    if (!is_valid_nick(buf + 6)) {
        write(env->clients[i - 1].fd,
            "NAH HUNNNN error your pseudo aren't correct\n", 44);
        return;
    }
    env->clients[i - 1].nick = stu_strdup(buf + 6);
    env->clients[i - 1].nick[stu_strlen(env->clients[i - 1].nick) - 1] = '\0';
}

void shrek(struct chat_env *env, int i)
{
    char buf[4096];
    int fd;
    int len;

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
    int fd;
    int len;

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

void write_nick_or_guest(int fd, struct client *client)
{
    char *num;

    if (client->nick != NULL) {
        write(fd, client->nick, stu_strlen(client->nick));
    } else {
        num = base10_to_char(client->id);
        write(fd, "Guest", 5);
        write(fd, num, stu_strlen(num));
        free(num);
    }
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
            write_nick_or_guest(requester_fd, &env->clients[j - 1]);
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
    write(env->clients[i - 1].fd,
        "   /nick         for setup your nickname\n"
        "   /logout       to leave the server\n"
        "   /shrek        cat an ascii of shrek\n"
        "   /among_u      cat an ascii of among us\n"
        "   /list         allow you to see who is connected\n",
        210);
}

static void broadcast_kick(struct chat_env *env, char *target_nick,
                           unsigned int nick_len)
{
    char msg[128];
    unsigned int msg_len;
    int j;

    msg_len = 0;
    while (target_nick[msg_len] != '\0' && msg_len < 64) {
        msg[msg_len] = target_nick[msg_len];
        msg_len += 1;
    }
    msg[msg_len] = '\0';
    j = 1;
    while (j <= env->max_clients) {
        if (env->fds[j].fd != -1) {
            write(env->fds[j].fd, msg, msg_len);
            write(env->fds[j].fd, " was kicked by an Admin\n", 24);
        }
        j += 1;
    }
    (void) nick_len;
}

static void kick_by_nick(struct chat_env *env, char *nick)
{
    int j;
    char *target_nick;
    unsigned int nick_len;

    nick_len = stu_strlen(nick);
    j = 1;
    while (j <= env->max_clients) {
        if (env->clients[j - 1].nick == NULL) {
            j += 1;
            continue;
        }
        target_nick = env->clients[j - 1].nick;
        if (stu_strncmp(target_nick, nick, (int) nick_len) == 0
            && stu_strlen(target_nick) == nick_len) {
            write(env->clients[j - 1].fd,
                "You have been kicked by an Admin\n", 33);
            broadcast_kick(env, target_nick, nick_len);
            disconnect_client(env, j);
            write(1, "User kicked.\n", 13);
            return;
        }
        j += 1;
    }
    write(1, "User not found.\n", 16);
}

void handle_admin(struct chat_env *env)
{
    char buf[256];
    int  len;

    len = read(0, buf, 255);
    if (len <= 0) {
        return ;
    }
    buf[len] = '\0';
    if (buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
        len -= 1;
    }
    if (stu_strncmp(buf, "/kick ", 6) == 0 && len > 6) {
        kick_by_nick(env, buf + 6);
    } else if (stu_strcmp(buf, "/shutdown") == 0) {
        shutdown_server(env, 0);
    } else {
        write(1, "Admin commands: /kick <nick> | /shutdown\n", 41);
    }
}

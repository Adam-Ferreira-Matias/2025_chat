#ifndef CHAT_H_
#define CHAT_H_

#include <poll.h>

struct config {
    int port;
    int fallback;
    int limit;
};

struct client {
    int fd;
};

struct chat_env {
    int server_fd;
    int max_clients;
    struct pollfd *fds;
    struct client *clients;
};

int stu_strcmp(const char *s1, const char *s2);
int stu_atoi(const char *str);
void init_config(struct config *cfg);
int parse_args(int ac, char **av, struct config *cfg);
int init_server(struct config *cfg);

int init_env(struct chat_env *env, struct config *cfg, int server_fd);
void free_env(struct chat_env *env);
void run_chat(struct chat_env *env);
void accept_client(struct chat_env *env);
void handle_client(struct chat_env *env, int i);
void broadcast_msg(struct chat_env *env, int sender_fd, char *msg, int len);

#endif

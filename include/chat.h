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
    char *nick;
    char *buf;
};

struct chat_env {
    int server_fd;
    int max_clients;
    struct pollfd *fds;
    struct client *clients;
};

struct chat {
    char *symbol;
    void (*fptr)(struct chat_env *env, int i);
};

int stu_strcmp(const char *s1, const char *s2);
int stu_strncmp(const char *s1, const char *s2, int n);
char *stu_strdup(char *str);
unsigned int stu_strlen(const char *str);
int stu_atoi(const char *str);
void init_config(struct config *settings);
int parse_args(int ac, char **av, struct config *settings);
int init_server(struct config *settings);
int stu_strcmp_space(const char *s1, const char *s2);
int init_env(struct chat_env *env, struct config *settings, int server_fd);
void free_env(struct chat_env *env);
void run_chat(struct chat_env *env);
void accept_client(struct chat_env *env);
void disconnect_client(struct chat_env *env, int i);
void handle_client(struct chat_env *env, int i);
void broadcast_msg(struct chat_env *env, int sender_fd, char *msg, int len);
void nick (struct chat_env *env, int i);
void cmd_logout(struct chat_env *env, int i);
void shrek(struct chat_env *env, int i);
void among_us(struct chat_env *env, int i);

#endif

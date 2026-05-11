#ifndef CHAT_H_
#define CHAT_H_

struct config {
    int port;
    int fallback;
    int limit;
};

int stu_strcmp(const char *s1, const char *s2);
int stu_atoi(const char *str);
void init_config(struct config *cfg);
int parse_args(int ac, char **av, struct config *cfg);
int init_server(struct config *cfg);

#endif

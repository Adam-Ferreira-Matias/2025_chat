#include "chat.h"

void init_config(struct config *cfg)
{
    cfg->port = 0;
    cfg->fallback = 0;
    cfg->limit = 0;
}

int parse_args(int ac, char **av, struct config *cfg)
{
    int i;

    init_config(cfg);
    i = 1;
    while (i < ac) {
        if (stu_strcmp(av[i], "-p") == 0 && i + 1 < ac) {
            cfg->port = stu_atoi(av[i + 1]);
            i += 1;
        } else if (stu_strcmp(av[i], "-f") == 0) {
            cfg->fallback = 1;
        } else if (stu_strcmp(av[i], "-l") == 0 && i + 1 < ac) {
            cfg->limit = stu_atoi(av[i + 1]);
            i += 1;
        } else {
            return (1);
        }
        i += 1;
    }
    return (0);
}

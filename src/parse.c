#include "chat.h"

void init_config(struct config *settings)
{
    settings->port = 0;
    settings->fallback = 0;
    settings->limit = 0;
}

int parse_args(int ac, char **av, struct config *settings)
{
    int i;

    init_config(settings);
    i = 1;
    while (i < ac) {
        if (stu_strcmp(av[i], "-p") == 0 && i + 1 < ac) {
            settings->port = stu_atoi(av[i + 1]);
            i += 1;
        } else if (stu_strcmp(av[i], "-f") == 0) {
            settings->fallback = 1;
        } else if (stu_strcmp(av[i], "-l") == 0 && i + 1 < ac) {
            settings->limit = stu_atoi(av[i + 1]);
            i += 1;
        } else {
            return (1);
        }
        i += 1;
    }
    return (0);
}

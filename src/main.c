#include "chat.h"
#include <unistd.h>

int main(int ac, char **av)
{
    struct config settings;
    struct chat_env env;
    int server_fd;

    if (parse_args(ac, av, &settings) != 0 || settings.port == 0 || settings.limit == 0) {
        write(2, "Usage: ./chat_server -p PORT -l LIMIT [-f]\n", 43);
        return (1);
    }
    server_fd = init_server(&settings);
    if (server_fd < 0) {
        write(2, "Failed to start server\n", 23);
        return (1);
    }
    if (init_env(&env, &settings, server_fd) == 0) {
        run_chat(&env);
        free_env(&env);
    }
    close(server_fd);
    return (0);
}

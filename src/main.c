#include "chat.h"
#include <unistd.h>

int main(int ac, char **av)
{
    struct config cfg;
    int server_fd;

    if (parse_args(ac, av, &cfg) != 0 || cfg.port == 0 || cfg.limit == 0) {
        write(2, "Usage: ./chat_server -p PORT -l LIMIT [-f]\n", 43);
        return (1);
    }
    server_fd = init_server(&cfg);
    if (server_fd < 0) {
        write(2, "Failed to start server\n", 23);
        return (1);
    }
    write(1, "Server started successfully.\n", 29);
    close(server_fd);
    return (0);
}

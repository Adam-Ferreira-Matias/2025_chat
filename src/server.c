#include "chat.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int configure_socket(int sock)
{
    const int opt = 1;

    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        return (1);
    }
    return (0);
}

int attempt_bind(int sock, int port)
{
    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons((uint16_t) port);
    if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        return (1);
    }
    return (0);
}

int bind_server(int sock, struct config *cfg)
{
    int bound;

    bound = 0;
    while (!bound) {
        if (attempt_bind(sock, cfg->port) == 0) {
            bound = 1;
        } else if (cfg->fallback) {
            cfg->port += 1;
        } else {
            return (1);
        }
    }
    return (0);
}

int init_server(struct config *cfg)
{
    int sock;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        return (-1);
    }
    if (configure_socket(sock) || bind_server(sock, cfg)) {
        close(sock);
        return (-1);
    }
    if (listen(sock, cfg->limit) < 0) {
        close(sock);
        return (-1);
    }
    return (sock);
}

#include "chat.h"
#include <string.h>
#include <unistd.h>
#include <assert.h>

static void test_wisp_scenario(char *client_buf, char *client_nick,
                               const char *expected)
{
    struct chat_env env;
    struct client clients[2];
    struct pollfd fds[3];
    int fd_pipe[2];
    char output[1024];

    memset(output, 0, 1024);
    assert(pipe(fd_pipe) != -1);

    env.max_clients = 2;
    env.clients = clients;
    env.fds = fds;

    fds[1].fd = fd_pipe[1];
    clients[0].nick = "Target";
    clients[0].buf = "";

    fds[2].fd = fd_pipe[1];
    clients[1].nick = client_nick;
    clients[1].buf = client_buf;

    wisp(&env, 2);
    read(fd_pipe[0], output, 1023);

    assert(strncmp(output, expected, strlen(expected)) == 0);

    close(fd_pipe[0]);
    close(fd_pipe[1]);
}

int main(void)
{
    test_wisp_scenario("/wisp Target Hello!", "Sender",
                       "[Wisp de Sender] : Hello!");
    test_wisp_scenario("/wisp Ghost Hello!", "Sender",
                       "Erreur : Utilisateur introuvable.\n");
    test_wisp_scenario("/wisp Target  ", "Sender",
                       "Erreur : Message vide.\n");

    return 0;
}

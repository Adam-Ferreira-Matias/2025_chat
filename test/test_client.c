#include "chat.h"
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

static void check_strcmp_space(void)
{
    assert(stu_strcmp_space("/nick", "/nick") == 0);
    assert(stu_strcmp_space("/nick", "/nick Bob") == 0);
    assert(stu_strcmp_space("/wisp", "/nick") != 0);
    assert(stu_strcmp_space("/ni", "/nick") != 0);
    assert(stu_strcmp_space("/nickname", "/nick") != 0);
}

static void check_nick(void)
{
    struct chat_env env;
    struct client c[1];
    int p[2];
    char out[1024];

    assert(pipe(p) != -1);
    memset(out, 0, 1024);
    env.clients = c;
    c[0].fd = p[1];
    c[0].nick = NULL;
    c[0].buf = "/nick Bob";

    nick(&env, 1);
    assert(c[0].nick != NULL);
    assert(strncmp(c[0].nick, "Bob", 3) == 0);
    free(c[0].nick);

    c[0].nick = NULL;
    c[0].buf = "/nick B@d";
    nick(&env, 1);
    assert(c[0].nick == NULL);

    read(p[0], out, 1023);
    assert(out[0] != '\0');

    close(p[0]);
    close(p[1]);
}

int main(void)
{
    check_strcmp_space();
    check_nick();
    return 0;
}

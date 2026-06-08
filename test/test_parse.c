#include "chat.h"
#include <assert.h>

int main(void)
{
    struct config cfg;
    char *a1[] = {"./srv", "-p", "80", "-l", "5"};
    char *a2[] = {"./srv", "-p", "80", "-f", "-l", "5"};
    char *e1[] = {"./srv", "-p"};
    char *e2[] = {"./srv", "-x"};
    char *e3[] = {"./srv", "-p", "80", "-l"};

    assert(parse_args(5, a1, &cfg) == 0);
    assert(cfg.port == 80);
    assert(cfg.limit == 5);
    assert(cfg.fallback == 0);

    assert(parse_args(6, a2, &cfg) == 0);
    assert(cfg.port == 80);
    assert(cfg.limit == 5);
    assert(cfg.fallback == 1);

    assert(parse_args(2, e1, &cfg) == 1);
    assert(parse_args(2, e2, &cfg) == 1);
    assert(parse_args(4, e3, &cfg) == 1);

    return 0;
}

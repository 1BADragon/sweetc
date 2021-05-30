#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <sc/hooks.h>

static struct sc_hooks {
    void *(*alloc)(size_t);
    void (*free)(void *ptr);
} hooks = {
    malloc,
    free,
};

int sc_set_hook(enum sc_hook_vals val, void *hook)
{
    switch (val) {
    case SC_HOOK_ALLOC:
        hooks.alloc = hook;
        break;
    case SC_HOOK_FREE:
        hooks.free = hook;
        break;
    default:
        errno = EINVAL;
        return -1;
    }

    return 0;
}

void *sc_zalloc(size_t size)
{
    void *chunk = hooks.alloc(size);

    if (NULL == chunk) {
        return NULL;
    }

    return memset(chunk, 0, size);
}

void sc_free(void *ptr)
{
    hooks.free(ptr);
}

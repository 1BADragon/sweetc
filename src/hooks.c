#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <sc/hooks.h>

static struct sc_hooks {
    sc_alloc_t alloc;
    sc_free_t free;
    sc_realloc_t realloc;
} hooks = {
    malloc,
    free,
    realloc,
};

int sc_set_hook(enum sc_hook_vals val, void *hook)
{
    assert(hook);

    switch (val) {
    case SC_HOOK_ALLOC:
        hooks.alloc = hook;
        break;
    case SC_HOOK_FREE:
        hooks.free = hook;
        break;
    case SC_HOOK_REALLOC:
        hooks.realloc = hook;
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

void *sc_realloc(void *ptr, size_t size)
{
    return hooks.realloc(ptr, size);
}

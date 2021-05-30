#ifndef _SC_HOOKS_H
#define _SC_HOOKS_H

#include <stddef.h>

enum sc_hook_vals {
    SC_HOOK_ALLOC,
    SC_HOOK_FREE,
};

int sc_set_hook(enum sc_hook_vals, void *hook);

void *sc_zalloc(size_t size);

void sc_free(void *ptr);

#endif // _SC_HOOKS_H

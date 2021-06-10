#ifndef _SC_MACROS_H
#define _SC_MACROS_H

#define UNUSED __attribute__((unused))

#define container_of(ptr, type, member)                                                            \
    ({                                                                                             \
        const typeof(((type *)0)->member) *__mptr = (ptr);                                         \
        (type *)((char *)__mptr - offsetof(type, member));                                         \
    })

#define MAX(a, b)                                                                                  \
    ({                                                                                             \
        typeof(a) _a = (a);                                                                        \
        typeof(b) _b = (b);                                                                        \
        (_a > _b) ? _a : _b;                                                                       \
    })

#define MIN(a, b)                                                                                  \
    ({                                                                                             \
        typeof(a) _a = (a);                                                                        \
        typeof(b) _b = (b);                                                                        \
        (_a < _b) ? _a : _b;                                                                       \
    })

#endif

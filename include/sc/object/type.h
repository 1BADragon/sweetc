#ifndef _SC_OBJECT_TYPE_H
#define _SC_OBJECT_TYPE_H

#include <sc/traits.h>

struct sc_type {
    const char *name;
    void *triats[SC_TRAITS_MAX];
};

#endif // _SC_OBJECT_TYPE_H

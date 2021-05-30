#ifndef _SC_TRAIT_HASHABLE_H
#define _SC_TRAIT_HASHABLE_H

#include <stddef.h>

#define SC_TRAIT_HASHABLE (3)

struct sc_object;

typedef size_t (*sc_hash_f)(struct sc_object *);

struct sc_trait_hashable {
    sc_hash_f hash_f;
};

#endif // _SC_TRAIT_HASHABLE_H

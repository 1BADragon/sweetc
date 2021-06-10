#ifndef _SC_TRAIT_PARTIAL_CMP_H
#define _SC_TRAIT_PARTIAL_CMP_H

#include <stdbool.h>

#define SC_TRAIT_PARTIAL_CMP (2)

#define sc_trait_partial_cmp(obj)                                                                  \
    ((struct sc_trait_partial_cmp *)sc_object_trait((obj), SC_TRAIT_PARTIAL_CMP))

struct sc_object;

typedef bool (*sc_partial_cmp_f)(struct sc_object *, struct sc_object *);

struct sc_trait_partial_cmp {
    sc_partial_cmp_f partial_cmp_f;
};

bool sc_object_partial_cmp(void *a, void *b);

#endif

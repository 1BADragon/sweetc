#ifndef _SC_TRAIT_CMP_H
#define _SC_TRAIT_CMP_H

#define SC_TRAIT_CMP (1)

#define sc_trait_cmp(obj) ((struct sc_trait_cmp *)sc_object_trait((obj), SC_TRAIT_CMP))

struct sc_object;

typedef int (*sc_cmp_f)(struct sc_object *, struct sc_object *);

struct sc_trait_cmp {
    sc_cmp_f cmp_f;
};

int sc_object_cmp(void *a, void *b);

#endif // _SC_TRAIT_CMP_H

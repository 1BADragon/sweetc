#ifndef _SC_TRAIT_CMP_H
#define _SC_TRAIT_CMP_H

#define SC_TRAIT_CMP (1)

struct sc_object;

typedef int (*sc_cmp_f)(struct sc_object *, struct sc_object *);

struct sc_trait_cmp {
    sc_cmp_f cmp_f;
};

#endif // _SC_TRAIT_CMP_H

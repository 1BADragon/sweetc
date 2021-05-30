#ifndef _SC_TRAIT_OBJECT_H
#define _SC_TRAIT_OBJECT_H

#define SC_TRAIT_OBJECT (0)

#define sc_trait_object(obj) ((struct sc_trait_object *)sc_object_trait((obj), SC_TRAIT_OBJECT))

struct sc_object;

typedef void (*sc_free_f)(struct sc_object *);

struct sc_trait_object {
    sc_free_f free_f;
};

void sc_object_free(void *obj);

#endif

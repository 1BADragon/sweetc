#include <assert.h>

#include <sc/traits.h>
#include <sc/traits/hashable.h>

size_t sc_object_hash(struct sc_object *obj)
{
    struct sc_trait_hashable *trait;

    trait = sc_trait_hashable(obj);
    assert(trait);

    return trait->hash_f(obj);
}

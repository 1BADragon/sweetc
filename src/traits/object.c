#include <assert.h>

#include <sc/traits.h>
#include <sc/traits/object.h>

void sc_object_free(void *obj)
{
    struct sc_trait_object *trait;

    trait = sc_trait_object(obj);
    assert(trait);

    trait->free_f(obj);
}

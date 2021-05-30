#include <assert.h>

#include <sc/object/object.h>
#include <sc/traits.h>

void *sc_object_trait(struct sc_object *obj, uint32_t trait)
{
    void *t = obj->type->triats[trait];
    assert(t);
    return t;
}

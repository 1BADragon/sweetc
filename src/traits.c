#include <assert.h>

#include <sc/object/object.h>
#include <sc/traits.h>

void *sc_object_trait(struct sc_object *obj, uint32_t trait)
{
    assert(obj);
    assert(obj->type);
    void *t = obj->type->triats[trait];
    return t;
}

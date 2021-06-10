#include <assert.h>

#include <sc/object/object.h>
#include <sc/traits/cmp.h>

int sc_object_cmp(void *a, void *b)
{
    struct sc_trait_cmp *cmp = sc_object_trait(a, SC_TRAIT_CMP);

    assert(cmp);

    return cmp->cmp_f(a, b);
}

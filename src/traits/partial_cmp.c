#include <assert.h>

#include <sc/object/object.h>
#include <sc/traits/cmp.h>
#include <sc/traits/partial_cmp.h>

bool sc_object_partial_cmp(void *a, void *b)
{
    struct sc_trait_partial_cmp *partial;

    partial = sc_trait_partial_cmp(a);

    if (NULL == partial) {
        struct sc_trait_cmp *cmp = sc_trait_cmp(a);

        // NOTE: Should partial cmp fallback to comparing hashes?
        assert(cmp);

        return cmp->cmp_f(a, b) == 0;
    }

    return partial->partial_cmp_f(a, b);
}

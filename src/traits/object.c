#include <sc/traits.h>
#include <sc/traits/object.h>

void sc_object_free(void *obj)
{
    sc_trait_object(obj)->free_f(obj);
}

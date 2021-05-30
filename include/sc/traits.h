#ifndef _SC_TRAITS_H
#define _SC_TRAITS_H
#include <stdint.h>

// clang-format off
#include <sc/traits/object.h>       // 0
#include <sc/traits/cmp.h>          // 1
#include <sc/traits/partial_cmp.h>  // 2
#include <sc/traits/hashable.h>     // 3
// clang-format on

#define SC_TRAITS_MAX (4)

struct sc_object;

void *sc_object_trait(struct sc_object *obj, uint32_t trait);

#endif // _SC_TRAITS_H

#ifndef _SC_TRAITS_H
#define _SC_TRAITS_H
#include <stdint.h>

/**
 * @group SC_TRAITS
 * @brief Object traits define the various capabilities of a given type.
 */

// clang-format off
#include <sc/traits/object.h>       // 0
#include <sc/traits/cmp.h>          // 1
#include <sc/traits/partial_cmp.h>  // 2
#include <sc/traits/hashable.h>     // 3
// clang-format on

#define SC_TRAITS_MAX (4)

struct sc_object;

/**
 * @brief Obtain a pointer to the trait struct of a given object. This function is a helper function
 * and should not be called directly, instead use the macros sc_trait_*. The macros perform the
 * proper casting required.
 * @param obj A pointer to a valid sc object.
 * @param trait A trait value.
 * @return A non-null pointer to the trait requested. NULL if the object in question does not have
 * the triat requested.
 */
void *sc_object_trait(struct sc_object *obj, uint32_t trait);

#endif // _SC_TRAITS_H

#ifndef _SC_TRAIT_PARTIAL_CMP_H
#define _SC_TRAIT_PARTIAL_CMP_H

#include <stdbool.h>

#define SC_TRAIT_PARTIAL_CMP (2)

/**
 * @macro sc_trait_partial_cmp
 * @brief The partial compare trait compares the equality of two objects. Instead of a memcmp style
 * comparison function, this triat only detects the equality of the two objects; returning true if
 * the objects are equal and false otherwise. If the full compare triat is implemented for the
 * type then this trait will fallback to the cmp function if this trait is not explicitly defined.
 */
#define sc_trait_partial_cmp(obj)                                                                  \
    ((struct sc_trait_partial_cmp *)sc_object_trait((obj), SC_TRAIT_PARTIAL_CMP))

struct sc_object;

/**
 * @typedef sc_partial_cmp_f
 * @brief Function prototype for the partial compare function.
 */
typedef bool (*sc_partial_cmp_f)(struct sc_object *, struct sc_object *);

/**
 * @brief The sc_trait_partial_cmp struct holds the function pointers for the functions that are
 * used to define the partial compare trait.
 */
struct sc_trait_partial_cmp {
    /// The partial compare function
    sc_partial_cmp_f partial_cmp_f;
};

/**
 * @brief Calls the partial compare trait function. Like other traits, this function should be
 * called instead of calling the trait function pointers directly. Like the full compare function,
 * the triat used in the comparison is a's type.
 * @param a The first object to compare. This object's type is used for the triat function.
 * @param b The second object to compare.
 * @return true if the two objects are equal, false otherwise
 */
bool sc_object_partial_cmp(void *a, void *b);

#endif

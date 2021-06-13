#ifndef _SC_TRAIT_HASHABLE_H
#define _SC_TRAIT_HASHABLE_H

#include <stddef.h>

#define SC_TRAIT_HASHABLE (3)

/**
 * @macro sc_trait_hashable
 * @brief The hashable trait defines an types ability to be fingerprinted into a single integer
 * value. A type's hash function should be relatively fast and should make a resonable attempt to
 * prevent collisions with other object of the same type.
 */
#define sc_trait_hashable(obj)                                                                     \
    ((struct sc_trait_hashable *)sc_object_trait((obj), SC_TRAIT_HASHABLE))

struct sc_object;

/**
 * @typedef sc_hash_f
 * @brief The prototype for the hash function in the hashable trait. Takes a sc_object pointer and
 * returns a size_t value that fingerprints the object.
 */
typedef size_t (*sc_hash_f)(struct sc_object *);

/**
 * @brief The sc_trait_hashable struct contains the functions required to be defined for the trait.
 */
struct sc_trait_hashable {
    /// The hashable trait hash function.
    sc_hash_f hash_f;
};

/**
 * @brief The sweetc hash function. Used to hash any compatible sweetc object. This function should
 * be used instead of calling the trait function directly. This function should alway produce a
 * hash value and should never fail.
 * @param obj The object to hash.
 * @return The hash value for obj.
 */
size_t sc_object_hash(struct sc_object *obj);

#endif // _SC_TRAIT_HASHABLE_H

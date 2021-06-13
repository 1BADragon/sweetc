#ifndef _SC_TRAIT_OBJECT_H
#define _SC_TRAIT_OBJECT_H

#define SC_TRAIT_OBJECT (0)

/**
 * @macro sc_trait_object
 * @brief Returns the object trait from an object.
 * @param obj Object containing the trait.
 * @return Pointer to a struct sc_trait_object belonging to obj.
 */
#define sc_trait_object(obj) ((struct sc_trait_object *)sc_object_trait((obj), SC_TRAIT_OBJECT))

struct sc_object;

/**
 * @typedef sc_free_f
 * @brief The prototype for the struct sc_trait_object's free function. Takes one argument,
 * a pointer to the object in question. Should free the object completly.
 */
typedef void (*sc_free_f)(struct sc_object *);

/**
 * @brief The sc_trait_object struct contains the pointers the trait functions required to
 * implement this trait. This trait must be fully implemented for every type.
 */
struct sc_trait_object {
    /// Object's free function. Should completely free all associated data of an object.
    sc_free_f free_f;
};

/**
 * @brief Executor function for freeing an sweetc object. This function should be called when an
 * sc object needs to be free'ed. This function should be called not trait function's directly.
 * @param obj
 */
void sc_object_free(void *obj);

#endif

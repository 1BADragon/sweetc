#ifndef _SC_TRAIT_CMP_H
#define _SC_TRAIT_CMP_H

#define SC_TRAIT_CMP (1)

/**
 * @macro sc_trait_cmp
 * @brief Returns the cmp trait from an object. Used to compare two objects. Objects do not need
 * to be of the same type but the cmp triat function needs to be able to handle the secondary
 * object's type. This trait returns a value less than 0 when 'a' is less than 'b', 0 zero
 * if they are concidered equal, and a value greater than 0 when 'a' is greater than 'b'; similar
 * to memcmp or strcmp.
 */
#define sc_trait_cmp(obj) ((struct sc_trait_cmp *)sc_object_trait((obj), SC_TRAIT_CMP))

struct sc_object;

/**
 * @typedef sc_cmp_f
 * @brief The prototype of the cmp trait.
 */
typedef int (*sc_cmp_f)(struct sc_object *, struct sc_object *);

/**
 * @brief The sc_trait_cmp struct contains the functions available for the cmp trait.
 */
struct sc_trait_cmp {
    /// The compare function pointer.
    sc_cmp_f cmp_f;
};

/**
 * @brief Calls the compare trait's cmp function on a and b. When running this trait this function
 * should be called instead of calling a trait directly. When this trait is called, 'a''s trait is
 * used. If a can be compared with more types that its own its cmp function need to be able to
 * handle b's type.
 * @param a The first object to compare. This objects type triat is used for the compare function.
 * @param b The second object to compare.
 * @return <0, 0, >0 if a it greater than, equal to, or less than b, respectively
 */
int sc_object_cmp(void *a, void *b);

#endif // _SC_TRAIT_CMP_H

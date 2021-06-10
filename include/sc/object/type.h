#ifndef _SC_OBJECT_TYPE_H
#define _SC_OBJECT_TYPE_H

#include <sc/traits.h>

/**
 * @brief The sc_type struct defines the properties of an object's type. Type objects should be
 * statically allocated however, dynamic type creation is possible if you're feeling daring enough.
 */
struct sc_type {
    /// A pointer to a C style string containing the name of the type. This field is required.
    const char *name;
    /// Array of standard type traits certain traits are required for an object to be used with
    /// containers or other constructs in this library. SC_TRAIT_OBJECT is the only required trait.
    void *triats[SC_TRAITS_MAX];
};

#endif // _SC_OBJECT_TYPE_H

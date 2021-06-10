#ifndef _SC_OBJECT_OBJECT_H
#define _SC_OBJECT_OBJECT_H

#include <sc/object/type.h>

/**
 * @brief The sc_object struct define the base type header required for any managed object.
 * Typically, all objects are dynamically allocated with sc_zalloc and free'ed with sc_free.
 */
struct sc_object {
    /// Pointer to a type definition for a type. All objects of the same type should point to
    /// the same type struct.
    struct sc_type *type;
};

#endif

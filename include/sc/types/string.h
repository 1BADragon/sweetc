#ifndef _SC_TYPES_STRING_H
#define _SC_TYPES_STRING_H

#include <stddef.h>

struct sc_string;

typedef struct sc_string sc_string_t;

sc_string_t *sc_string_build_empty();

size_t sc_string_len(sc_string_t *str);

#endif // _SC_TYPES_STRING_H

#ifndef _SC_TYPES_STRING_H
#define _SC_TYPES_STRING_H

#include <stddef.h>
#include <stdint.h>

struct sc_string;

typedef struct sc_string sc_string_t;

sc_string_t *sc_string_build_empty(void);

sc_string_t *sc_string_build_str(const char *str);

sc_string_t *sc_string_build_raw(const uint8_t *data, size_t len);

sc_string_t *sc_string_take_raw(uint8_t *data, size_t len);

int sc_string_append_str(sc_string_t *str, const char *more);

int sc_string_append_raw(sc_string_t *str, const uint8_t *more, size_t len);

int sc_string_append_scstr(sc_string_t *str, sc_string_t *more);

int sc_string_strncmp(sc_string_t *str, char *rhs, size_t len);

size_t sc_string_len(sc_string_t *str);

char *sc_string_ptr(sc_string_t *str);

int sc_string_raw_cmp(sc_string_t *str, const uint8_t *rhs, size_t len);

#endif // _SC_TYPES_STRING_H

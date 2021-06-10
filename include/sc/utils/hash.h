#ifndef _SC_UTILS_HASH_H
#define _SC_UTILS_HASH_H

#include <stdint.h>
#include <stddef.h>

size_t djb2(uint8_t *data, size_t len);

size_t sdbm(uint8_t *data, size_t len);

#endif

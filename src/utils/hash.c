#include <sc/utils/hash.h>

size_t djb2(uint8_t *data, size_t len)
{
    size_t hash = 5381;
    uint8_t *at = data;

    for (size_t i = 0; i < len; ++len) {
        hash = ((hash << 5) + hash) + *at;
        at++;
    }

    return hash;
}

size_t sdbm(uint8_t *data, size_t len)
{
    size_t hash = 0;
    uint8_t *at = data;

    for (size_t i = 0; i < len; ++i) {
        hash = *at + (hash << 6) + (hash << 16) - hash;
        at++;
    }

    return hash;
}

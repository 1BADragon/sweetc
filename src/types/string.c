#include <assert.h>
#include <string.h>

#include <sc/hooks.h>
#include <sc/macros.h>
#include <sc/object/object.h>
#include <sc/types/string.h>
#include <sc/utils/hash.h>

#define DEFAULT_STRING_SIZE 32

struct sc_string {
    struct sc_object hdr;
    size_t loglen;
    size_t phylen;
    uint8_t *data;
};

static void sc_string_free(sc_string_t *str);
static int sc_string_cmp(sc_string_t *a, sc_string_t *b);
static int sc_string_reserve_for(sc_string_t *str, size_t len);
static size_t sc_string_hash(sc_string_t *str);

struct sc_trait_object sc_string_object_trait = {
    .free_f = (sc_free_f)sc_string_free,
};

struct sc_trait_cmp sc_string_cmp_trait = {
    .cmp_f = (sc_cmp_f)sc_string_cmp,
};

struct sc_trait_hashable sc_string_hashable_triat = {
    .hash_f = (sc_hash_f)sc_string_hash,
};

struct sc_type sc_string_type = {
    .name = "sc::string",
    .triats = {
        [SC_TRAIT_OBJECT] = &sc_string_object_trait,
        [SC_TRAIT_CMP] = &sc_string_cmp_trait,
        [SC_TRAIT_HASHABLE] = &sc_string_hashable_triat,
    },
};

sc_string_t *sc_string_build_empty(void)
{
    sc_string_t *ret = sc_zalloc(sizeof(sc_string_t));

    if (NULL == ret) {
        return NULL;
    }

    ret->data = sc_zalloc(DEFAULT_STRING_SIZE);

    if (NULL == ret->data) {
        sc_free(ret);
        return NULL;
    }

    ret->loglen = 0;
    ret->phylen = DEFAULT_STRING_SIZE;

    ret->hdr.type = &sc_string_type;

    return ret;
}

sc_string_t *sc_string_build_str(const char *str)
{
    sc_string_t *ret = sc_string_build_empty();

    if (NULL == ret) {
        return NULL;
    }

    if (sc_string_append_str(ret, str)) {
        sc_string_free(ret);
        return NULL;
    }

    return ret;
}

sc_string_t *sc_string_build_raw(const uint8_t *data, size_t len)
{
    sc_string_t *ret = sc_string_build_empty();

    if (NULL == ret) {
        return NULL;
    }

    if (sc_string_append_raw(ret, data, len)) {
        sc_string_free(ret);
        return NULL;
    }

    return ret;
}

sc_string_t *sc_string_take_raw(uint8_t *data, size_t len)
{
    sc_string_t *ret = sc_zalloc(sizeof(sc_string_t));

    uint32_t build_size = 2;

    while (build_size <= len) {
        build_size *= 2;
    }

    uint8_t *resized_data = sc_realloc(data, build_size);

    if (NULL == resized_data) {
        sc_free(ret);
        return NULL;
    }

    ret->phylen = build_size;
    ret->loglen = len;
    ret->data = resized_data;
    ret->hdr.type = &sc_string_type;
    return ret;
}

int sc_string_append_str(sc_string_t *str, const char *more)
{
    assert(str);
    assert(more);

    return sc_string_append_raw(str, (uint8_t *)more, strlen(more));
}

int sc_string_append_raw(sc_string_t *str, const uint8_t *more, size_t len)
{
    assert(str);
    assert(more);

    size_t required_size = str->loglen + len;

    if (sc_string_reserve_for(str, required_size)) {
        return -1;
    }

    memcpy(str->data + str->loglen, more, len);
    str->loglen += len;
    return 0;
}

int sc_string_append_scstr(sc_string_t *str, const sc_string_t *more)
{
    assert(str);
    assert(more);

    return sc_string_append_raw(str, more->data, more->loglen);
}

int sc_string_strncmp(sc_string_t *str, char *rhs, size_t len)
{
    return sc_string_raw_cmp(str, (uint8_t *)rhs, len);
}

static int sc_string_reserve_for(sc_string_t *str, size_t len)
{
    if (len >= str->phylen) {
        size_t new_size = str->phylen;
        while (new_size <= len) {
            new_size *= 2;
        }

        uint8_t *new_data = sc_realloc(str->data, new_size);

        if (!new_data) {
            return -1;
        }

        str->data = new_data;
        str->phylen = new_size;
    }

    return 0;
}

size_t sc_string_len(sc_string_t *str)
{
    return str->loglen;
}

char *sc_string_ptr(sc_string_t *str)
{
    assert(str);

    if (str->loglen == str->phylen) {
        sc_string_reserve_for(str, str->loglen + 1);
    }

    str->data[str->loglen] = '\0';

    return (char *)str->data;
}

int sc_string_raw_cmp(sc_string_t *str, const uint8_t *rhs, size_t len)
{
    size_t cmp_len = MIN(str->loglen, len);

    int rc = memcmp(str->data, rhs, cmp_len);

    if (0 == rc) {
        if (str->loglen > len) {
            return 1;
        } else if (str->loglen < len) {
            return -1;
        } else {
            return 0;
        }
    }

    return rc;
}

static void sc_string_free(sc_string_t *str)
{
    assert(str->hdr.type == &sc_string_type);
    sc_free(str->data);
    str->data = NULL;
    sc_free(str);
}

static int sc_string_cmp(sc_string_t *a, sc_string_t *b)
{
    assert(a->hdr.type == &sc_string_type);
    assert(b->hdr.type == &sc_string_type);

    return sc_string_raw_cmp(a, b->data, b->loglen);
}

static size_t sc_string_hash(sc_string_t *str)
{
    assert(str->hdr.type == &sc_string_type);
    return djb2(str->data, str->loglen);
}

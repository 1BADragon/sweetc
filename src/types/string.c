
#include <sc/hooks.h>
#include <sc/object/object.h>
#include <sc/types/string.h>

struct sc_string {
    struct sc_object hdr;
    size_t len;
    char data[];
};

static void sc_string_free(struct sc_string *str);

struct sc_trait_object sc_string_object_trait = {
    .free_f = (sc_free_f)sc_string_free,
};

struct sc_type sc_string_type = {
    .name = "sc::string",
    .triats = {
      [SC_TRAIT_OBJECT] = &sc_string_object_trait,
    },
};

sc_string_t *sc_string_build_empty()
{
    sc_string_t *ret = sc_zalloc(sizeof(struct sc_string));
    ret->hdr.type = &sc_string_type;

    return ret;
}

size_t sc_string_len(sc_string_t *str)
{
    return str->len;
}

static void sc_string_free(struct sc_string *str)
{
    sc_free(str);
}



set(DEFAULT_SRCS
        hooks.c traits.c
        traits/object.c traits/cmp.c traits/partial_cmp.c traits/hashable.c
        types/string.c
        containers/list.c
        utils/hash.c
        )
target_sources(sweetc PRIVATE ${DEFAULT_SRCS})

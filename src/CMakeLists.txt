

set(DEFAULT_SRCS
        hooks.c traits.c
        traits/object.c
        types/string.c
        )
target_sources(sweetc PRIVATE ${DEFAULT_SRCS})

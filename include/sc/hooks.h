#ifndef _SC_HOOKS_H
#define _SC_HOOKS_H

#include <stddef.h>

/**
 * @brief The sc_hook_vals enum define the various system hooks required by sweetc.
 */
enum sc_hook_vals
{
    /// Dynamic memory allocator for sweetc. This function should return an allocation
    /// of at least the given size.
    SC_HOOK_ALLOC,
    /// Dynamic memory free'er for sweetc.
    SC_HOOK_FREE,
    /// Dynamic memory re-allocator for sweetc.
    SC_HOOK_REALLOC,
};

/**
 * @typedef sc_alloc_t
 * @brief Prototype for sc's allocator hook. Set with the SC_HOOK_ALLOC value.
 */
typedef void *(*sc_alloc_t)(size_t);

/**
 * @typedef sc_free_t
 * @brief Prototype for sc's free function. Set with the SC_HOOK_FREE value.
 */
typedef void (*sc_free_t)(void *ptr);

/**
 * @typedef sc_realloc_t
 * @brief Prototype for sc's realloc function. Set with SC_HOOK_REALLOC value.
 */
typedef void *(*sc_realloc_t)(void *, size_t);

/**
 * @brief Sets a given hook for sweetc's backend. This function should only be called
 * before any other sweetc functions are called, otherwise undefined behavior can occure.
 * @param val An enum sc_hook_vals value to designate which hook is being replaced.
 * @param hook A pointer to the function that is going to replace the designated hook.
 * @return 0 on succes or -1 if val is out of range.
 */
int sc_set_hook(enum sc_hook_vals val, void *hook);

/**
 * @brief Wrapper around the set alloc hook for sweetc. Zero's out an allocation.
 * @param size The size of the allocation.
 * @return A pointer to a newly allocated block of data at least size bytes large. NULL if the
 * allocation fails.
 */
void *sc_zalloc(size_t size);

/**
 * @brief Wrapper around the set free hook for sweetc.
 * @param ptr Pointer to a previously allocated block.
 */
void sc_free(void *ptr);

/**
 * @brief Wrapper around the set realloc hook for sweetc.
 * @param ptr Pointer to an existing allocation.
 * @param size The new size required for the allocation.
 * @return Either a pointer to the new allocation or NULL if the allocation could not be performed.
 */
void *sc_realloc(void *ptr, size_t size);

#endif // _SC_HOOKS_H

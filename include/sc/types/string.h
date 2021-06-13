#ifndef _SC_TYPES_STRING_H
#define _SC_TYPES_STRING_H

#include <stddef.h>
#include <stdint.h>

struct sc_string;

/**
 * @brief The sc_string_t contains a string of bytes, typically in a C style string, however, the
 * sc_string_t can support raw binary data (containing NULL bytes). The sc_string_t type implements
 * the following traits:
 *      * Object trait
 *      * Full compare trait
 *          -- Only supports comparisons to other sc_string_t objects.
 *      * Hashable trait
 */
typedef struct sc_string sc_string_t;

/**
 * @brief Build an empty sc string object.
 * @return A valid pointer to a new sc string object or NULL if an error occurs. If NULL is returned
 * then the allocation function returned an error.
 */
sc_string_t *sc_string_build_empty(void);

/**
 * @brief Build a sc string object from a valid C style string.
 * @param str A null terminated string. Coppied, not free'ed.
 * @return A valid pointer to a new sc string object or NULL on error.
 * @see sc_string_build_empty
 */
sc_string_t *sc_string_build_str(const char *str);

/**
 * @brief Build a sc string from a raw data pointer with a length. Null bytes are supported if in
 * the buffer being passed in.
 * @param data Pointer to the begining of a data buffer. Ownership of the buffer remains with the
 * caller.
 * @param len The length of the buffer.
 * @return A valid pointer to a new sc string object or NULL on error.
 */
sc_string_t *sc_string_build_raw(const uint8_t *data, size_t len);

/**
 * @brief Build a sc string from a raw data pointer with a length. This function differs from
 * sc_string_build_raw by taking ownership of the buffer passed in. This buffer must be allocated
 * with the same allocation suit as is configured in sweetc's allocation hook.
 * @param data Pointer to the data buffer to be passed in. Ownership of the buffer is passed to
 * the new object. If the return value of this function is NULL, the caller should assume the data
 * still belongs to them and is responsible for managing the memory.
 * @param len The length of the buffer pointed to by data.
 * @return A valid pointer to a new sc string object or NULL on error.
 */
sc_string_t *sc_string_take_raw(uint8_t *data, size_t len);

/**
 * @brief Appends a C style string to the end of a sc string.
 * @param str A valid sc string object.
 * @param more A NULL-terminated C string to be appended to str. Ownership of the buffer remains
 * with the caller.
 * @return 0 on succes or -1 on failure.
 */
int sc_string_append_str(sc_string_t *str, const char *more);

/**
 * @brief Appends a raw byte string to the end of a sc string. The data can contain NULL bytes.
 * @param str A valid sc string object.
 * @param more A buffer to be appened to the string. Ownership of the buffer remains with the
 * caller.
 * @param len The length of the buffer.
 * @return 0 on success or -1 on failure.
 */
int sc_string_append_raw(sc_string_t *str, const uint8_t *more, size_t len);

/**
 * @brief Appends a sc string to another sc string.
 * @param str A valid sc string object. This object will be appened to.
 * @param more A valid sc stirng object.
 * @return 0 on success or -1 on failure.
 */
int sc_string_append_scstr(sc_string_t *str, const sc_string_t *more);

/**
 * @brief Compare a sc string to a C style string with a max len. No more then len bytes of rhs
 * will be read for comparison. If str's lenght is shorter then len then only str's length
 * bytes will be compared of str and rhs.
 * @param str A valid sc string pointer.
 * @param rhs A valid C stirng
 * @param len The maximum number of bytes to read of rhs.
 * @return <0 if str is less than rhs, 0 if they are equal and >0 if str is greater than rhs. Only
 * the first len bytes of rhs side are compared, upto the length of str.
 */
int sc_string_strncmp(sc_string_t *str, char *rhs, size_t len);

/**
 * @brief Returns the length of a sc string.
 * @param str A valid sc stirng pointer.
 * @return The length of the sc string.
 */
size_t sc_string_len(sc_string_t *str);

/**
 * @brief Returns a pointer to the string buffer used by an sc string. The bufer can be edited but
 * no more than sc_string_len bytes should be modified in the buffer. This function ensures the
 * buffer is NULL terminated before returning.
 * @param str A valid sc string pointer. This object must remain valid the entire time the
 * returned buffer is used.
 * @return A pointer to the internal memory buffer for the sc string. Do no free this value. This
 * value should only be used while the owning object is valid.
 */
char *sc_string_ptr(sc_string_t *str);

/**
 * @brief A raw compare function to use. This function accepts a buffer that can contain NULL bytes.
 * @param str A valid sc string pointer.
 * @param rhs A buffer to compare against.
 * @param len A limit of how many bytes of rhs to compare.
 * @return Returns a value similar to memcmp when comparing str's internal bufer and rhs.
 */
int sc_string_raw_cmp(sc_string_t *str, const uint8_t *rhs, size_t len);

#endif // _SC_TYPES_STRING_H

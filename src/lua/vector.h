#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>

typedef struct {
    void             *cursor;
    const void *const endpos;
    const size_t      step;
} lua_iterator_t;

/**
 * @brief Iterator for loop condition and element retrieval.
 */
bool lua_iterator_next(lua_iterator_t *it, void **w);

typedef struct {
    void  *data;
    size_t size;
    size_t count;
} lua_vector_storage_t;

/**
 * @brief Free a vector storage allocated by @p lua_bind_vector.
 */
void lua_free_vector_storage(lua_vector_storage_t *s);

/**
 * @brief Create an iterator using vector.
 */
lua_iterator_t lua_vector_iterator(const lua_vector_storage_t *s);

#endif
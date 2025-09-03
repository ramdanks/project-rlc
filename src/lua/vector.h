#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

#include "com/iterator.h"

typedef struct {
    void*  data;
    size_t step;
    size_t count;
} lua_vector_t;

/**
 * @brief Free a vector storage allocated by @p lua_bind_vector.
 */
inline void lua_free_vector(lua_vector_t* s)
{
    free(s->data);
    s->data  = NULL;
    s->step  = 0;
    s->count = 0;
}

/**
 * @brief Returns the vector size in bytes.
 */
inline size_t lua_vector_size(const lua_vector_t* s)
{
    return s->step * s->count;
}

/**
 * @brief Create an iterator using vector.
 */
inline iterator_t lua_vector_iterator(const lua_vector_t* s,
                                      iterator_range_t*   buf)
{
    buf->step   = s->step;
    buf->cursor = (char*) s->data;
    buf->endpos = (char*) s->data + lua_vector_size(s);
    return make_iterator_range(buf);
}

/**
 * @brief Access vector element specified by index.
 */
inline void* lua_vector_read(const lua_vector_t* s, size_t index)
{
    return (char*) s->data + (s->step * index);
}

#endif
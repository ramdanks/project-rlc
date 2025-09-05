#ifndef COM_VECTOR_H
#define COM_VECTOR_H

#include <stdlib.h>

#include "iterator.h"

typedef struct {
    void*  data;
    size_t step;
    size_t count;
} vector_t;

inline void init_vector(vector_t* obj, size_t step, size_t count);
inline void free_vector(vector_t* obj);

inline size_t     vector_size(const vector_t* self);
inline void*      vector_read(const vector_t* self, size_t index);
inline iterator_t vector_iterator(const vector_t* self, iterator_range_t* buf);

// Begin inline function definition.

inline void init_vector(vector_t* obj, size_t step, size_t count)
{
    obj->step  = step;
    obj->count = count;
    obj->data  = malloc(step * count);
}

inline void free_vector(vector_t* s)
{
    free(s->data);
    s->data  = NULL;
    s->step  = 0;
    s->count = 0;
}

inline size_t vector_size(const vector_t* s)
{
    return s->step * s->count;
}

inline void* vector_read(const vector_t* s, size_t index)
{
    return (char*) s->data + (s->step * index);
}

inline iterator_t vector_iterator(const vector_t* s, iterator_range_t* buf)
{
    buf->step   = s->step;
    buf->cursor = (char*) s->data;
    buf->endpos = (char*) s->data + vector_size(s);
    return make_iterator_range(buf);
}

// End inline function definition.

#endif // COM_VECTOR_H
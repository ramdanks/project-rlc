#include "vector.h"

#include <stdlib.h>

bool lua_iterator_next(lua_iterator_t* it, void** w)
{
    it->cursor = (char*) it->cursor + it->step;
    *w         = it->cursor;
    return it->cursor < it->endpos;
}

void lua_free_vector_storage(lua_vector_storage_t* s)
{
    free(s->data);
    s->data  = NULL;
    s->count = 0;
    s->size  = 0;
}

lua_iterator_t lua_vector_iterator(const lua_vector_storage_t* s)
{
    size_t step   = s->size / s->count;
    void*  cursor = (char*) s->data - step;
    void*  endpos = (char*) s->data + s->size;
    return (lua_iterator_t) {cursor, endpos, step};
}
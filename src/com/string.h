#ifndef COM_STRING_H
#define COM_STRING_H

#include <stdlib.h>

typedef const char* cstr_t;

typedef struct {
    char*  string;
    size_t len;
} string_t;

typedef struct {
    cstr_t string;
    size_t len;
} string_view_t;

inline void free_string(string_t* self);

// Begin inline function definition.

inline void free_string(string_t* self)
{
    free(self->string);
    self->string = NULL;
    self->len    = 0;
}

// End inline function definition.

#endif // COM_STRING_H
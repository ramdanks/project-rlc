#include "binding.h"

#include <lauxlib.h>
#include <lualib.h>
#include <stdlib.h>

int lua_bind_vector(lua_State* L, lua_bind_vector_t arg)
{
    const int index = -1;

    if (!lua_istable(L, index))
        return LUA_BIND_EINVAL;

    const size_t n = lua_objlen(L, index);
    const size_t s = n * arg.elem_size;

    arg.vector->data  = NULL;
    arg.vector->count = n;
    arg.vector->step  = arg.elem_size;

    if (n == 0)
        return LUA_BIND_OK;

    arg.vector->data = malloc(s);
    if (arg.vector->data == NULL)
        return LUA_BIND_MALLOC_FAIL;

    char* w    = (char*) (arg.vector->data);
    char* wend = w + s;

    for (int i = 1; w < wend; w += arg.elem_size, i++)
    {
        lua_rawgeti(L, index, i);
        arg.binding(L, w);
        lua_pop(L, 1);
    }

    return LUA_BIND_OK;
}

int lua_bind_class(lua_State* L, lua_bind_class_t arg)
{
    const int index = -1;

    if (!lua_istable(L, index))
        return LUA_BIND_EINVAL;

    for (size_t i = 0; i < arg.scalar.count; ++i)
    {
        const char* key = arg.scalar.fields[i].key;
        void*       buf = arg.scalar.fields[i].buf;
        lua_bind_fn bfn = arg.scalar.fields[i].binding;

        lua_getfield(L, -1, key);
        bfn(L, buf);
        lua_pop(L, 1);
    }

    for (size_t i = 0; i < arg.vector.count; ++i)
    {
        lua_bind_vector_field_t f = arg.vector.fields[i];

        lua_bind_vector_t arg;
        arg.binding   = f.binding;
        arg.elem_size = f.size;
        arg.vector    = f.buf;

        lua_getfield(L, -1, f.key);
        lua_bind_vector(L, arg);
        lua_pop(L, 1);
    }

    return LUA_BIND_OK;
}

int lua_bind_string(lua_State* L, const char** w)
{
    if (!lua_isstring(L, -1))
        return LUA_BIND_EINVAL;

    *w = lua_tostring(L, -1);
    return LUA_BIND_OK;
}

int lua_bind_number(lua_State* L, double* w)
{
    if (!lua_isnumber(L, -1))
        return LUA_BIND_EINVAL;

    *w = lua_tonumber(L, -1);
    return LUA_BIND_OK;
}

int lua_bind_integer(lua_State* L, int* w)
{
    if (!lua_isnumber(L, -1))
        return LUA_BIND_EINVAL;

    *w = lua_tointeger(L, -1);
    return LUA_BIND_OK;
}
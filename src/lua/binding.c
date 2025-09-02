#include "binding.h"

#include <stdlib.h>
#include <lualib.h>
#include <lauxlib.h>

int lua_bind_array(lua_State *L, lua_bind_array_t arg)
{
    const int index = -1;
    
    if (!lua_istable(L, index))
        return LUA_BIND_EINVAL;

    const size_t n  = lua_objlen(L, index);
    *arg.data       = NULL;
    *arg.data_count = n;
    *arg.data_size  = n * arg.elem_size;

    if (n == 0)
        return LUA_BIND_OK;

    *arg.data = malloc(*arg.data_size);
    if (*arg.data == NULL)
        return LUA_BIND_MALLOC_FAIL;
    
    char *w    = (char*)(*arg.data);
    char *wend = w + *arg.data_size;

    for (size_t i = 1; w < wend; w += arg.elem_size, i++) {
        lua_rawgeti(L, index, (int)i);
        arg.binding(L, w);
        lua_pop(L, 1);
    }

    return LUA_BIND_OK;
}

int lua_bind_class(lua_State *L, lua_bind_class_t arg)
{
    const int index = -1;
    
    if (!lua_istable(L, index))
        return LUA_BIND_EINVAL;

    lua_gettable(L, index);

    // bind class scalar
    for (size_t i = 0; i < arg.s_count; ++i)
    {
        const lua_bind_scalar_field_t f = arg.s_fields[i];
        lua_getfield(L, -1, f.key);
        f.binding(L, f.buf);
        lua_pop(L, 1);
    }

    // bind class array
    for (size_t i = 0; i < arg.a_count; ++i)
    {
        const lua_bind_array_field_t f = arg.a_fields[i];
        const lua_bind_array_t arg = {
            .binding    = f.binding,
            .elem_size  = f.size,
            .data       = &f.buf->data,
            .data_count = &f.buf->data_count,
            .data_size  = &f.buf->data_size,
        };
        lua_getfield(L, -1, f.key);
        lua_bind_array(L, arg);
        lua_pop(L, 1);
    }
    
    return LUA_BIND_OK;
}

int lua_bind_string(lua_State *L, const char **w)
{
    if (!lua_isstring(L, -1))
        return LUA_BIND_EINVAL;
    
    *w = lua_tostring(L, -1);
    return LUA_BIND_OK;
}

int lua_bind_integer(lua_State *L, int *w)
{
    if (!lua_isnumber(L, -1))
        return LUA_BIND_EINVAL;
    
    *w = lua_tointeger(L, -1);
    return LUA_BIND_OK;
}

int lua_bind_entity(lua_State *L, lua_entity_t *w)
{
    enum { a_count = 0, s_count = 2 };
    const lua_bind_class_t arg = {
        .a_count = a_count,
        .s_count = s_count,
        .a_fields = NULL,
        .s_fields = (lua_bind_scalar_field_t[s_count]){
            {"name" , &w->name , lua_bind_string },
            {"value", &w->value, lua_bind_integer},
        },
    };
    return lua_bind_class(L, arg);
}

int lua_bind_module_entity(lua_State *L, lua_module_entity_t *w)
{
    enum { a_count = 1, s_count = 0 };
    const lua_bind_class_t arg = {
        .a_count = a_count,
        .s_count = s_count,
        .a_fields = (lua_bind_array_field_t[a_count]){
            {"data", &w->data, lua_bind_entity, sizeof(lua_entity_t)},
        },
        .s_fields = NULL,
    };
    return lua_bind_class(L, arg);
}

void lua_free_module_entity(lua_module_entity_t *w)
{
    free(w->data);
    w->data       = NULL;
}

#ifndef EXT_LUA_H
#define EXT_LUA_H

#include <lua.h>

#include "com/string.h"

inline string_view_t ext_lua_tostring(lua_State* L, int idx)
{
    size_t len;
    cstr_t str = lua_tolstring(L, idx, &len);
    return (string_view_t) {str, len};
}

#endif // EXT_LUA_H
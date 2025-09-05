#include "binding.h"
#include "lua.h"

#define P_DESCRIPTOR const bind_descriptor_t* des

const bind_descriptor_t lua_str_bd = {(bind_fn) bind_str, sizeof(bind_str_t)};
const bind_descriptor_t lua_num_bd = {(bind_fn) bind_num, sizeof(bind_num_t)};
const bind_descriptor_t lua_int_bd = {(bind_fn) bind_int, sizeof(bind_int_t)};
const bind_descriptor_t lua_fun_bd = {(bind_fn) bind_fun, sizeof(bind_fun_t)};

void _bind_vec(lua_State* L, int idx, bind_vec_t* buf, P_DESCRIPTOR)
{
    const size_t step  = des->size;
    const size_t len   = lua_objlen(L, idx);
    const size_t bytes = len * step;

    buf->data  = NULL;
    buf->count = len;
    buf->step  = step;

    if (len == 0)
        return;

    buf->data = malloc(bytes);
    if (buf->data == NULL)
        return; // TODO: return error code.

    char* w    = (char*) (buf->data);
    char* wend = w + bytes;

    for (int i = 1; true; ++i, --idx)
    {
        lua_rawgeti(L, idx, i);
        des->bind(L, -1, w);

        w += step;
        if (w >= wend)
        {
            lua_pop(L, i);
            break;
        }
    }
}
#ifndef DBINDING_H
#define DBINDING_H

#include <lua.h>

#include "com/string.h"
#include "com/vector.h"
#include "ext/lua.h"

#define P_DESCRIPTOR const bind_descriptor_t* des

typedef string_view_t bind_str_t;
typedef lua_Number    bind_num_t;
typedef lua_Integer   bind_int_t;
typedef lua_CFunction bind_fun_t;
typedef void          bind_ext_t;
typedef vector_t      bind_vec_t;

typedef void (*bind_fn)(lua_State* L, int idx, bind_ext_t* w);

typedef struct {
    lua_State* L;
    int        idx;
    int        top;
} bind_t;

typedef struct {
    bind_fn bind;
    size_t  size;
} bind_descriptor_t;

extern const bind_descriptor_t lua_str_bd;
extern const bind_descriptor_t lua_num_bd;
extern const bind_descriptor_t lua_int_bd;
extern const bind_descriptor_t lua_fun_bd;

inline bind_t bind_begin(lua_State* L, int idx);
inline void   bind_reset(bind_t* self);

inline void bind_str(lua_State* L, int idx, bind_str_t* buf);
inline void bind_num(lua_State* L, int idx, bind_num_t* buf);
inline void bind_int(lua_State* L, int idx, bind_int_t* buf);
inline void bind_fun(lua_State* L, int idx, bind_fun_t* buf);
inline void bind_ext(lua_State* L, int idx, bind_ext_t* buf, P_DESCRIPTOR);
inline void bind_vec(lua_State* L, int idx, bind_vec_t* buf, P_DESCRIPTOR);

inline void bind_str_f(bind_t* agg, cstr_t key, bind_str_t* buf);
inline void bind_num_f(bind_t* agg, cstr_t key, bind_num_t* buf);
inline void bind_int_f(bind_t* agg, cstr_t key, bind_int_t* buf);
inline void bind_fun_f(bind_t* agg, cstr_t key, bind_fun_t* buf);
inline void bind_ext_f(bind_t* agg, cstr_t key, bind_ext_t* buf, P_DESCRIPTOR);
inline void bind_vec_f(bind_t* agg, cstr_t key, bind_vec_t* buf, P_DESCRIPTOR);

void _bind_vec(lua_State* L, int idx, bind_vec_t* buf, P_DESCRIPTOR);

// Begin inline function definition.

#define BINDF(L, pidx, key, buf, binding)                                      \
    lua_getfield(L, pidx, key);                                                \
    binding(L, -1, buf);                                                       \
    pidx--

inline bind_t bind_begin(lua_State* L, int idx)
{
    return (bind_t) {L, idx, -1};
}
inline void bind_reset(bind_t* self)
{
    lua_settop(self->L, self->top);
    self->top = -1;
}

inline void bind_str(lua_State* L, int idx, bind_str_t* buf)
{
    *buf = ext_lua_tostring(L, idx);
}
inline void bind_num(lua_State* L, int idx, bind_num_t* buf)
{
    *buf = lua_tonumber(L, idx);
}
inline void bind_int(lua_State* L, int idx, bind_int_t* buf)
{
    *buf = lua_tointeger(L, idx);
}
inline void bind_fun(lua_State* L, int idx, bind_fun_t* buf)
{
    *buf = lua_tocfunction(L, idx);
}
inline void bind_ext(lua_State* L, int idx, bind_ext_t* buf, P_DESCRIPTOR)
{
    des->bind(L, idx, buf);
}
inline void bind_vec(lua_State* L, int idx, bind_vec_t* buf, P_DESCRIPTOR)
{
    _bind_vec(L, idx, buf, des);
}

inline void bind_str_f(bind_t* agg, cstr_t key, bind_str_t* buf)
{
    BINDF(agg->L, agg->top, key, buf, bind_str);
}
inline void bind_num_f(bind_t* agg, cstr_t key, bind_num_t* buf)
{
    BINDF(agg->L, agg->top, key, buf, bind_num);
}
inline void bind_int_f(bind_t* agg, cstr_t key, bind_int_t* buf)
{
    BINDF(agg->L, agg->top, key, buf, bind_int);
}
inline void bind_fun_f(bind_t* agg, cstr_t key, bind_fun_t* buf)
{
    BINDF(agg->L, agg->top, key, buf, bind_fun);
}
inline void bind_ext_f(bind_t* agg, cstr_t key, bind_ext_t* buf, P_DESCRIPTOR)
{
    lua_getfield(agg->L, agg->top, key);
    bind_ext(agg->L, -1, buf, des);
    agg->top--;
}
inline void bind_vec_f(bind_t* agg, cstr_t key, bind_vec_t* buf, P_DESCRIPTOR)
{
    lua_getfield(agg->L, agg->top, key);
    bind_vec(agg->L, -1, buf, des);
    agg->top--;
}

// End inline function definition.

#undef P_DESCRIPTOR

#endif // DBINDING_H
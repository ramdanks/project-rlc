#ifndef BINDING_H
#define BINDING_H

#include <lua.h>

#include "vector.h"

#define LUA_BIND_OK          (int) 0  // Bind Success
#define LUA_BIND_EINVAL      (int) 1  // Error Invalid
#define LUA_BIND_MALLOC_FAIL (int) 2  // Error Invalid

#define lua_bind_fn_string  (lua_bind_fn) lua_bind_string
#define lua_bind_fn_number  (lua_bind_fn) lua_bind_number
#define lua_bind_fn_integer (lua_bind_fn) lua_bind_integer

/**
 * @brief Function type for binding a Lua value to a C object.
 *
 * The Lua value to bind is always expected at the top of the stack.
 * The implementation should write the result into @p w.
 *
 * @param L Lua state.
 * @param w Destination pointer for the bound value.
 *
 * @return LUA_BIND_OK on success, or an error code on failure.
 */
typedef int (*lua_bind_fn)(lua_State *L, void *w);

/**
 * @brief Arguments for binding a Lua table into a C array.
 */
typedef struct {
    lua_bind_fn binding;
    size_t      elem_size;
    void      **data;
    size_t     *size;
    size_t     *count;
} lua_bind_vector_t;

typedef struct {
    const char *key;
    void       *buf;
    lua_bind_fn binding;
} lua_bind_scalar_field_t;

typedef struct {
    const char           *key;
    lua_vector_storage_t *buf;
    lua_bind_fn           binding;
    size_t                size;
} lua_bind_vector_field_t;

typedef struct {
    const size_t                   count;
    const lua_bind_scalar_field_t *fields;
} lua_bind_scalar_field_arg_t;

typedef struct {
    const size_t                   count;
    const lua_bind_vector_field_t *fields;
} lua_bind_vector_field_arg_t;

typedef struct {
    lua_bind_scalar_field_arg_t scalar;
    lua_bind_vector_field_arg_t vector;
} lua_bind_class_t;

/**
 * @brief Bind a Lua homogenous table to a C struct array.
 *
 * Reads a Lua table and allocates a C array for binding.
 * The results are written into the fields of @p arg.
 *
 * @param L    Lua state.
 * @param arg  Binding argument struct with output fields.
 *
 * @return One of the following:
 * @retval LUA_BIND_OK          Success.
 * @retval LUA_BIND_EINVAL      Invalid Lua types.
 * @retval LUA_BIND_MALLOC_FAIL Memory allocation failure.
 */
int lua_bind_vector(lua_State *L, lua_bind_vector_t arg);

/**
 * @brief Bind a Lua table to a C scalar value or array.
 */
int lua_bind_class(lua_State *L, lua_bind_class_t arg);

/**
 * @brief Bind a Lua string to C string.
 */
int lua_bind_string(lua_State *L, const char **w);

/**
 * @brief Bind a Lua number to a C double.
 */
int lua_bind_number(lua_State *L, double *w);

/**
 * @brief Bind a Lua integer to a C int.
 */
int lua_bind_integer(lua_State *L, int *w);

#endif
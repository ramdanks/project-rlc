#ifndef BINDING_H
#define BINDING_H

#include <lua.h>

#define LUA_BIND_OK          (int)0 //Bind Success
#define LUA_BIND_EINVAL      (int)1 //Error Invalid
#define LUA_BIND_MALLOC_FAIL (int)2 //Error Invalid

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
typedef int (*lua_bind_fn)(lua_State *L, void* w);

/**
 * @brief Arguments for binding a Lua table into a C array.
 */
typedef struct
{
    /**
     * @brief Element binding callback (must not be NULL).
     */
    lua_bind_fn binding;

    /**
     * @brief Size of each element in bytes.
     */
    size_t elem_size;

    /**
     * @brief Output: allocated array of bound elements (must not be NULL).
     */
    void **data;

    /**
     * @brief Output: total size of @p data in bytes (must not be NULL).
     */
    size_t *data_size;

    /**
     * @brief Output: number of elements in @p data (must not be NULL).
     */
    size_t *data_count;
} lua_bind_array_t;

typedef struct
{
    void*  data;
    size_t data_size;
    size_t data_count;
} lua_bind_array_storage_t;

typedef struct
{
    const char* key;
    void*       buf;
    lua_bind_fn binding;
} lua_bind_scalar_field_t;

typedef struct
{
    const char*               key;
    lua_bind_array_storage_t* buf;
    lua_bind_fn               binding;
    size_t                    size;
} lua_bind_array_field_t;

typedef struct
{
    size_t s_count;
    size_t a_count;
    lua_bind_scalar_field_t *s_fields;
    lua_bind_array_field_t  *a_fields;
} lua_bind_class_t;

/**
 * @brief Arguments for binding a Lua table into a C array.
 */
typedef struct
{
    const char *name;
    int value;
} lua_entity_t;

/**
 * @brief Arguments for binding a Lua table into a C array.
 */
typedef struct
{
    lua_bind_array_storage_t data;
} lua_module_entity_t;

/**
 * @brief Bind a Lua table to a C struct array.
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
int lua_bind_array(lua_State *L, lua_bind_array_t arg);

int lua_bind_class(lua_State *L, lua_bind_class_t arg);

int lua_bind_string(lua_State *L, const char** w);

int lua_bind_integer(lua_State *L, int* w);

int lua_bind_entity(lua_State *L, lua_entity_t *w);

int lua_bind_module_entity(lua_State *L, lua_module_entity_t *w);

void lua_free_array_storage(lua_bind_array_storage_t* s);

void lua_free_module_entity(lua_module_entity_t *w);

#endif
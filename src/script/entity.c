#include "entity.h"

#include "lua/truncate.h"

int script_bind_entity(lua_State* L, script_entity_t* w)
{
    enum { scalar_count = 2, vector_count = 0 };
    const scalar_field_t scalar_fields[scalar_count] = {
        {"name",  &w->name,  lua_bind_fn_string },
        {"value", &w->value, lua_bind_fn_integer},
    };
    const scalar_field_arg_t scalar = {scalar_count, scalar_fields};
    const vector_field_arg_t vector = {vector_count, NULL};
    return lua_bind_class(L, (class_t) {scalar, vector});
}

int script_bind_module_entity(lua_State* L, script_module_entity_t* w)
{
    enum { scalar_count = 1, vector_count = 1 };
    const scalar_field_t scalar_fields[scalar_count] = {
        {"name", &w->name, lua_bind_fn_string},
    };
    const vector_field_t vector_fields[vector_count] = {
        {"data", &w->data, script_bind_fn_entity, sizeof(script_entity_t)},
    };
    const scalar_field_arg_t scalar = {scalar_count, scalar_fields};
    const vector_field_arg_t vector = {vector_count, vector_fields};
    return lua_bind_class(L, (class_t) {scalar, vector});
}

void script_free_module_entity(script_module_entity_t* w)
{
    lua_free_vector_storage(&w->data);
}
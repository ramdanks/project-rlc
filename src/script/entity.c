#include "entity.h"

#include "truncate.h"

#define bind_entity (lua_bind_fn) script_bind_entity

int script_bind_entity(lua_State* L, script_entity_t* w)
{
    enum { scalar_count = 2, vector_count = 0 };
    const bind_scalar_field_t scalar_fields[scalar_count] = {
        {"name",  &w->name,  bind_string },
        {"value", &w->value, bind_integer},
    };
    const bind_class_scalar_t scalar = {scalar_count, scalar_fields};
    const bind_class_vector_t vector = {vector_count, NULL};
    return lua_bind_class(L, (bind_class_t) {scalar, vector});
}

int script_bind_module_entity(lua_State* L, script_module_entity_t* w)
{
    enum { scalar_count = 1, vector_count = 1 };
    const bind_scalar_field_t scalar_fields[scalar_count] = {
        {"name", &w->name, bind_string},
    };
    const bind_vector_field_t vector_fields[vector_count] = {
        {"data", &w->data, bind_entity, sizeof(script_entity_t)},
    };
    const bind_class_scalar_t scalar = {scalar_count, scalar_fields};
    const bind_class_vector_t vector = {vector_count, vector_fields};
    return lua_bind_class(L, (bind_class_t) {scalar, vector});
}

void script_free_module_entity(script_module_entity_t* w)
{
    lua_free_vector(&w->data);
}
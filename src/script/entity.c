#include "entity.h"
#include "binding.h"
#include "lua.h"

const bind_descriptor_t entity_bd = {
    .bind = script_bind_entity,
    .size = sizeof(script_entity_t),
};

void script_bind_entity(lua_State* L, int idx, void* w)
{
    script_entity_t* self = w;

    bind_t bind = bind_begin(L, idx);
    bind_str_f(&bind, "name", &self->name);
    bind_int_f(&bind, "value", &self->value);
    bind_reset(&bind);
}

void script_bind_module_entity(lua_State* L, int idx, void* w)
{
    script_module_entity_t* self = w;

    bind_t bind = bind_begin(L, idx);
    bind_str_f(&bind, "name", &self->name);
    bind_vec_f(&bind, "data", &self->data, &entity_bd);
    bind_reset(&bind);
}

void script_free_module_entity(script_module_entity_t* w)
{
    free_vector(&w->data);
}

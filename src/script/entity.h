#ifndef ENTITY_H
#define ENTITY_H

#include <lua.h>

#include "binding.h"

typedef struct {
    bind_str_t name;
    bind_int_t value;
} script_entity_t;

typedef struct {
    bind_str_t name;
    vector_t   data; // script_entity_t
} script_module_entity_t;

extern const bind_descriptor_t entity_bd;

void script_bind_entity(lua_State* L, int idx, void* w);

void script_bind_module_entity(lua_State* L, int idx, void* w);

void script_free_module_entity(script_module_entity_t* w);

#endif
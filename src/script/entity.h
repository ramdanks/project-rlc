#ifndef ENTITY_H
#define ENTITY_H

#include <lua.h>

#include "lua/vector.h"

#define script_bind_fn_entity (lua_bind_fn) script_bind_entity

typedef struct {
    const char *name;
    int         value;
} script_entity_t;

typedef struct {
    const char          *name;
    lua_vector_storage_t data;  // script_entity_t
} script_module_entity_t;

int script_bind_entity(lua_State *L, script_entity_t *w);

int script_bind_module_entity(lua_State *L, script_module_entity_t *w);

void script_free_module_entity(script_module_entity_t *w);

#endif
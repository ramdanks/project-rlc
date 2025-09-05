#include "script.h"

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <stdio.h>

#include "content.h"
#include "script/entity.h"

int script_new_state(script_state_t* s)
{
    s->L = luaL_newstate();
    if (s->L == NULL)
        return 1;

    luaL_openlibs(s->L);
    return 0;
}

void script_load_entity(script_state_t* s)
{
    if (luaL_dofile(s->L, SCRIPT_ENTITY_PATH))
    {
        const char* msg = lua_tostring(s->L, -1);
        fprintf(stderr, "Failed to load entity: %s\n", msg);
        return;
    }

    script_module_entity_t m;
    script_bind_module_entity(s->L, -1, &m);
    script_free_module_entity(&m);
}

void script_free_state(script_state_t* s)
{
    lua_close(s->L);
    s->L = NULL;
}

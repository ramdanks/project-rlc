#include "script.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "content.h"
#include "lua/binding.h"

int script_new_state(script_state_t *s)
{
    s->L = luaL_newstate();
    if (s->L == NULL)
        return 1;

    luaL_openlibs(s->L);
    return 0;
}

void script_load_entity(script_state_t *s)
{
    if (luaL_dofile(s->L, SCRIPT_ENTITY_PATH))
    {
        const char *msg = lua_tostring(s->L, -1);
        fprintf(stderr, "Failed to load entity: %s\n", msg);
        return;
    }

    lua_module_entity_t e;
    lua_bind_module_entity(s->L, &e);
    lua_free_module_entity(&e);
}

void script_free_state(script_state_t *s)
{
    lua_close(s->L);
    s->L = NULL;
}

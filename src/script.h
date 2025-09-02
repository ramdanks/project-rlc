#ifndef SCRIPT_H
#define SCRIPT_H

#include <lua.h>

typedef struct 
{
    lua_State *L;
} script_state_t;

int script_new_state(script_state_t* s);

void script_load_entity(script_state_t* s);

void script_free_state(script_state_t* s);

#endif
#include <SWI-Prolog.h>

#include "lua.h"

int unify_lua_State(term_t t);
int get_lua_State(term_t t, lua_State **L);

#include "prolog.h"
#include "lua.h"

typedef struct lua
{ atom_t a;
  lua_State *L;
  IOSTREAM *i;
  IOSTREAM *o;
  IOSTREAM *e;
} lua;

int unify_lua(term_t t, lua *lua);
int get_lua(term_t t, lua **lua);
int get_lua_State(term_t t, lua_State **L);

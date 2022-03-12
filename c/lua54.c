#include "lua_prolog.h"
#include "lua_blob.h"
#include "lua.h"

foreign_t
lua_open_1(term_t Lua)
{ lua *lua;
  if (!get_lua(Lua, &lua)) PL_fail;
  lua->L = lua_newstate(l_alloc, lua);
  if (lua->L == NULL) return PL_resource_error("memory");
  PL_succeed;
}

foreign_t
lua_newstate_1(term_t Lua)
{ lua *lua = PL_malloc(sizeof(*lua));
  if (lua == NULL) return PL_resource_error("memory");
  memset(lua, 0, sizeof(*lua));
  return unify_lua(Lua, lua) && lua_open_1(Lua);
}

foreign_t
lua_close_1(term_t Lua)
{ lua *lua;
  if (!get_lua(Lua, &lua) || lua->L == NULL) PL_fail;
  lua_close(lua->L);
  lua->L = NULL;
  PL_succeed;
}

foreign_t
lua_absindex_3(term_t Lua, term_t Index, term_t Abs)
{ lua_State *L;
  int index;
  return get_lua_State(Lua, &L)
      && PL_get_integer_ex(Index, &index)
      && PL_unify_integer(Abs, lua_absindex(L, index));
}

foreign_t
lua_gettop_2(term_t Lua, term_t Top)
{ lua_State *L;
  if (!get_lua_State(Lua, &L)) PL_fail;
  return PL_unify_integer(Top, lua_gettop(L));
}

foreign_t
lua_settop_2(term_t Lua, term_t Top)
{ lua_State *L;
  int top;
  if (!get_lua_State(Lua, &L) || !PL_get_integer_ex(Top, &top)) PL_fail;
  lua_settop(L, top);
  PL_succeed;
}

install_t
install_lua54()
{ PL_register_foreign("lua_open", 1, lua_open_1, 0);
  PL_register_foreign("lua_newstate", 1, lua_newstate_1, 0);
  PL_register_foreign("lua_close", 1, lua_close_1, 0);
  PL_register_foreign("lua_absindex", 3, lua_absindex_3, 0);
  PL_register_foreign("lua_gettop", 2, lua_gettop_2, 0);
  PL_register_foreign("lua_settop", 2, lua_settop_2, 0);
}

install_t
uninstall_lua54()
{ ;
}

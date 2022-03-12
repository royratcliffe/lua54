#include "lua_prolog.h"
#include "lua_blob.h"
#include "lua.h"

foreign_t
lua_open_1(term_t L)
{ lua *lua;
  if (!get_lua(L, &lua)) PL_fail;
  lua->L = lua_newstate(l_alloc, NULL);
  if (lua->L == NULL) return PL_resource_error("memory");
  PL_succeed;
}

foreign_t
lua_close_1(term_t L)
{ lua *lua;
  if (!get_lua(L, &lua) || lua->L == NULL) PL_fail;
  lua_close(lua->L);
  lua->L = NULL;
  PL_succeed;
}

foreign_t
lua_newstate_1(term_t L)
{ lua *lua = PL_malloc(sizeof(*lua));
  if (lua == NULL) return PL_resource_error("memory");
  memset(lua, 0, sizeof(*lua));
  return unify_lua(L, lua) && lua_open_1(L);
}

install_t
install_lua54()
{ PL_register_foreign("lua_newstate", 1, lua_newstate_1, 0);
  PL_register_foreign("lua_open", 1, lua_open_1, 0);
  PL_register_foreign("lua_close", 1, lua_close_1, 0);
}

install_t
uninstall_lua54()
{ ;
}

#include "lua_prolog.h"
#include "lua_blob.h"
#include "lua.h"

/*
 * Include memory.h for memset on macOS.
 */
#include <memory.h>

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
  return get_lua_State(Lua, &L) && PL_unify_integer(Top, lua_gettop(L));
}

foreign_t
lua_settop_2(term_t Lua, term_t Top)
{ lua_State *L;
  int top;
  if (!get_lua_State(Lua, &L) || !PL_get_integer_ex(Top, &top)) PL_fail;
  lua_settop(L, top);
  PL_succeed;
}

/*
 * Lua error to Prolog error generically. Converts a Lua status code to a Prolog error and `FALSE` return value, assuming that the Prolog error function answers `FALSE`.
 *
 * `LUA_ERRERR` occurs when an error occurs while handling an error: an error in error handling.
 */
int
lua_err(int status)
{ switch (status)
  { case 0:
      break;
    case LUA_ERRRUN:
      return PL_syntax_error("run", NULL);
    case LUA_ERRSYNTAX:
      return PL_syntax_error("syntax", NULL);
    case LUA_ERRMEM:
      return PL_resource_error("mem");
    case LUA_ERRERR:
      return PL_resource_error("err");
    case LUA_ERRFILE:
      return PL_resource_error("file");
  }
  PL_succeed;
}

foreign_t
luaL_dostring_2(term_t Lua, term_t String)
{ lua_State *L;
  char *string;
  if (!get_lua_State(Lua, &L) ||
      !PL_get_chars(String, &string, CVT_ALL|CVT_EXCEPTION|REP_UTF8)) PL_fail;
  return lua_err(luaL_dostring(L, string));
}

foreign_t
luaL_openlibs_1(term_t Lua)
{ lua_State *L;
  if (!get_lua_State(Lua, &L)) PL_fail;
  luaL_openlibs(L);
  PL_succeed;
}

install_t
install_lua54()
{ /*
   * core
   */
  PL_register_foreign("lua_open", 1, lua_open_1, 0);
  PL_register_foreign("lua_newstate", 1, lua_newstate_1, 0);
  PL_register_foreign("lua_close", 1, lua_close_1, 0);

  /*
   * stack manipulation
   */
  PL_register_foreign("lua_absindex", 3, lua_absindex_3, 0);
  PL_register_foreign("lua_gettop", 2, lua_gettop_2, 0);
  PL_register_foreign("lua_settop", 2, lua_settop_2, 0);

  /*
   * auxilliary functions & useful macros
   *
   * Predicate luaL_openlibs/1 appears near the end. It opens all the Lua standard libraries.
   */
  PL_register_foreign("luaL_dostring", 2, luaL_dostring_2, 0);
  PL_register_foreign("luaL_openlibs", 1, luaL_openlibs_1, 0);
}

install_t
uninstall_lua54()
{ ;
}

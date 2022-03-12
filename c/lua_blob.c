#include "lua_blob.h"
#include "blob.h"
#include "lua.h"

int
release_lua(atom_t a)
{ lua *lua = PL_blob_data(a, NULL, NULL);
  if (lua->L)
  { lua_close(lua->L);
    lua->L = NULL;
  }
  PL_free(lua);
  PL_succeed;
}

void
acquire_lua(atom_t a)
{ lua *lua = PL_blob_data(a, NULL, NULL);
  lua->a = a;
}

PL_blob_t lua_blob =
{ .magic = PL_BLOB_MAGIC,
  .flags = PL_BLOB_NOCOPY,
  .name = "lua",
  .release = release_lua,
  .write = write_blob,
  .acquire = acquire_lua
};

int
unify_lua(term_t t, lua *lua)
{ if (lua->a) return PL_unify_atom(t, lua->a);
  else return PL_unify_blob(t, lua, sizeof(*lua), &lua_blob);
}

/*
 * Gets a Lua state from an arbitrary term. Fails with type error if the
 * term is not a blob and blob is not a Lua blob. Uses the blob type
 * name as the expected type in case of error.
 */
int
get_lua(term_t t, lua **lua)
{ void *data;
  if (!get_blob_ex(t, &lua_blob, &data)) PL_fail;
  *lua = data;
  PL_succeed;
}

/*
 * Gets the underlying Lua state from a given term's Lua blob. Fails if
 * the term does not describe a Lua blob, or if the Lua blob does not
 * bind an open Lua state. The latter occurs after applying lua_close/1
 * to a Lua blob.
 */
int
get_lua_State(term_t t, lua_State **L)
{ lua *lua;
  if (!get_lua(t, &lua) || lua->L == NULL) PL_fail;
  *L = lua->L;
  PL_succeed;
}

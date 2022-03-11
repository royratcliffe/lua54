#include <SWI-Prolog.h>

#include "lua.h"
#include "blob.h"

int
lua_State_release(atom_t a)
{ lua_State *L = PL_blob_data(a, NULL, NULL);
  lua_close(L);
  PL_succeed;
}

PL_blob_t lua_State_blob =
{ .magic = PL_BLOB_MAGIC,
  .flags = PL_BLOB_UNIQUE|PL_BLOB_NOCOPY,
  .name = "lua_State",
  .release = lua_State_release,
  .write = blob_write
};

void *
l_alloc(void *unused1, void *mem, size_t unused3, size_t size)
{ if (size == 0)
  { PL_free(mem);
    return NULL;
  }
  return PL_realloc(mem, size);
}

int
unify_lua_State(term_t t)
{ lua_State *L = lua_newstate(l_alloc, NULL);
  return PL_unify_blob(t, L, sizeof(L), &lua_State_blob);
}

/*
 * Gets a Lua state from an arbitrary term. Fails with type error if the
 * term is not a blob and blob is not a Lua state. Uses the blob type
 * name as the expected type in case of error.
 */
int
get_lua_State(term_t t, lua_State **L)
{ void *data;
  if (!get_blob_ex(t, &lua_State_blob, &data)) PL_fail;
  *L = data;
  PL_succeed;
}

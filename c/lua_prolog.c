#include "lua_prolog.h"

void *
l_alloc(void *mem0, void *mem, size_t size0, size_t size)
{ if (size == 0)
  { PL_free(mem);
    return NULL;
  }
  return PL_realloc(mem, size);
}

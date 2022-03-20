#include "lua_prolog.h"
#include "lua.h"

void *
l_alloc(void *mem0, void *mem, size_t size0, size_t size)
{ if (size == 0)
  { PL_free(mem);
    return NULL;
  }
  return PL_realloc(mem, size);
}

/*
 * Lua error to Prolog error generically. Converts a Lua status code to
 * a Prolog error and `FALSE` return value, assuming that the Prolog
 * error function answers `FALSE`.
 *
 * `LUA_ERRERR` occurs when an error occurs while handling an error: an
 * error in error handling.
 */
int
l_err(int status)
{ switch (status)
  { case 0:
      break;
    case LUA_ERRRUN:
      return PL_syntax_error("run", NULL);
    case LUA_ERRSYNTAX:
      return PL_syntax_error("syntax", NULL);
    case LUA_ERRMEM:
      return PL_resource_error("memory");
    case LUA_ERRERR:
      return PL_resource_error("err");
    case LUA_ERRFILE:
      return PL_resource_error("file");
    default:
    { char buf[BUFSIZ];
      Ssprintf(buf, "error(%d)", status);
      return PL_resource_error(buf);
    }
  }
  PL_succeed;
}

#include "lua_prolog.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

void *
l_alloc(void *mem0, void *mem, size_t size0, size_t size)
{ if (size == 0)
  { PL_free(mem);
    return NULL;
  }
  return PL_realloc(mem, size);
}

struct io_stream *l_open_pipe(const char *cmd, const char *how)
{ return Sopen_pipe(cmd, how);
}

struct io_stream *l_open_file(const char *path, const char *how)
{ return Sopen_file(path, how);
}

int l_close(struct io_stream *s)
{ return Sclose(s);
}

int l_lock(struct io_stream *s)
{ return Slock(s);
}

int l_unlock(struct io_stream *s)
{ return Sunlock(s);
}

int l_seek64(struct io_stream *s, off64_t off, int whence)
{ return Sseek64(s, off, whence);
}

off64_t l_tell64(struct io_stream *s)
{ return Stell64(s);
}

int l_fgetc(struct io_stream *s)
{ return Sfgetc(s);
}

int l_ungetc(int c, struct io_stream *s)
{ return Sungetc(c, s);
}

size_t l_fread(void *data, size_t size, size_t len, struct io_stream *s)
{ return Sfread(data, size, len, s);
}

/*
 * Writes to a given stream accounting for the stream's encoding. How does a Prolog stream handle UTF-8? Lua uses only UTF-8.
 *
 * Returns the number of successfully written elements.
 */
size_t l_fwrite(const void *data, size_t size, size_t len, struct io_stream *s)
{ return Sfwrite(data, size, len, s);
}

int l_fprintf(struct io_stream *s, const char *f, ...)
{ va_list a;
  va_start(a, f);
  return Svfprintf(s, f, a);
}

int l_flush(struct io_stream *s)
{ return Sflush(s);
}

int l_ferror(struct io_stream *s)
{ return Sferror(s);
}

void l_clearerr(struct io_stream *s)
{ Sclearerr(s);
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

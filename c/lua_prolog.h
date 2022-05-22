#include "prolog.h"

void *l_alloc(void *mem0, void *mem, size_t size0, size_t size);
struct io_stream *l_open_pipe(const char *cmd, const char *how);
struct io_stream *l_open_file(const char *path, const char *how);
int l_close(struct io_stream *s);
int l_lock(struct io_stream *s);
int l_unlock(struct io_stream *s);
int l_seek64(struct io_stream *s, off64_t off, int whence);
off64_t l_tell64(struct io_stream *s);
int l_fgetc(struct io_stream *s);
int l_ungetc(int c, struct io_stream *s);
size_t l_fread(void *data, size_t size, size_t len, struct io_stream *s);
size_t l_fwrite(const void *data, size_t size, size_t len, struct io_stream *s);
int l_fprintf(struct io_stream *s, const char *f, ...);
int l_flush(struct io_stream *s);
int l_ferror(struct io_stream *s);
void l_clearerr(struct io_stream *s);
int l_err(int status);

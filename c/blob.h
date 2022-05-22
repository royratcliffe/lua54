#include "prolog.h"

int get_blob_ex(term_t t, PL_blob_t *expected, void **data);
int write_blob(IOSTREAM *s, atom_t a, int flags);

#include "blob.h"

/*
 * Gets blob data from term, raising type error if not a blob *or* blob
 * does not have the expected type. Uses the expected blob name as the
 * type error's expectation.
 */
int
get_blob_ex(term_t t, PL_blob_t *expected, void **data)
{ PL_blob_t *blob;
  if (!PL_get_blob(t, data, NULL, &blob) || blob != expected)
    return PL_type_error(expected->name, t);
  PL_succeed;
}

/*
 * Generically writes a blob's description to the given stream. Uses the
 * blob name as type name along with the hexadecimal memory address of
 * the blob instance.
 */
int
blob_write(IOSTREAM *s, atom_t a, int flags)
{ PL_blob_t *blob;
  void *data = PL_blob_data(a, NULL, &blob);
  Sfprintf(s, "<%s>(%p)", blob->name, data);
  PL_succeed;
}

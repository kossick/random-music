#include "../inc/album.h"
#include <stdlib.h>
#include <string.h>

struct Album *buildAlbum(const char *artist, const char *title) {
  /* Creates an `Album` object based on the given artist name title
   *
   * @param artist name
   * @param title of album
   * @return `Album` object
   */
  struct Album *ap = malloc(sizeof(*ap));
  ap->artist = strdup(artist);
  ap->title = strdup(title);
  return ap;
}

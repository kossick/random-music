#ifndef ALBUM_H
#define ALBUM_H

int newAlbum();
void loop(char *path);
struct Album *buildAlbum(const char *artist, const char *title);

struct Album {
  char *artist;
  char *title;
};

#endif

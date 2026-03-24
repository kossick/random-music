#include "album.h"
#include <dirent.h>

#define MUSIC_DIR "/Music"
#define NOTVALID                                                               \
  "Music", "Movies", "Compilations", "Downloads", "iTunes", "TV Shows",        \
      "Unknown Artist", "Various Artists",                                     \
      "Automatically Add to iTunes.localized",                                 \
      "Automatically Add to Music.localized", ".", ".."
#define MAXNAMELENGTH 100

struct Album *chooseMusic(const char *path);

#include "inc/album.h"
#include "inc/dirtree.h"
#include <ctype.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(void) {
  // Use userID to get user's home directory
  uid_t uid = getuid();
  struct passwd *pwd = getpwuid(uid);
  // Append music directory
  char musicPath[MAXNAMLEN];
  snprintf(musicPath, MAXNAMLEN, "%s/%s", pwd->pw_dir, MUSIC_DIR);

  // Get randomness seed
  time_t t;
  srand(time(&t));

  loop(musicPath);

  puts("Okay, maybe next time...");
  return 0;
}

void loop(char *path) {
  /* Handles ability to perform the main functionality repeatedly
   *
   * @param initial directory to find music files in
   */
  int repeat;

  do {
    struct Album *album = chooseMusic(path);

    printf("Why not \"%s\" by %s?\n", album->title, album->artist);
    free(album);
    album = NULL;
    printf("Would you like to receive a new album [y/N]? ");
    repeat = getchar();
    if (repeat == '\n' || repeat == EOF) {
      break;
    }
    getchar();
  } while (tolower(repeat) == 'y');
}

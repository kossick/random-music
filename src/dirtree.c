#include "../inc/dirtree.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int inInvalidChoice(const char *dirName) {
  /* Checks whether a given directory name matches the pattern of a band, an
   * album or neither. A band or album name is assumed if a directory does not
   * conform to any of the default directories in the macOS `Music` folder, nor
   * matches `.` or `..`.
   *
   * @param name of the current directory
   * @return 0 (=invalid) or 1 (=valid)
   */
  char *notValid[] = {NOTVALID};
  // Hack to get length of array
  size_t arrayLength = (int)sizeof(notValid) / (int)sizeof(notValid[0]);
  // Check against the elements of `NOTVALID`
  for (int i = 0; i < arrayLength; i++) {
    if (strcmp(dirName, notValid[i]) == 0) {
      return 0; // Not a band or album name
    }
  }
  return 1; // Not matching given patterns, assumed to be band name
}

int countSubDir(DIR *dp) {
  struct dirent *entry;
  int totalDirs = 0;
  // Cycle through elements of directory
  while ((entry = readdir(dp))) {
    totalDirs++;
  }
  return totalDirs;
}

char *chooseElement(const char *basePath) {
  /* Hack way to assess available bands or albums and return one at random.
   * Cycles through all subdirectories within the given directory, selects a
   * random one if it is suitable (not a default folder within `Music/` in
   * macOS, say) and returns the name.
   *
   * @param path of the directory to scan through
   * @return randomly selected element (band name or album)
   */

  DIR *dp;
  dp = opendir(basePath);

  if (dp == NULL) {
    fprintf(stderr, "Error: unable to find path %s - %s\n", basePath,
            strerror(errno));
    return NULL;
  }

  struct dirent *entry;
  int totalElements = countSubDir(dp);

  char *elementName =
      malloc(MAXNAMELENGTH * sizeof(char)); // arbitrary size allocation
  if (elementName == NULL) {
    return NULL;
  }
  strcpy(elementName, "");

  char *tmp =
      malloc(MAXNAMELENGTH * sizeof(char)); // used for local copy of names
  if (tmp == NULL) {
    return NULL;
  }

  do {
    int chosenElement = rand() % totalElements;
    int n = 0;
    rewinddir(dp);
    while ((entry = readdir(dp)) && n <= chosenElement) {
      if (entry->d_type == DT_DIR) {
        strcpy(tmp, entry->d_name);
      }
      n++;
    }
    if (inInvalidChoice(tmp) == 1) {
      strcat(elementName, tmp);
    }
  } while (strcmp(elementName, "") == 0);

  free(tmp);
  tmp = NULL;
  closedir(dp);
  return elementName;
}

struct Album *chooseMusic(const char *basePath) {
  /* Selects a band and album by choosing a band at random, followed by randomly
   * selecting an album.
   *
   * @param the path of the music directory
   * @return selected album with band name and title
   */

  // Select a band
  char *bandName = chooseElement(basePath);

  // Build path to band directory
  char *bandPath = malloc(MAXNAMELENGTH * sizeof(char));
  strcpy(bandPath, basePath);
  strcat(bandPath, "/");
  strcat(bandPath, bandName);

  // Select an album
  char *albumName = chooseElement(bandPath);

  // Build album
  struct Album *album = buildAlbum(bandName, albumName);

  // Free memory
  free(bandPath);
  bandPath = NULL;
  free(bandName);
  bandName = NULL;
  free(albumName);
  albumName = NULL;

  return album;
}

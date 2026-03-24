# Random Music Selector

This repo is for a very simple CLI-based programme that randomly selects an artist and band from a user's `~/Music/` directory.
This is a project intended to get me back into programming in C, and also to familiarise myself with best practices, project structuring and using makefiles.

## Building the project

The project is built with `Make` and `CMake`.
In order to build and run it (on a Unix-like system), within the terminal run the following commands from the root directory for the repo:

```bash
$ cmake -B build       # builds the `build` directory containing the makefile
$ cmake --build build  # populates the directory
$ cd build
$ make                 # build the executable
```

After which the executable can be run with 

```bash
$ ./random_music
```

## TO-DO

- [ ] Increase securities
- [ ] Allow prompting for changing scanned directory
- [ ] Implement testing
- [ ] Investigate porting to Windows
- [ ] Investigate feasibility of adding playback with default music player

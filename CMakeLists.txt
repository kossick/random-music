cmake_minimum_required(VERSION 3.23)

project(random_music)

add_executable(random_music)

target_sources(random_music
  PRIVATE
  main.c
  src/album.c
  src/dirtree.c
)

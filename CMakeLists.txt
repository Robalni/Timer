cmake_minimum_required(VERSION 2.6)
project(timer C)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${timer_SOURCE_DIR}/cmake")
find_package(SDL2)
find_package(SDL2_ttf)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -Wall -Wextra -g")
set(SOURCE_FILES
  src/main.c
#  src/text.c src/text.h
  )
add_executable(timer ${SOURCE_FILES})
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(timer ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY})

cmake_minimum_required(VERSION 2.6)
project(timer CXX C)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${timer_SOURCE_DIR}/cmake")
find_package(SDL2)
find_package(SDL2_ttf)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -g")
set(SOURCE_FILES
  src/main.cpp
  src/text.cpp src/text.hpp
  src/timer.cpp src/timer.hpp
  src/app.cpp src/app.hpp
  src/coord.hpp
  src/input.cpp src/input.hpp
  src/object.cpp src/object.hpp
  )
add_executable(timer ${SOURCE_FILES})
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(timer ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY})

cmake_minimum_required(VERSION 3.0)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

project(Terroir)

set(CMAKE_CXX_FLAGS "-Wall")
# append flag, best practice, suggested, don't lose previously defined flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0")

set(CMAKE_CXX_STANDARD 20)

set(LibraryName Terroir)

add_subdirectory(Terroir)
add_subdirectory(Sandbox)

# YOU NEED TO COMMENT THIS OUT
# add_subdirectory(opengltest)

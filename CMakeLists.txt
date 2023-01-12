cmake_minimum_required(VERSION 3.0)
project(Terroir)

set(CMAKE_CXX_FLAGS "-Wall")
# append flag, best practice, suggested, don't lose previously defined flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

set(CMAKE_CXX_STANDARD 17)

set(LibraryName Terroir)

add_subdirectory(Terroir)
add_subdirectory(Sandbox)

# YOU NEED TO COMMENT THIS OUT
add_subdirectory(opengltest)

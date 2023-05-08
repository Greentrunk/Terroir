cmake_minimum_required(VERSION 3.23.2)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(Terroir CXX C)

if (WIN32)
    set(CMAKE_CXX_FLAGS "-W4")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")

    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -WX")
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Debug /Zi")
    endif ()
endif ()

if (UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "-Wall")

    # append flag, best practice, suggested, don't lose previously defined flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
    set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0")
endif (UNIX AND NOT APPLE)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Terroir)
add_subdirectory(Sandbox)

# Tracy profiler
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/tracy)


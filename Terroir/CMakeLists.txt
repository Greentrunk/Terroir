# Set output path to lib
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# Locate packages installed by vcpkg
find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# Header only libraries
find_path(STB_INCLUDE_DIRS "stb_image.h")


# OpenGL per platform
if (WIN32)
    set(OPENGL opengl32)
elseif (UNIX AND NOT APPLE)
    set(OPENGL OpenGL)
endif (WIN32)

# Terroir platform defines
if (WIN32)
    add_compile_definitions(TERROIR_WINDOWS)
endif (WIN32)

if (UNIX AND NOT APPLE)
    add_compile_definitions(TERROIR_LINUX)
endif (UNIX AND NOT APPLE)

# Include headers
include_directories(${PROJECT_SOURCE_DIR}/Terroir/src)

# Defines
add_compile_definitions(TERR_ENABLE_ASSERTS)
#add_compile_definitions(TILING_WM)
add_compile_definitions(GLFW_INCLUDE_NONE)
add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_CUSTOM)

# add_compile_definitions(GLM_FORCE_CTOR_INIT)

# Remove comment to enable test gui
#add_compile_definitions(SHOW_TEST_GUI)
file(GLOB_RECURSE sources "*.c" "*.cpp" "*.h" "*.hpp")

add_library(Terroir STATIC ${sources})

# Pre compiled headers
target_precompile_headers(Terroir PRIVATE pch/Tpch.h)

# Include directory for PCH
include_directories(${PROJECT_SOURCE_DIR}/Terroir/pch)

# Link Export Header
target_include_directories(Terroir PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR} ${STB_INCLUDE_DIRS})

# Link libraries from vcpkg
target_link_libraries(Terroir PUBLIC spdlog::spdlog glfw ${OPENGL} glad::glad imgui::imgui glm::glm Tracy::TracyClient)

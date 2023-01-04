# Set output path to lib
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# Locate packages installed by vcpkg
find_package(spdlog REQUIRED)

# For cmake to generate export macros
include(GenerateExportHeader)

# SO building
add_library(Terroir SHARED src/Application.cpp src/Application.h Terroir.h src/AppEntry.h src/log/Log.cpp src/log/Log.h)

# Macros
generate_export_header(Terroir)

# Link headers
target_include_directories(Terroir PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR})

# Link libraries from vcpkg
target_link_libraries(Terroir PUBLIC spdlog::spdlog)

# Set output path to lib
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# Locate packages installed by vcpkg
find_package(spdlog REQUIRED)
find_package(glfw3 REQUIRED)

# For cmake to generate export macros
include(GenerateExportHeader)

# Include headers
include_directories(${PROJECT_SOURCE_DIR}/Terroir/src)

# Defines
add_compile_definitions(TERR_ENABLE_ASSERTS)
add_compile_definitions(TILING_WM)

# SO building
add_library(Terroir SHARED src/core/application/Application.cpp src/core/application/Application.h include/Terroir.h src/core/AppEntry.h src/log/Log.cpp src/log/Log.h src/core/Types.h src/core/event/Event.h src/core/event/EventType.h src/core/event/KeyEvent.h src/core/event/MouseEvent.h src/core/event/WindowEvent.h src/core/event/ApplicationEvent.h src/core/event/AllEvents.h pch/Tpch.h src/platform/Window.h src/platform/GLFW/GLFWWindow.cpp src/platform/GLFW/GLFWWindow.h src/core/Assert.h src/core/layer/Layer.cpp src/core/layer/Layer.h src/core/layer/LayerStack.cpp src/core/layer/LayerStack.h)

# Macros
generate_export_header(Terroir)

# Pre compiled headers
target_precompile_headers(Terroir PRIVATE pch/Tpch.h)

# Include directory for PCH
include_directories(${PROJECT_SOURCE_DIR}/Terroir/pch)

# Link Export Header
target_include_directories(Terroir PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR})

# Link libraries from vcpkg
target_link_libraries(Terroir PUBLIC spdlog::spdlog glfw OpenGL)

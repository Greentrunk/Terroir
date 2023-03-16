# Set output path to bin
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

# Include headers
include_directories(${PROJECT_SOURCE_DIR}/Terroir/src)



# target_compile_definitions(GLM_FORCE_CTOR_INIT)

# Remove comment to enable test gui
#target_compile_definitions(SHOW_TEST_GUI)
#file(GLOB_RECURSE sources "*.c" "*.cpp" "*.h" "*.hpp")
set(sources
        src/core/application/Application.cpp
        src/core/application/Application.h
        src/core/event/Event.h
        src/core/event/ApplicationEvent.h
        src/core/event/KeyEvent.h
        src/core/event/MouseEvent.h
        src/core/event/WindowEvent.h
        src/core/layer/Layer.h
        src/core/layer/LayerStack.h
        src/core/layer/LayerStack.cpp
        src/core/AppEntry.h
        src/core/Assert.h
        src/core/KeyCodes.h
        src/core/MouseButtonCodes.h
        src/core/Profile.h
        src/core/Timestep.h
        src/core/Types.h
        src/dear-imgui/DearImGuiLayer.cpp
        src/dear-imgui/DearImGuiLayer.h
        src/log/Log.h
        src/log/Log.cpp
        src/math/Math.h
        src/platform/glfw/DearImGuiGLFW.cpp
        src/platform/glfw/DearImGuiGLFW.h
        src/platform/glfw/GLFWWindow.cpp
        src/platform/glfw/GLFWWindow.h
        src/platform/glfw/GLFWInput.cpp
        src/platform/glfw/GLFWInput.h
        src/platform/opengl/DearImGuiOpenGLRenderer.cpp
        src/platform/opengl/DearImGuiOpenGLRenderer.h
        src/platform/Input.h
        src/platform/Window.h
        src/platform/Window.cpp
        src/renderer/buffer/BufferLayout.h
        src/renderer/buffer/IndexBuffer.cpp
        src/renderer/buffer/IndexBuffer.h
        src/renderer/buffer/VertexBuffer.cpp
        src/renderer/buffer/VertexBuffer.h
        src/renderer/camera/OrthographicCamera.cpp
        src/renderer/camera/OrthographicCamera.h
        src/renderer/camera/OrthographicCameraController.cpp
        src/renderer/camera/OrthographicCameraController.h
        src/renderer/opengl/OpenGLContext.cpp
        src/renderer/opengl/OpenGLContext.h
        src/renderer/opengl/OpenGLShader.cpp
        src/renderer/opengl/OpenGLShader.h
        src/renderer/opengl/OpenGLIndexBuffer.cpp
        src/renderer/opengl/OpenGLIndexBuffer.h
        src/renderer/opengl/OpenGLVertexBuffer.cpp
        src/renderer/opengl/OpenGLVertexBuffer.h
        src/renderer/opengl/OpenGLVertexArray.cpp
        src/renderer/opengl/OpenGLVertexArray.h
        src/renderer/opengl/OpenGLRendererAPI.cpp
        src/renderer/opengl/OpenGLRendererAPI.h
        src/renderer/opengl/OpenGLTexture.cpp
        src/renderer/opengl/OpenGLTexture.h
        src/renderer/shader/Shader.h
        src/renderer/shader/Shader.cpp
        src/renderer/shader/ShaderLibrary.cpp
        src/renderer/shader/ShaderLibrary.h
        src/renderer/texture/Texture.h
        src/renderer/texture/Texture2D.h
        src/renderer/texture/Texture2D.cpp
        src/renderer/GraphicsContext.cpp
        src/renderer/GraphicsContext.h
        src/renderer/Renderer.cpp
        src/renderer/Renderer.h
        src/renderer/RendererAPI.h
        src/renderer/RendererAPI.cpp
        src/renderer/RenderCommand.cpp
        src/renderer/RenderCommand.h
        src/renderer/VertexArray.cpp
        src/renderer/VertexArray.h
        src/renderer/stb_image.cpp
        src/renderer/Renderer2D.cpp src/renderer/Renderer2D.h src/renderer/renderable/Sprite.cpp src/renderer/renderable/Sprite.h src/renderer/renderable/Renderable2D.cpp src/renderer/renderable/Renderable2D.h src/core/Color.h)


add_library(Terroir STATIC ${sources} src/core/Profile.h)


# Terroir platform defines
if (WIN32)
    target_compile_definitions(Terroir PRIVATE TERROIR_WINDOWS)
endif (WIN32)

if (UNIX AND NOT APPLE)
    target_compile_definitions(Terroir PRIVATE TERROIR_LINUX)
endif (UNIX AND NOT APPLE)

# Defines
target_compile_definitions(Terroir PRIVATE TERR_ENABLE_ASSERTS)
#target_compile_definitions(Terroir PRIVATE TERR_ENABLE_PROFILING)
#target_compile_definitions(TILING_WM)
target_compile_definitions(Terroir PRIVATE GLFW_INCLUDE_NONE)
target_compile_definitions(Terroir PRIVATE IMGUI_IMPL_OPENGL_LOADER_CUSTOM)

# Pre compiled headers
target_precompile_headers(Terroir PRIVATE pch/Tpch.h)

# Include directory for PCH
include_directories(${PROJECT_SOURCE_DIR}/Terroir/pch)

# Link Export Header
target_include_directories(Terroir PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR} ${STB_INCLUDE_DIRS})

# Link libraries from vcpkg
target_link_libraries(Terroir PUBLIC spdlog::spdlog glfw ${OPENGL} glad::glad imgui::imgui glm::glm TracyClient)

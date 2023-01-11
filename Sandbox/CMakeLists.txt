set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# Include SO headers
include_directories(${PROJECT_SOURCE_DIR}/Terroir/include)
add_executable(Sandbox src/main.cpp)

target_link_libraries(Sandbox PRIVATE Terroir)



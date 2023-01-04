set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_executable(Sandbox src/main.cpp)

target_link_libraries(Sandbox PRIVATE Terroir)

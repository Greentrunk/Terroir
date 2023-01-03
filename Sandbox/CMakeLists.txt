set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_executable(Sandbox src/main.cpp)

target_link_libraries(Sandbox PRIVATE Terroir)
target_include_directories(Sandbox PRIVATE ${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR})

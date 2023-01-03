set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
include(GenerateExportHeader)
add_library(Terroir SHARED src/Test.cpp src/Test.h)
generate_export_header(Terroir)
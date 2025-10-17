add_library(vendor INTERFACE)
target_include_directories(vendor SYSTEM INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/tileson")
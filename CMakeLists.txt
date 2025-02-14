cmake_minimum_required(VERSION 3.10)
project(nauty_wrapper VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Nauty build configuration
set(NAUTY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/nauty2_8_9)
set(NAUTY_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/nauty)

# Create custom target for building Nauty
add_custom_target(nauty_build
    COMMAND ./configure
    COMMAND make
    WORKING_DIRECTORY ${NAUTY_SOURCE_DIR}
)

# Define Nauty library target
add_library(nauty STATIC IMPORTED)
set_target_properties(nauty PROPERTIES 
    IMPORTED_LOCATION ${NAUTY_SOURCE_DIR}/nauty.a
)
add_dependencies(nauty nauty_build)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${NAUTY_SOURCE_DIR}
)

# Add wrapper library
add_library(nauty_wrapper
    src/nauty_wrapper.cpp
)

# Add dependencies
add_dependencies(nauty_wrapper nauty)

# Link against Nauty
target_link_libraries(nauty_wrapper PRIVATE nauty)

# Add tests
enable_testing()
add_subdirectory(test)

# Installation rules
install(TARGETS nauty_wrapper
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY include/
    DESTINATION include
)
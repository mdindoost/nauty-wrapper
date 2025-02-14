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

# Add nauty_classify library
add_library(nauty_classify
    src/nautyClassify.cpp
)

# Link libraries with nauty
target_link_libraries(nauty_wrapper PRIVATE nauty)
target_link_libraries(nauty_classify PRIVATE nauty)

# Add test executable for classify
add_executable(test_classify
    test/test_nautyClassify.cpp
)

# Link test_classify with nauty_classify
target_link_libraries(test_classify PRIVATE nauty_classify)

# Add dependencies
add_dependencies(nauty_wrapper nauty)
add_dependencies(nauty_classify nauty)

# Add tests
enable_testing()
add_subdirectory(test)

# Add test to CTest
add_test(NAME ClassifyTest COMMAND test_classify)

# Installation rules
install(TARGETS nauty_wrapper nauty_classify
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY include/
    DESTINATION include
)
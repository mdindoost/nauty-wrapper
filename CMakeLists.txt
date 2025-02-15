cmake_minimum_required(VERSION 3.10)
project(nauty_wrapper VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Nauty source directory
set(NAUTY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/nauty2_8_9)

# Create bin directory
add_custom_target(create_dirs ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/bin
)

# Compile nauty object files
add_custom_target(nauty_objects ALL
    COMMAND ${CMAKE_C_COMPILER} -c ${NAUTY_SOURCE_DIR}/nauty.c 
            -I${NAUTY_SOURCE_DIR} -fPIC -o ${CMAKE_SOURCE_DIR}/bin/nauty.o
    COMMAND ${CMAKE_C_COMPILER} -c ${NAUTY_SOURCE_DIR}/naugraph.c 
            -I${NAUTY_SOURCE_DIR} -fPIC -o ${CMAKE_SOURCE_DIR}/bin/naugraph.o
    COMMAND ${CMAKE_C_COMPILER} -c ${NAUTY_SOURCE_DIR}/nautil.c 
            -I${NAUTY_SOURCE_DIR} -fPIC -o ${CMAKE_SOURCE_DIR}/bin/nautil.o
    DEPENDS create_dirs
)

# Compile nautyClassify.cpp to object file
add_custom_target(nauty_classify ALL
    COMMAND ${CMAKE_CXX_COMPILER} -c ${CMAKE_SOURCE_DIR}/src/nautyClassify.cpp
            -I${CMAKE_SOURCE_DIR}/include
            -I${NAUTY_SOURCE_DIR}
            -fPIC -o ${CMAKE_SOURCE_DIR}/bin/nautyClassify.o
    DEPENDS nauty_objects
)
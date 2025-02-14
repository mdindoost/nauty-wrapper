# Add the test executable
add_executable(wrapper_test wrapper_test.cpp)

# Link against the wrapper library
target_link_libraries(wrapper_test PRIVATE nauty_wrapper)

# Add the test to CTest
add_test(NAME WrapperTest COMMAND wrapper_test)
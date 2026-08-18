cmake_minimum_required(VERSION 3.20)

project(cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Main application
add_executable(cpp
    src/main.cpp
    src/state.cpp
)
target_include_directories(cpp PRIVATE
    include
)


# Matrix tests
add_executable(test_matrix
    tests/test_matrix.cpp
    src/state.cpp
)
target_include_directories(test_matrix PRIVATE
    include
)

# State tests
add_executable(test_state
    tests/test_state.cpp
    src/state.cpp
)
target_include_directories(test_state PRIVATE
    include
)

# Enable CTest
enable_testing()

add_test(NAME MatrixTests COMMAND test_matrix)
add_test(NAME StateTests COMMAND test_state)
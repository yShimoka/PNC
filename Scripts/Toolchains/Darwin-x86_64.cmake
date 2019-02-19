# Specify the OS X target.
set(CMAKE_SYSTEM_NAME Darwin)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Find and set the clang compiler.
find_program(CMAKE_C_COMPILER names clang)
set(CMAKE_C_COMPILER clang)
find_program(CMAKE_CXX_COMPILER names clang++)
set(CMAKE_CXX_COMPILER clang++)
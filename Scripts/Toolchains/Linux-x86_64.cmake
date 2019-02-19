# Specify the linux target.
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Find and set the gcc compiler.
find_program(CMAKE_C_COMPILER names gcc)
set(CMAKE_C_COMPILER gcc)
find_program(CMAKE_CXX_COMPILER names g++)
set(CMAKE_CXX_COMPILER g++)
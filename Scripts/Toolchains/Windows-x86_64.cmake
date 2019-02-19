# Specify the windows target.
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Enable the WIN32 flag.
set(WIN32 TRUE)

# Find and set the mingw compiler.
find_program(CMAKE_C_COMPILER names x86_64-w64-mingw32-gcc)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
find_program(CMAKE_CXX_COMPILER names x86_64-w64-mingw32-g++)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
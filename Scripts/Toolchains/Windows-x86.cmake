# Specify the windows target.
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR i686)

# Enable the WIN32 flag.
set(WIN32 TRUE)

# Find and set the mingw compiler.
find_program(CMAKE_C_COMPILER names i686-w64-mingw32-gcc)
set(CMAKE_C_COMPILER i686-w64-mingw32-gcc)
find_program(CMAKE_CXX_COMPILER names i686-w64-mingw32-g++)
set(CMAKE_CXX_COMPILER i686-w64-mingw32-g++)
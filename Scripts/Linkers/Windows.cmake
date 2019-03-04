# Link the mingw library.
link_libraries(mingw32)

# Seek and load the SDL2 libraries.
find_library(SDL2_MAIN libSDL2main.a PATH "${CMAKE_LIBRARY_PATH}/lib")
link_libraries(${SDL2_MAIN})
find_library(SDL2 libSDL2.dll.a PATH "${CMAKE_LIBRARY_PATH}/lib")
link_libraries(${SDL2})
find_library(SDL2_TTF libSDL2_ttf.dll.a PATH "${CMAKE_LIBRARY_PATH}/lib")
link_libraries(${SDL2_TTF})
find_library(SDL2_IMG libSDL2_image.dll.a PATH "${CMAKE_LIBRARY_PATH}/lib")
link_libraries(${SDL2_IMG})
find_library(SDL2_MIX libSDL2_mixer.dll.a PATH "${CMAKE_LIBRARY_PATH}/lib")
link_libraries(${SDL2_MIX})

# Include the libraries.
include_directories("${CMAKE_LIBRARY_PATH}/include")
include_directories("${CMAKE_LIBRARY_PATH}/include/SDL2")
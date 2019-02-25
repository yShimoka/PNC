# Link the mingw library.
link_libraries(mingw32)

# Seek and load the SDL2main library.
find_library(SDL2_MAIN libSDL2main.a PATH "${CMAKE_LIBRARY_PATH}/lib")
message(STATUS "SDL2main library location: ${SDL2_MAIN}")
link_libraries(${SDL2_MAIN})

# Seek and load the SDL2 library.
find_library(SDL2 libSDL2.dll.a PATH "${CMAKE_LIBRARY_PATH}/lib")
message(STATUS "SDL2 library location: ${SDL2}")
link_libraries(${SDL2})

# Seek and load the SDL2_ttf library.
find_library(SDL2_TTF libSDL2_ttf.dll.a PATH "${CMAKE_LIBRARY_PATH}/lib")
message(STATUS "SDL2_ttf library location: ${SDL2_TTF}")
link_libraries(${SDL2_TTF})

# Seek and load the SDL2_image library.
find_library(SDL2_IMG libSDL2_image.dll.a PATH "${CMAKE_LIBRARY_PATH}/lib")
message(STATUS "SDL2_image library location: ${SDL2_IMG}")
link_libraries(${SDL2_IMG})

# Seek and load the SDL2_mixer library.
find_library(SDL2_MIX libSDL2_mixer.dll.a PATH "${CMAKE_LIBRARY_PATH}/lib")
message(STATUS "SDL2_mixer library location: ${SDL2_MIX}")
link_libraries(${SDL2_MIX})

# Include all the header files.
include_directories("${CMAKE_LIBRARY_PATH}/include")
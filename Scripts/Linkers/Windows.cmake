# Link the mingw library.
link_libraries(mingw32)

# Set the windows library path.
set(WINDOWS_SDL_LIBRARY_PATH "C:\\SDL2")

# Seek and load the SDL2 libraries.
find_library(SDL2_MAIN libSDL2main.a PATHS "${CMAKE_LIBRARY_PATH}/lib" "${WINDOWS_SDL_LIBRARY_PATH}")
link_libraries(${SDL2_MAIN})
find_library(SDL2 libSDL2.dll.a PATHS "${CMAKE_LIBRARY_PATH}/lib" "${WINDOWS_SDL_LIBRARY_PATH}")
link_libraries(${SDL2})
find_library(SDL2_TTF libSDL2_ttf.dll.a PATHS "${CMAKE_LIBRARY_PATH}/lib" "${WINDOWS_SDL_LIBRARY_PATH}")
link_libraries(${SDL2_TTF})
find_library(SDL2_IMG libSDL2_image.dll.a PATHS "${CMAKE_LIBRARY_PATH}/lib" "${WINDOWS_SDL_LIBRARY_PATH}")
link_libraries(${SDL2_IMG})
find_library(SDL2_MIX libSDL2_mixer.dll.a PATHS "${CMAKE_LIBRARY_PATH}/lib" "${WINDOWS_SDL_LIBRARY_PATH}")
link_libraries(${SDL2_MIX})

# Seek the SDL header files.
find_path(SDL2_HEADER SDL.h PATHS "${CMAKE_LIBRARY_PATH}/lib" "${WINDOWS_SDL_LIBRARY_PATH}")
include_directories(${SDL2_HEADER})
find_path(SDL2_MIX_HEADER SDL_mixer.h PATHS "${CMAKE_LIBRARY_PATH}/lib" "${WINDOWS_SDL_LIBRARY_PATH}")
include_directories(${SDL2_MIX_HEADER})
find_path(SDL2_IMG_HEADER SDL_image.h PATHS "${CMAKE_LIBRARY_PATH}/lib" "${WINDOWS_SDL_LIBRARY_PATH}")
include_directories(${SDL2_IMG_HEADER})
find_path(SDL2_TTF_HEADER SDL_ttf.h PATHS "${CMAKE_LIBRARY_PATH}/lib" "${WINDOWS_SDL_LIBRARY_PATH}")
include_directories(${SDL2_TTF_HEADER})
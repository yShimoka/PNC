# Seek and load the SDL2 library.
find_library(SDL2 SDL2)
message(STATUS "SDL2 library location: ${SDL2}")
link_libraries(${SDL2})
include_directories(${SDL2}/Headers)

# Seek and load the SDL2_image library.
find_library(SDL2_IMG SDL2_image)
message(STATUS "SDL2_image library location: ${SDL2_IMG}")
link_libraries(${SDL2_IMG})
include_directories(${SDL2_IMG}/Headers)

# Seek and load the SDL2_ttf library.
find_library(SDL2_TTF SDL2_ttf)
message(STATUS "SDL2_ttf library location: ${SDL2_TTF}")
link_libraries(${SDL2_TTF})
include_directories(${SDL2_TTF}/Headers)

# Seek and load the SDL2_mixer library.
find_library(SDL2_MIXER SDL2_mixer)
message(STATUS "SDL2_mixer library location: ${SDL2_MIXER}")
link_libraries(${SDL2_MIXER})
include_directories(${SDL2_MIXER}/Headers)
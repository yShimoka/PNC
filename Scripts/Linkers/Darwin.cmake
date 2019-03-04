# Seek and load the SDL2 library.
find_library(SDL2 SDL2)
link_libraries(${SDL2})

# Seek and load the SDL2_image library.
find_library(SDL2_IMG SDL2_image)
link_libraries(${SDL2_IMG})

# Seek and load the SDL2_ttf library.
find_library(SDL2_TTF SDL2_ttf)
link_libraries(${SDL2_TTF})

# Seek and load the SDL2_mixer library.
find_library(SDL2_MIXER SDL2_mixer)
link_libraries(${SDL2_MIXER})
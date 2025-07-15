cmake_minimum_required(VERSION 3.25)
include(FetchContent)

project(SDL-DEMO VERSION 1.0)

# Set the C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Disable Shared Libs
set(BUILD_SHARED_LIBS OFF)
set(SDL_SHARED OFF)
set(SDL_STATIC ON)

# Disable 3rd party dependencies
set(SDLIMAGE_VENDORED OFF)
set(SDLMIXER_VENDORED OFF)

# Fetch SDL3, SDL3_image, and SDL3_mixer from their respective repositories
FetchContent_Declare(
  SDL3_SRC
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-3.2.18
)
FetchContent_MakeAvailable(SDL3_SRC)

FetchContent_Declare(
  SDL3_IMAGE_SRC
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
  GIT_TAG release-3.2.4
)
FetchContent_MakeAvailable(SDL3_IMAGE_SRC)

FetchContent_Declare(
  SDL3_MIXER_SRC
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
  GIT_TAG main
)
FetchContent_MakeAvailable(SDL3_MIXER_SRC)

# Create an executable from our source files
add_executable(sdl-demo src/main.cpp)

# Link our application against SDL3 libraries
target_link_libraries(
    sdl-demo
    PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
)
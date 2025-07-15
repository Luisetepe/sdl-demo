cmake_minimum_required(VERSION 3.25)

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

# Add the SDL3 and SDL3_image subdirectories
add_subdirectory(deps/SDL)
add_subdirectory(deps/SDL_image)
add_subdirectory(deps/SDL_mixer)

# Create an executable from our source files
add_executable(sdl-demo src/main.cpp)

# Link our application against SDL3 and SDL3_image
target_link_libraries(
    sdl-demo
    PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
)
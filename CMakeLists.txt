cmake_minimum_required(VERSION 3.25)
include(FetchContent)

project(SDL-DEMO VERSION 1.0)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Disable Shared Libs
set(BUILD_SHARED_LIBS OFF)
set(SDL_SHARED OFF)
set(SDL_STATIC ON)

# Disable 3rd party dependencies
set(SDLIMAGE_VENDORED OFF)
set(SDLMIXER_VENDORED OFF)

# Define the source assets directory
set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")
# Define the destination assets directory in the build output
set(ASSETS_DEST_DIR "${CMAKE_BINARY_DIR}/release/assets")

# Add the SDL3 and SDL3_image subdirectories
add_subdirectory(deps/SDL)
add_subdirectory(deps/SDL_image)
add_subdirectory(deps/SDL_mixer)

# Create an executable from our source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")
add_executable(sdl-demo ${SOURCES})

# Set the output directory for the executable
set_target_properties(
    sdl-demo
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/release"
)

# Link our application against SDL3 libraries
target_link_libraries(
    sdl-demo
    PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
)

# Add a custom command to copy the assets directory
add_custom_command(
    TARGET sdl-demo
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        "${ASSETS_SOURCE_DIR}"
        "${ASSETS_DEST_DIR}"
    COMMENT "Copying assets to build directory for sdl-demo"
)
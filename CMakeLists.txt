# =============================
# Project and CMake Version
# =============================
cmake_minimum_required(VERSION 3.25)
project(sdl-demo VERSION 1.0)

# =============================
# Compiler Settings
# =============================
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PROJECT_TARGET_NAME sdl-demo)

# =============================
# Dependencies: SDL3, SDL3_image, SDL3_mixer
# =============================
find_library(SDL3_LIB
    NAMES SDL3
    PATHS "${CMAKE_SOURCE_DIR}/vendor/SDL/bin"
    NO_DEFAULT_PATH
)

find_library(SDL3_IMAGE_LIB
    NAMES SDL3_image
    PATHS "${CMAKE_SOURCE_DIR}/vendor/SDL_image/bin"
    NO_DEFAULT_PATH
)

find_library(SDL3_MIXER_LIB
    NAMES SDL3_mixer
    PATHS "${CMAKE_SOURCE_DIR}/vendor/SDL_mixer/bin"
    NO_DEFAULT_PATH
)

# Fail if the library is not found
if(NOT SDL3_LIB)
    message(FATAL_ERROR "SDL library not found in vendor/SDL/bin")
endif()

if(NOT SDL3_IMAGE_LIB)
    message(FATAL_ERROR "SDL_image library not found in vendor/SDL_image/bin")
endif()

if(NOT SDL3_MIXER_LIB)
    message(FATAL_ERROR "SDL_mixer library not found in vendor/SDL_mixer/bin")
endif()

# =============================
# Source Files
# =============================
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp")

# =============================
# Executable Target
# =============================
add_executable(${PROJECT_TARGET_NAME} ${SOURCES})

# =============================
# Include Directories
# =============================
target_include_directories(${PROJECT_TARGET_NAME} PRIVATE
    vendor/SDL/include
    vendor/SDL_image/include
    vendor/SDL_mixer/include
)

# =============================
# Link Libraries
# =============================
target_link_libraries(${PROJECT_TARGET_NAME} PRIVATE
    ${SDL3_LIB}
    ${SDL3_IMAGE_LIB}
    ${SDL3_MIXER_LIB}
)

# =============================
# Output Directories
# =============================
set_target_properties(
    ${PROJECT_TARGET_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}"
)

# =============================
# Assets Copy (Post Build)
# =============================
set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")
set(ASSETS_DEST_DIR "$<TARGET_FILE_DIR:${PROJECT_TARGET_NAME}>/assets")
add_custom_command(
    TARGET ${PROJECT_TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        "${ASSETS_SOURCE_DIR}"
        "${ASSETS_DEST_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL3_LIB}"
            "$<TARGET_FILE_DIR:${PROJECT_TARGET_NAME}>/"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL3_IMAGE_LIB}"
            "$<TARGET_FILE_DIR:${PROJECT_TARGET_NAME}>/"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL3_MIXER_LIB}"
            "$<TARGET_FILE_DIR:${PROJECT_TARGET_NAME}>/"
)
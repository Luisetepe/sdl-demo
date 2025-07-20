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
# Dependencies: SDL3, SDL3_image
# =============================
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)

# =============================
# Source Files
# =============================
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp")

# =============================
# Executable Target
# =============================
add_executable(${PROJECT_TARGET_NAME} ${SOURCES})

# =============================
# Link Libraries
# =============================
target_link_libraries(
    ${PROJECT_TARGET_NAME}
    PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
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
)
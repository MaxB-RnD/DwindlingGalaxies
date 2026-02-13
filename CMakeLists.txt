# ------------------------------------------------------------------------------
# -               V E R S I O N   I D E N T I F I C A T I O N                  -
# ------------------------------------------------------------------------------
# File:                    %name: CMakeLists.txt %
# Date Created:            %date_created: Thur Feb 12 11:21:22 2026 %
# CM Version               %version: 1 %
# CM Instance              %instance: 1 %
# Author:                  %created_by: MBusato %
# ------------------------------------------------------------------------------
# -                          D E S C R I P T I O N                             -
# ------------------------------------------------------------------------------
# CMake template for C++ projects with integrated logging from Shared-Libraries.
#
# ------------------------------------------------------------------------------
# -                          L I C E N S I N G                                 -
# ------------------------------------------------------------------------------
# No licensing restrictions are applicable to the software below.
# ------------------------------------------------------------------------------

# Set Minimum Required CMake Version.
cmake_minimum_required(VERSION 3.16)

# Set C++ Standard (C++17 for Good Balance of Features & Compatibility).
set(CMAKE_CXX_STANDARD 17)

# Set Output Variables
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_VERBOSE_MAKEFILE ON)

# -----------------------------------------------------------------------------
#                              PROJECT SET-UP
# -----------------------------------------------------------------------------
# Set Overarching Simulation Engine Name.
project(Dwindling_Galaxies)

# Move .exe Files to a 'bin' Folder.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../windows-x64)

# Move .lib Files to a 'lib' Folder.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../windows-x64)
# -----------------------------------------------------------------------------


# -----------------------------------------------------------------------------
#                              EXECUTABLE SET-UP
# -----------------------------------------------------------------------------
# Executable for Game Engine.
add_executable(${PROJECT_NAME} 
    "src/main.cpp"
    "src/resources/Resource.rc"
)

# Copy the Fonts Folder to the Build Directory.
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/libs/Fonts
            ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Fonts
)

# Copy the Images Folder to the Build Directory.
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/libs/Images
            ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Images
)

# Copy the Scores Folder to the Build Directory.
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/libs/Scores
            ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Scores
)

# Copy the Sounds Folder to the Build Directory.
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/libs/Sounds
            ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Sounds
)

# Copy the Dynamic Library Files to the Build Directory.
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML/msvc-x64/bin/
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
# -----------------------------------------------------------------------------


# -----------------------------------------------------------------------------
#                                 LIBRARY LINKING 
# -----------------------------------------------------------------------------
# Set Include Path to SFML Library.
set(SFML_DIR
    "${CMAKE_SOURCE_DIR}/libs/SFML/msvc-x64/lib/cmake/SFML"
)

# Add Library Packages.
find_package(SFML 2.6.2 COMPONENTS audio graphics window system REQUIRED)

# Add Project Libraries.
add_subdirectory("src/enemies/")
add_subdirectory("src/mechanics/")
add_subdirectory("src/modifiers/")
add_subdirectory("src/player/")

# Link all Libraries to the Project.
target_link_libraries(${PROJECT_NAME}
    enemies
    mechanics
    modifiers
    player
)
# -----------------------------------------------------------------------------
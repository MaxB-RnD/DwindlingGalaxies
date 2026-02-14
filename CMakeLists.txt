# ------------------------------------------------------------------------------
# -               V E R S I O N   I D E N T I F I C A T I O N                  -
# ------------------------------------------------------------------------------
# File:                    %name: CMakeLists.txt %
# Date Created:            %date_created: Thur Feb 12 11:21:22 2026 %
# CM Version               %version: 2 %
# CM Instance              %instance: 1 %
# Author:                  %created_by: MBusato %
# ------------------------------------------------------------------------------
# -                          D E S C R I P T I O N                             -
# ------------------------------------------------------------------------------
# Cross-platform CMake template for C++ projects with SFML. This build supports 
# both Windows (MinGW) and Linux builds from WSL.
#
# USAGE:
#  1. Before building ensure that the setup script has been run.
#      $ chmod +x setup.sh
#      $ ./setup.sh
#
#  2. Use the Makefile to automatically build the executable. Use 'make help' 
#     for more details. 
#
#  3. For file clean-up on WSL:
#       find . -name "*:Zone.Identifier" -type f -delete
#  
# 4. Give the executable permission to run. (Linux Only)
#       chmod +x dist/linux-x64/Dwindling_Galaxies
# ------------------------------------------------------------------------------
# -                          L I C E N S I N G                                 -
# ------------------------------------------------------------------------------
# Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this 
# software is subject to the license terms found in the LICENSE file located in 
# the root directory of this repository.
# ------------------------------------------------------------------------------

# Set Minimum Required CMake Version.
cmake_minimum_required(VERSION 3.16)

# Set C++ Standard (C++17 for Good Balance of Features & Compatibility).
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set Output Variables.
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_VERBOSE_MAKEFILE ON)


# -----------------------------------------------------------------------------
#                              PROJECT SET-UP
# -----------------------------------------------------------------------------
# Set Overarching Simulation Engine Name.
project(Dwindling_Galaxies)

# Determine Platform-Specific Settings.
if(WIN32 OR MINGW)
    set(PLATFORM_NAME "windows-x64")
    set(SFML_SUBDIR "mingw-x64")
else()
    set(PLATFORM_NAME "linux-x64")
    set(SFML_SUBDIR "linux-x64")
endif()

# Set Output Directories Based on Platform.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../libs/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../libs/)

# Final Output Goes to Clean Deployment Directory.
set(FINAL_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/build/${PLATFORM_NAME})
# -----------------------------------------------------------------------------


# -----------------------------------------------------------------------------
#                              EXECUTABLE SET-UP
# -----------------------------------------------------------------------------
# Executable for Game Engine.
if(WIN32 OR MINGW)
    # Windows Build with Resource File.
    add_executable(${PROJECT_NAME} 
        "src/main.cpp"
        "src/resources/Resource.rc"
    )
    # Set Windows Subsystem (Remove Console Window for Release Builds).
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set_target_properties(${PROJECT_NAME} PROPERTIES
            WIN32_EXECUTABLE TRUE
        )
    endif()
else()
    # Linux Build Without Resource File.
    add_executable(${PROJECT_NAME} 
        "src/main.cpp"
    )
endif()

# Copy the Fonts Folder to the Build Directory.
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/libs/Fonts
            ${FINAL_OUTPUT_DIR}/Fonts
)

# Copy the Images Folder to the Build Directory.
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/libs/Images
            ${FINAL_OUTPUT_DIR}/Images
)

# Copy the Scores Folder to the Build Directory.
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/libs/Scores
            ${FINAL_OUTPUT_DIR}/Scores
)

# Copy the Sounds Folder to the Build Directory.
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/libs/Sounds
            ${FINAL_OUTPUT_DIR}/Sounds
)

# Copy the Executable to the Final Build Directory.
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:${PROJECT_NAME}>
            ${FINAL_OUTPUT_DIR}/
)

# Copy the Dynamic Library Files to the Build Directory.
if(WIN32 OR MINGW)
    # Copy Windows DLLs.
    add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML/${SFML_SUBDIR}/bin/
                ${FINAL_OUTPUT_DIR}
    )
else()
    # Copy Linux Shared Libraries.
    add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML/${SFML_SUBDIR}/lib/
                ${FINAL_OUTPUT_DIR}
    )
endif()
# -----------------------------------------------------------------------------


# -----------------------------------------------------------------------------
#                                 LIBRARY LINKING 
# -----------------------------------------------------------------------------
# Set Include Path to SFML Library.
set(SFML_DIR "${CMAKE_SOURCE_DIR}/libs/SFML/${SFML_SUBDIR}/lib/cmake/SFML")

# Add Library Packages.
find_package(SFML 2.6.2 COMPONENTS audio graphics window system REQUIRED)

# Add Project Libraries.
add_subdirectory("src/enemies/")
add_subdirectory("src/mechanics/")
add_subdirectory("src/modifiers/")
add_subdirectory("src/player/")

# Link all Libraries to the Project (Order Matters).
target_link_libraries(${PROJECT_NAME}
    mechanics
    enemies
    modifiers
    player
)

# Additional Platform-Specific Linking.
if(UNIX AND NOT APPLE)
    # Linux Requires Additional System Libraries.
    target_link_libraries(${PROJECT_NAME}
        pthread
        GL
        openal
        X11
        Xrandr
        Xcursor
        Xi
        FLAC
        vorbisenc
        vorbisfile
        vorbis
        ogg
    )
endif()
# -----------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# -               V E R S I O N   I D E N T I F I C A T I O N -
# ------------------------------------------------------------------------------
# File:                    %name: CMakeLists.txt %
# Date Created:            %date_created: Tue Feb 17 18:43:10 2026 %
# CM Version               %version: 2 %
# CM Instance              %instance: 1 %
# Author:                  %created_by: MBusato %
# ------------------------------------------------------------------------------
# -                          D E S C R I P T I O N -
# ------------------------------------------------------------------------------
# CMake configuration file for the Enemies library. This file manages the 
# compilation of enemy entity classes and links required SFML dependencies.
#
# ------------------------------------------------------------------------------
# -                          L I C E N S I N G -
# ------------------------------------------------------------------------------
# Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this
# software is subject to the license terms found in the LICENSE file located in
# the root directory of this repository.
# ------------------------------------------------------------------------------

# Set Library Name.
set(LIBRARY_NAME "enemies")

# List Headers Explicitly.
set(ENEMIES_HEADERS
    "Alien.h"
    "Helghast.h"
    "MondoShawn.h"
    "Talz.h"
)

# List Sources Explicitly.
set(ENEMIES_SOURCES
    "Alien.cpp"
    "Helghast.cpp"
    "MondoShawn.cpp"
    "Talz.cpp"
)

# Add the Static Library.
add_library(${LIBRARY_NAME} STATIC
    ${ENEMIES_HEADERS}
    ${ENEMIES_SOURCES}
)

# Include Directories for this Library.
target_include_directories(${LIBRARY_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../player/
)

# Link Subfolders for the Library Dependencies.
target_link_libraries(${LIBRARY_NAME} PUBLIC
  sfml-graphics
)
# -----------------------------------------------------------------------------
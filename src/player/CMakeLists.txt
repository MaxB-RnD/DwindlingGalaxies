# ------------------------------------------------------------------------------
# -               V E R S I O N   I D E N T I F I C A T I O N -
# ------------------------------------------------------------------------------
# File:                    %name: CMakeLists.txt %
# Date Created:            %date_created: Tue Feb 17 18:49:12 2026 %
# CM Version               %version: 2 %
# CM Instance              %instance: 1 %
# Author:                  %created_by: MBusato %
# ------------------------------------------------------------------------------
# -                          D E S C R I P T I O N -
# ------------------------------------------------------------------------------
# CMake configuration file for the Player library. This file manages the 
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
set(LIBRARY_NAME "player")

# List Headers Explicitly.
set(PLAYER_HEADERS
    "GameEntity.h"
    "Laser.h"
    "Lives.h"
    "Player.h"
)

# List Sources Explicitly.
set(PLAYER_SOURCES
    "GameEntity.cpp"
    "Laser.cpp"
    "Lives.cpp"
    "Player.cpp"
)

# Add the Static Library.
add_library(${LIBRARY_NAME} STATIC
    ${PLAYER_HEADERS}
    ${PLAYER_SOURCES}
)

# Include Directories for this Library.
target_include_directories(${LIBRARY_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link Subfolders for the Library Dependencies.
target_link_libraries(${LIBRARY_NAME} PUBLIC
  sfml-graphics
)
# -----------------------------------------------------------------------------
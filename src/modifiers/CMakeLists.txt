# ------------------------------------------------------------------------------
# -               V E R S I O N   I D E N T I F I C A T I O N -
# ------------------------------------------------------------------------------
# File:                    %name: CMakeLists.txt %
# Date Created:            %date_created: Tue Feb 17 18:45:23 2026 %
# CM Version               %version: 2 %
# CM Instance              %instance: 1 %
# Author:                  %created_by: MBusato %
# ------------------------------------------------------------------------------
# -                          D E S C R I P T I O N -
# ------------------------------------------------------------------------------
# CMake configuration file for the Modifiers library. This file manages the 
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
set(LIBRARY_NAME "modifiers")

# List Headers Explicitly.
set(MODIFIERS_HEADERS
    "ExtraLive.h"
    "FasterFiring.h"
    "PowerUp.h"
)

# List Sources Explicitly.
set(MODIFIERS_SOURCES
    "ExtraLive.cpp"
    "FasterFiring.cpp"
    "PowerUp.cpp"
)

# Add the Static Library.
add_library(${LIBRARY_NAME} STATIC
    ${MODIFIERS_HEADERS}
    ${MODIFIERS_SOURCES}
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
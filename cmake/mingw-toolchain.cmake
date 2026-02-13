# ------------------------------------------------------------------------------
# -               V E R S I O N   I D E N T I F I C A T I O N                  -
# ------------------------------------------------------------------------------
# File:                    %name: mingw-toolchain.cmake %
# Date Created:            %date_created: Fri Feb 13 19:27:45 2026 %
# CM Version               %version: 1 %
# CM Instance              %instance: 1 %
# Author:                  %created_by: MBusato %
# ------------------------------------------------------------------------------
# -                          D E S C R I P T I O N                             -
# ------------------------------------------------------------------------------
# This toolchain file configures CMake to cross-compile Windows executables
# from a Linux environment using the MinGW-w64 toolchain.
#
# USAGE:
#   cmake -DCMAKE_TOOLCHAIN_FILE=cmake/mingw-toolchain.cmake ..
#
# ------------------------------------------------------------------------------
# -                          L I C E N S I N G                                 -
# ------------------------------------------------------------------------------
# Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this 
# software is subject to the license terms found in the LICENSE file located in 
# the root directory of this repository.
# ------------------------------------------------------------------------------

# Specify the Build System.
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Specify the Cross Compiler.
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

# Where to Look for the Target Environment.
set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)

# Search Headers & Libraries in the Target Environment, Search Programs in the 
# Host Environment.
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Set MinGW Flags.
set(MINGW TRUE)
set(WIN32 TRUE)

#!/bin/bash
# ------------------------------------------------------------------------------
# -               V E R S I O N   I D E N T I F I C A T I O N                  -
# ------------------------------------------------------------------------------
# File:                    %name: setup.sh %
# Date Created:            %date_created: Fri Feb 13 23:23:48 2026 %
# CM Version               %version: 1 %
# CM Instance              %instance: 1 %
# Author:                  %created_by: MBusato %
# ------------------------------------------------------------------------------
# -                          D E S C R I P T I O N                             -
# ------------------------------------------------------------------------------
# This script creates the necessary directory structure for the build system
# and moves the toolchain file to the correct location.
#
# ------------------------------------------------------------------------------
# -                          L I C E N S I N G                                 -
# ------------------------------------------------------------------------------
# Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this 
# software is subject to the license terms found in the LICENSE file located in 
# the root directory of this repository.
# ------------------------------------------------------------------------------

echo "========================================================================"
echo "            Setting up Dwindling Galaxies Build System..."
echo "========================================================================"

# Create CMake Directory if it Doesn't Exist.
if [ ! -d "cmake" ]; then
    echo "Creating cmake/ Directory..."
    mkdir -p cmake
fi

# Move Toolchain File if it's in the Root.
if [ -f "mingw-toolchain.cmake" ]; then
    echo "Moving Toolchain File to cmake/ Directory..."
    mv mingw-toolchain.cmake cmake/
fi

# Verify SFML Library Structure.
echo ""
echo "Checking SFML Library Structure..."

if [ ! -d "libs/SFML" ]; then
    echo "WARNING: libs/SFML directory Not Found!"
    echo "Please Ensure your SFML Libraries are Organised as Follows:"
    echo "  libs/SFML/mingw-x64/    - Windows MinGW Libraries."
    echo "  libs/SFML/linux-x64/    - Linux Libraries."
else
    echo "PASSED: libs/SFML Directory Found."
    
    if [ -d "libs/SFML/mingw-x64" ]; then
        echo "PASSED: Windows MinGW Libraries Found."
    else
        echo "WARNING: libs/SFML/mingw-x64/ Not Found."
    fi
    
    if [ -d "libs/SFML/linux-x64" ]; then
        echo "PASSED: Linux Libraries Found."
    else
        echo "WARNING: libs/SFML/linux-x64/ Not Found."
    fi
fi

# Check for MinGW Compiler.
echo ""
echo "Checking for MinGW Compiler..."
if command -v x86_64-w64-mingw32-g++ &> /dev/null; then
    echo "PASSED: MinGW Compiler Found: $(x86_64-w64-mingw32-g++ --version | head -n1)."
else
    echo "ERROR: MinGW Compiler Not Found!"
    echo "Install it with: sudo apt install mingw-w64 g++-mingw-w64."
fi

# Check for CMake.
echo ""
echo "Checking for CMake..."
if command -v cmake &> /dev/null; then
    echo "PASSED: CMake found: $(cmake --version | head -n1)."
else
    echo "ERROR: CMake Not Found!"
    echo "Install it with: sudo apt install cmake."
fi

# Print a Summary Statement. 
echo ""
echo "Setup Complete! You Can Now Use the Makefile to Build the Project."
echo ""

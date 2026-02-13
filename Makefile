# ------------------------------------------------------------------------------
# -               V E R S I O N   I D E N T I F I C A T I O N                  -
# ------------------------------------------------------------------------------
# File:                    %name: Makefile %
# Date Created:            %date_created: Fri Feb 13 19:27:45 2026 %
# CM Version               %version: 1 %
# CM Instance              %instance: 1 %
# Author:                  %created_by: MBusato %
# ------------------------------------------------------------------------------
# -                          D E S C R I P T I O N                             -
# ------------------------------------------------------------------------------
# This Makefile provides convenient targets for building the Dwindling Galaxies
# executable for both Windows (using MinGW cross-compiler) and Linux platforms,
# in both Debug and Release configurations.
#
# ------------------------------------------------------------------------------
# -                          L I C E N S I N G                                 -
# ------------------------------------------------------------------------------
# No licensing restrictions are applicable to the software below.
# ------------------------------------------------------------------------------

# Project Name.
PROJECT_NAME := Dwindling_Galaxies

# Build Directories.
BUILD_DIR_WIN_DEBUG   := build/windows-debug
BUILD_DIR_WIN_RELEASE := build/windows-release
BUILD_DIR_LIN_DEBUG   := build/linux-debug
BUILD_DIR_LIN_RELEASE := build/linux-release

# Output Directories.
OUTPUT_DIR_WIN := windows-x64
OUTPUT_DIR_LIN := linux-x64

# MinGW Toolchain Configuration.
MINGW_PREFIX := x86_64-w64-mingw32

# Number of Parallel Jobs (Adjust to CPU Spec).
JOBS := $(shell nproc)

# Default Target.
.DEFAULT_GOAL := help


# ------------------------------------------------------------------------------
# PHONY Targets
# ------------------------------------------------------------------------------
.PHONY: all help clean \
        windows-debug windows-release windows-clean \
        linux-debug linux-release linux-clean
# ------------------------------------------------------------------------------


# ------------------------------------------------------------------------------
# Help Target
# ------------------------------------------------------------------------------
help:
	@echo "========================================================================"
	@echo "  	  Dwindling Galaxies - Cross-Platform Build System"
	@echo "========================================================================"
	@echo ""
	@echo "Available Targets:"
	@echo "  make windows-debug     - Build Windows Debug Version (MinGW)."
	@echo "  make windows-release   - Build Windows Release Version (MinGW)."
	@echo "  make linux-debug       - Build Linux Debug Version."
	@echo "  make linux-release     - Build Linux Release Version."
	@echo "  make all               - Build All Configurations."
	@echo "  make clean             - Remove All Build Artifacts."
	@echo "  make windows-clean     - Remove Windows Build Artifacts."
	@echo "  make linux-clean       - Remove Linux Build Artifacts."
	@echo "  make help              - Show this Help Message."
	@echo ""
	@echo "Output Directories:"
	@echo "  Windows: ./build/$(OUTPUT_DIR_WIN)/"
	@echo "  Linux:   ./build/$(OUTPUT_DIR_LIN)/"
	@echo ""
	@echo "========================================================================"
# ------------------------------------------------------------------------------


# ------------------------------------------------------------------------------
# Windows Builds
# ------------------------------------------------------------------------------
windows-debug:
	@echo "========================================================================"
	@echo "  	  	Building Windows Debug Configuration..."
	@echo "========================================================================"
	@mkdir -p $(BUILD_DIR_WIN_DEBUG)/cmake
	cd $(BUILD_DIR_WIN_DEBUG)/cmake && \
		cmake ../../.. \
			-DCMAKE_BUILD_TYPE=Debug \
			-DCMAKE_TOOLCHAIN_FILE=../../../cmake/mingw-toolchain.cmake \
			-DCMAKE_CXX_FLAGS="-g -O0" && \
		cmake --build . -- -j$(JOBS)
	@find build/$(OUTPUT_DIR_WIN) -name "*.dll" ! -name "*-d-*" -delete
	@echo ""
	@echo "Windows Debug Build Complete! Executable: ./build/$(OUTPUT_DIR_WIN)/$(PROJECT_NAME).exe"
	@echo ""

windows-release:
	@echo "========================================================================"
	@echo "  	  	Building Windows Release Configuration..."
	@echo "========================================================================"
	@mkdir -p $(BUILD_DIR_WIN_DEBUG)/cmake
	cd $(BUILD_DIR_WIN_DEBUG)/cmake && \
		cmake ../../.. \
			-DCMAKE_BUILD_TYPE=Release \
			-DCMAKE_TOOLCHAIN_FILE=../../../cmake/mingw-toolchain.cmake \
			-DCMAKE_CXX_FLAGS="-O3 -DNDEBUG" && \
		cmake --build . -- -j$(JOBS)
	@find build/$(OUTPUT_DIR_WIN) -name "*-d-*.dll" -delete
	@echo ""
	@echo "Windows Release Build Complete! Executable: ./build/$(OUTPUT_DIR_WIN)/$(PROJECT_NAME).exe"
	@echo ""
# ------------------------------------------------------------------------------


# ------------------------------------------------------------------------------
# Linux Builds
# ------------------------------------------------------------------------------
linux-debug:
	@echo "========================================================================"
	@echo "  	  	Building Linux Debug Configuration..."
	@echo "========================================================================"
	@mkdir -p $(BUILD_DIR_WIN_DEBUG)/cmake
	cd $(BUILD_DIR_WIN_DEBUG)/cmake && \
		cmake ../../.. \
			-DCMAKE_BUILD_TYPE=Debug \
			-DCMAKE_CXX_FLAGS="-g -O0" && \
		cmake --build . -- -j$(JOBS)
	@echo ""
	@echo "Linux Debug Build Complete! Executable: ./build/$(OUTPUT_DIR_LIN)/$(PROJECT_NAME)"
	@echo ""

linux-release:
	@echo "========================================================================"
	@echo "  	  	Building Linux Release Configuration..."
	@echo "========================================================================"
	@mkdir -p $(BUILD_DIR_WIN_DEBUG)/cmake
	cd $(BUILD_DIR_WIN_DEBUG)/cmake && \
		cmake ../../.. \
			-DCMAKE_BUILD_TYPE=Release \
			-DCMAKE_CXX_FLAGS="-O3 -DNDEBUG" && \
		cmake --build . -- -j$(JOBS)
	@echo ""
	@echo "Linux Release Build Complete! Executable: ./build/$(OUTPUT_DIR_LIN)/$(PROJECT_NAME)"
	@echo ""
# ------------------------------------------------------------------------------


# ------------------------------------------------------------------------------
# Build All Configurations
# ------------------------------------------------------------------------------
all: linux-debug linux-release windows-debug windows-release
	@echo "========================================================================"
	@echo "  	  		All Builds Complete!"
	@echo "========================================================================"
# ------------------------------------------------------------------------------


# ------------------------------------------------------------------------------
# Clean Targets
# # ------------------------------------------------------------------------------
windows-clean:
	@echo "Cleaning Windows Build Artifacts..."
	@rm -rf $(BUILD_DIR_WIN_DEBUG) $(BUILD_DIR_WIN_RELEASE) $(OUTPUT_DIR_WIN)
	@echo "Windows Build Artifacts Removed."

linux-clean:
	@echo "Cleaning Linux Build Artifacts..."
	@rm -rf $(BUILD_DIR_LIN_DEBUG) $(BUILD_DIR_LIN_RELEASE) $(OUTPUT_DIR_LIN)
	@echo "Linux build Artifacts Removed."

clean: windows-clean linux-clean
	@rm -rf build
	@echo "========================================================================"
	@echo "  	  	   All Build Artifacts Removed."
	@echo "========================================================================"
# ------------------------------------------------------------------------------

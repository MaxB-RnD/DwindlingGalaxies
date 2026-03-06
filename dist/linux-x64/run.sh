#!/bin/bash
# ------------------------------------------------------------------------------
# -               V E R S I O N   I D E N T I F I C A T I O N                  -
# ------------------------------------------------------------------------------
# File:                    %name: run.sh %
# Date Created:            %date_created: Fri Mar 06 15:11:21 2026 %
# CM Version               %version: 1 %
# CM Instance              %instance: 1 %
# Author:                  %created_by: MBusato %
# ------------------------------------------------------------------------------
# -                          D E S C R I P T I O N                             -
# ------------------------------------------------------------------------------
# This script launches Dwindling Galaxies with the correct library path set so
# that bundled shared libraries (.so files) located alongside the executable
# are found automatically at runtime.
#
# ------------------------------------------------------------------------------
# -                          L I C E N S I N G                                 -
# ------------------------------------------------------------------------------
# Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this 
# software is subject to the license terms found in the LICENSE file located in 
# the root directory of this repository.
# ------------------------------------------------------------------------------

# Make Sure it Looks in the Directory where the Script Lives. 
cd "$(dirname "$0")"

# Custom Run Command with Library Path Set.
LD_LIBRARY_PATH=. ./Dwindling_Galaxies

# -----------------------------------------------------------------------------
#                          BUILD MODIFIERS LIBRARY 
# -----------------------------------------------------------------------------
set(LIBRARY_NAME "modifiers")

# List Headers Explicitly
set(MODIFIERS_HEADERS
    "ExtraLive.h"
    "FasterFiring.h"
    "PowerUp.h"
)

# List Sources Explicitly
set(MODIFIERS_SOURCES
    "ExtraLive.cpp"
    "FasterFiring.cpp"
    "PowerUp.cpp"
)

# Add the Static Library
add_library(${LIBRARY_NAME} STATIC
    ${MODIFIERS_HEADERS}
    ${MODIFIERS_SOURCES}
)

# Include Directories for this Library
target_include_directories(${LIBRARY_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../player/
)

# Link Subfolders for the Library Dependencies
target_link_libraries(${LIBRARY_NAME} PUBLIC
  sfml-graphics
)
# -----------------------------------------------------------------------------
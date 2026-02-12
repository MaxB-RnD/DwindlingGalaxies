# -----------------------------------------------------------------------------
#                          BUILD ENEMIES LIBRARY 
# -----------------------------------------------------------------------------
set(LIBRARY_NAME "enemies")

# List Headers Explicitly
set(ENEMIES_HEADERS
    "Alien.h"
    "Helghast.h"
    "MondoShawn.h"
    "Talz.h"
)

# List Sources Explicitly
set(ENEMIES_SOURCES
    "Alien.cpp"
    "Helghast.cpp"
    "MondoShawn.cpp"
    "Talz.cpp"
)

# Add the Static Library
add_library(${LIBRARY_NAME} STATIC
    ${ENEMIES_HEADERS}
    ${ENEMIES_SOURCES}
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
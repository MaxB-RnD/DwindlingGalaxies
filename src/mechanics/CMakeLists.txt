# -----------------------------------------------------------------------------
#                          BUILD MECHANICS LIBRARY 
# -----------------------------------------------------------------------------
set(LIBRARY_NAME "mechanics")

# List Headers Explicitly
set(MECHANICS_HEADERS
    "DwindlingGalaxies.h"
    "GameMenu.h"
)

# List Sources Explicitly
set(MECHANICS_SOURCES
    "DwindlingGalaxies.cpp"
    "GameMenu.cpp"
)

# Add the Static Library
add_library(${LIBRARY_NAME} STATIC
    ${MECHANICS_HEADERS}
    ${MECHANICS_SOURCES}
)

# Include Directories for this Library
target_include_directories(${LIBRARY_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../enemies/
    ../modifiers/
    ../player/
)

# Link Subfolders for the Library Dependencies
target_link_libraries(${LIBRARY_NAME} PUBLIC
  sfml-audio
  sfml-graphics
  sfml-window
)
# -----------------------------------------------------------------------------
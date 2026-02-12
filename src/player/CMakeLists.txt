# -----------------------------------------------------------------------------
#                          BUILD PLAYER LIBRARY 
# -----------------------------------------------------------------------------
set(LIBRARY_NAME "player")

# List Headers Explicitly
set(PLAYER_HEADERS
    "GameEntity.h"
    "Laser.h"
    "Lives.h"
    "Player.h"
)

# List Sources Explicitly
set(PLAYER_SOURCES
    "GameEntity.cpp"
    "Laser.cpp"
    "Lives.cpp"
    "Player.cpp"
)

# Add the Static Library
add_library(${LIBRARY_NAME} STATIC
    ${PLAYER_HEADERS}
    ${PLAYER_SOURCES}
)

# Include Directories for this Library
target_include_directories(${LIBRARY_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link Subfolders for the Library Dependencies
target_link_libraries(${LIBRARY_NAME} PUBLIC
  sfml-graphics
)
# -----------------------------------------------------------------------------
# Build an executable
add_executable(GameApp
        main.cpp
        src/Map.cpp
        src/Map.h
        src/GameState.cpp
        src/GameState.h
        src/Bullet.cpp
        src/Bullet.h
        src/Cell.cpp
        src/Cell.h
        src/CellImplementation.h
        src/CellTypes/GrassCell.h
        src/CellTypes/WallCell.h
        src/CellTypes/WallCell.cpp
        src/CellTypes/TurretCell.h
        src/CellTypes/DestinationCell.h
        src/CellTypes/SteakCell.h
        src/CellTypes/HayStackCell.cpp
        src/CellTypes/HayStackCell.h
)

# Link the game executable against the engine dynamic library
target_link_libraries(GameApp Core)

# Include exposed "include" files from engine used to make this executable.
target_include_directories(GameApp PRIVATE
        ../Core/include
)

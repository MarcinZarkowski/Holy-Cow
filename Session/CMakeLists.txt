# Build an executable
add_executable(GameApp
#        src/Session.cpp
#        src/Session.h
        main.cpp
)

# Link the game executable against the engine dynamic library
target_link_libraries(GameApp Core)

# Include exposed "include" files from engine used to make this executable.
target_include_directories(GameApp PRIVATE
        ../Core/include
)

cmake_minimum_required(VERSION 3.10)
project(glad C)

# Build Glad as a static library
add_library(glad STATIC
        src/glad.c
)

# Expose include directory to any target that links with glad
target_include_directories(glad PUBLIC
        include/
)

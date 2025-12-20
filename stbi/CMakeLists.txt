cmake_minimum_required(VERSION 3.10)
project(stbi)

# Build stbi as a static library
add_library(stbi STATIC
    stbi.cpp
)

target_include_directories(stbi PUBLIC
    include
)


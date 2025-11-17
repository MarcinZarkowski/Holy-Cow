#
set(HEADER_FILES
        include/Core.h
        headers/utils.h
        headers/CoreApplication.h
        headers/pch.h
        headers/CoreWindow.h
        headers/WindowImplementation.h
        src/GLFWsrc/WindowGLFW.h
)

set(SOURCE_CODE_FILES
        src/CoreApplication.cpp
        src/CoreWindow.cpp
        src/CoreWindow.cpp
        src/WindowGLFW.cpp
)

# Build a dynamic library (SHARED)
add_library(Core SHARED
        ${HEADER_FILES}
        ${SOURCE_CODE_FILES}
)

target_compile_definitions(Core
        PRIVATE
        CORE_LIB
        CORE_GLFW
        PUBLIC
        $<$<CONFIG:Debug>:CORE_DEBUG=2>
        $<$<CONFIG:RelWithDebInfo>:CORE_DEBUG=1>
)

# if using Microsoft compiler, set CORE_MSVC so game is built
if(MSVC)
    target_compile_definitions(Core PUBLIC CORE_MSVC)
endif()

target_include_directories(Core PRIVATE ../glfw/include src)

target_link_libraries(Core glfw)

target_precompile_headers(Core PRIVATE headers/pch.h)


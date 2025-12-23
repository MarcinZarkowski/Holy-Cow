#
set(HEADER_FILES
        include/Core.h
        include/utils.h
        include/CoreApplication.h
        include/pch.h

        include/CoreWindow.h
        include/WindowImplementation.h
        include/GLFWsrc/WindowGLFW.h

        include/Renderer/Image.h
        include/Renderer/ImageImplementation.h
        include/GLFWsrc/ImageGLFW.h

        include/Renderer/Shader.h
        include/Renderer/ShaderImplementation.h
        include/GLFWsrc/ShaderGLFW.h

        include/Renderer/Renderer.h
        include/Renderer/RendererImplementation.h
        include/GLFWsrc/RendererGLFW.h

        include/KeyEvent.h

        include/WindowEvent.h
)

set(SOURCE_CODE_FILES
        src/CoreApplication.cpp

        src/CoreWindow.cpp
        src/GLFWsrc/WindowGLFW.cpp

        src/Renderer/Image.cpp
        src/GLFWsrc/ImageGLFW.cpp

        src/Renderer/Shader.cpp
        src/GLFWsrc/ShaderGLFW.cpp

        src/Renderer/Renderer.cpp
        src/GLFWsrc/RendererGLFW.cpp

        src/KeyEvent.cpp

        src/WindowEvent.cpp
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
        CORE_OPENGL
        PUBLIC
        $<$<CONFIG:Debug>:CORE_DEBUG=2>
        $<$<CONFIG:RelWithDebInfo>:CORE_DEBUG=1>
)

# if using Microsoft compiler, set CORE_MSVC so game is built
if(MSVC)
    target_compile_definitions(Core PUBLIC CORE_MSVC)
endif()

target_include_directories(Core PRIVATE
        include
)

target_link_libraries(Core
        PRIVATE
        glfw
        glad
        stbi
)

target_precompile_headers(Core PRIVATE include/pch.h)

file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR}/Core)
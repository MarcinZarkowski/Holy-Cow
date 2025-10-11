#
set(HEADER_FILES
        include/Core.h
        headers/utils.h
        headers/CoreApplication.h
        headers/pch.h
)

set(SOURCE_CODE_FILES
        src/CoreApplication.cpp
)

# Build a dynamic library (SHARED))
add_library(Core SHARED
        ${HEADER_FILES}
        ${SOURCE_CODE_FILES}
)


target_compile_definitions(Core
        PRIVATE
        CORE_LIB

        PUBLIC
        $<$<CONFIG:Debug>:CORE_DEBUG=2>
        $<$<CONFIG:RelWithDebInfo>:CORE_DEBUG=1>
)

# if using Microsoft compiler, set CORE_MSVC so game is built
if(MSVC)
    target_compile_definitions(Core PUBLIC CORE_MSVC)
endif()

target_precompile_headers(Core PRIVATE headers/pch.h)


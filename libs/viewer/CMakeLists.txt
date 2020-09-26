cmake_minimum_required(VERSION 3.10)
project(viewer)

set(TARGET viewer)
set(PUBLIC_HDR_DIR include)

# ==================================================================================================
# Sources and headers
# ==================================================================================================
set(PUBLIC_HDRS
        include/viewer/SimpleViewer.h
        include/viewer/ViewSettings.h
)

set(SRCS
        src/SimpleViewer.cpp
        src/ViewSettings.cpp
)

# ==================================================================================================
# Include and target definitions
# ==================================================================================================
add_library(${TARGET} STATIC ${PUBLIC_HDRS} ${SRCS})
target_link_libraries(${TARGET} PUBLIC imgui cgltf filament gltfio filagui)
target_include_directories(${TARGET} PUBLIC ${PUBLIC_HDR_DIR})

# ==================================================================================================
# Compiler flags
# ==================================================================================================
if (MSVC)
    target_compile_options(${TARGET} PRIVATE $<$<CONFIG:Release>:/fp:fast>)
else()
    target_compile_options(${TARGET} PRIVATE $<$<CONFIG:Release>:-ffast-math>)
    target_compile_options(${TARGET} PRIVATE -Wno-deprecated-register)
endif()

# ==================================================================================================
# Installation
# ==================================================================================================
install(TARGETS ${TARGET} ARCHIVE DESTINATION lib/${DIST_DIR})
install(DIRECTORY ${PUBLIC_HDR_DIR}/geometry DESTINATION include)

# ==================================================================================================
# Tests
# ==================================================================================================
if (NOT ANDROID AND NOT WEBGL AND NOT IOS)
    add_executable(test_viewsettings tests/test_viewsettings.cpp)
    target_link_libraries(test_viewsettings PRIVATE ${TARGET} gtest)
endif()

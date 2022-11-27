cmake_minimum_required(VERSION 3.14)
project(karamay_engine_graphics_unit)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_ARCH "-m64") 

link_libraries(opengl32.lib)
#sys

link_libraries(glew32s.lib)
#link_directories(karamay_engine_graphics_unit/dependencies/glew-2.1.0/lib/Release/Win32/)
link_directories(karamay_engine_graphics_unit/dependencies/glew-2.2.0/lib/Release/x64/)

link_libraries(glfw3.lib)
#link_directories(karamay_engine_graphics_unit/dependencies/glfw-3.3.bin.WIN32/lib-vc2019/)
link_directories(karamay_engine_graphics_unit/dependencies/glfw-3.3.4.bin.WIN64/lib-vc2019/)

link_libraries(lua54.lib)
link_directories(karamay_engine_graphics_unit/dependencies/lua54/)

link_libraries(vulkan-1.lib)
link_directories(karamay_engine_graphics_unit/dependencies/vulkan/lib/)


include_directories(karamay_engine_graphics_unit/dependencies)
include_directories(karamay_engine_graphics_unit/dependencies/glm_pack/include)
include_directories(karamay_engine_graphics_unit/dependencies/lua54/include)
include_directories(karamay_engine_graphics_unit/source)

file(GLOB_RECURSE USER_LIBS_PATH karamay_engine_graphics_unit/source/*.cpp)
# AUX_SOURCE_DIRECTORY(karamay_engine_graphics_unit/source/graphics DIR_SRCS)
#message("AAAAAA ${DIR_SRCS}")
add_executable(karamay_engine_graphics_unit ${USER_LIBS_PATH} "karamay_engine_graphics_unit/source/Kanas/" "karamay_engine_graphics_unit/source/Kanas/Core/swapchain.h" "karamay_engine_graphics_unit/source/Kanas/Core/swapchain.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/surface.h" "karamay_engine_graphics_unit/source/Kanas/Core/surface.cpp")

target_link_libraries(karamay_engine_graphics_unit glew32s.lib glfw3.lib)


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/karamay_engine_graphics_unit/assets
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/karamay_engine_graphics_unit/shaders
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/karamay_engine_graphics_unit/assets
#       ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
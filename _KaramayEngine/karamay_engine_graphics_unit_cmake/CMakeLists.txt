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
add_executable(karamay_engine_graphics_unit ${USER_LIBS_PATH} "karamay_engine_graphics_unit/source/Kanas/Kanas.h"  "karamay_engine_graphics_unit/source/Kanas/Core/VulkanObject.h" "karamay_engine_graphics_unit/source/Kanas/Core/Device.h" "karamay_engine_graphics_unit/source/Kanas/Core/VulkanInstance.h" "karamay_engine_graphics_unit/source/Kanas/Core/PhysicalDevice.h" "karamay_engine_graphics_unit/source/Kanas/Core/ShaderModule.h" "karamay_engine_graphics_unit/source/Kanas/Core/DeviceObject.h" "karamay_engine_graphics_unit/source/Kanas/Core/Buffer.h" "karamay_engine_graphics_unit/source/Kanas/Core/Image.h" "karamay_engine_graphics_unit/source/Kanas/Core/BufferView.h" "karamay_engine_graphics_unit/source/Kanas/Core/ImageView.h" "karamay_engine_graphics_unit/source/Kanas/Core/Semaphore.h" "karamay_engine_graphics_unit/source/Kanas/Core/Fence.h" "karamay_engine_graphics_unit/source/Kanas/Core/Event.h" "karamay_engine_graphics_unit/source/Kanas/Core/DeviceMemory.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/Buffer.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/CommandBuffer.h" "karamay_engine_graphics_unit/source/Kanas/Core/Image.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/Fence.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/BufferView.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/Event.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/ImageView.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/Semaphore.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/ShaderModule.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/Pipeline.h" "karamay_engine_graphics_unit/source/Kanas/Core/GraphicsPipeline.h" "karamay_engine_graphics_unit/source/Kanas/Core/ComputePipeline.h" "karamay_engine_graphics_unit/source/Kanas/Core/RayTracingPipeline.h" "karamay_engine_graphics_unit/source/Kanas/Core/ComputePipeline.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/PipelineCache.h" "karamay_engine_graphics_unit/source/Kanas/Core/PipelineLayout.h" "karamay_engine_graphics_unit/source/Kanas/Core/GraphicsPipeline.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/Pipeline.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/RenderPass.h" "karamay_engine_graphics_unit/source/Kanas/Core/RenderPass.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/Framebuffer.h" "karamay_engine_graphics_unit/source/Kanas/Core/PipelineCache.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/PipelineLayout.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/DescriptorSetLayout.h" "karamay_engine_graphics_unit/source/Kanas/Core/DescriptorSetLayout.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/DescriptorSet.h" "karamay_engine_graphics_unit/source/Kanas/Core/DescriptorSet.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/DescriptorPool.h" "karamay_engine_graphics_unit/source/Kanas/Core/DescriptorPool.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/Sampler.h" "karamay_engine_graphics_unit/source/Kanas/Core/Sampler.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/CommandPool.h" "karamay_engine_graphics_unit/source/Kanas/Core/CommandPool.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/Queue.h" "karamay_engine_graphics_unit/source/Kanas/Core/Queue.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/QueryPool.h" "karamay_engine_graphics_unit/source/Kanas/Core/QueryPool.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/RayTracingPipeline.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/Framebuffer.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/Device.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/PhysicalDevice.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/KanasCoreMinimal.h" "karamay_engine_graphics_unit/source/Kanas/Core/UniformBuffer.h" "karamay_engine_graphics_unit/source/Kanas/Core/UniformBuffer.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/KanasCoreMacros.h" "karamay_engine_graphics_unit/source/Kanas/Core/KanasCoreTypes.h" "karamay_engine_graphics_unit/source/Kanas/Core/VulkanInstance.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/AccelerationStructure.h" "karamay_engine_graphics_unit/source/Kanas/Core/AccelerationStructure.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/DeviceMemoryAllocator.h" "karamay_engine_graphics_unit/source/Kanas/Core/KanasFlagBits.h" "karamay_engine_graphics_unit/source/Core/CoreLibrary.h" "karamay_engine_graphics_unit/source/Kanas/Core/Shader.h" "karamay_engine_graphics_unit/source/Kanas/Core/DeferredOperation.h" "karamay_engine_graphics_unit/source/Kanas/Core/DeferredOperation.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/Shader.cpp" "karamay_engine_graphics_unit/source/Kanas/Core/DescriptorUpdateTemplate.h" "karamay_engine_graphics_unit/source/Kanas/Core/Resource.h")

target_link_libraries(karamay_engine_graphics_unit glew32s.lib glfw3.lib)


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/karamay_engine_graphics_unit/assets
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/karamay_engine_graphics_unit/shaders
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/karamay_engine_graphics_unit/assets
#       ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
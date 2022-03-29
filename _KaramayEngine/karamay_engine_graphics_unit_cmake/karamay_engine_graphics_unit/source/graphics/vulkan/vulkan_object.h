#ifndef VULKAN_OBJECT_H
#define VULKAN_OBJECT_H
#include "public/stl.h"
#include "public/vulkan_core.h"

enum class sharing_mode
{
	exclusive = VK_SHARING_MODE_EXCLUSIVE,
	concurrent = VK_SHARING_MODE_CONCURRENT
};

enum class buffer_usage : VkBufferUsageFlags
{
    // clang-format off
    transfer_src = VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
    transfer_dst = VK_BUFFER_USAGE_TRANSFER_DST_BIT,
    uniform_texel_buffer = VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT,
    storage_texel_buffer = VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT,
    uniform_buffer = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
    storage_buffer = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
    index_buffer = VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
    vertex_buffer = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
    indirect_buffer = VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT,
    shader_device_address = VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT,
#if defined( VK_ENABLE_BETA_EXTENSIONS )
    eVideoDecodeSrcKHR = VK_BUFFER_USAGE_VIDEO_DECODE_SRC_BIT_KHR,
    eVideoDecodeDstKHR = VK_BUFFER_USAGE_VIDEO_DECODE_DST_BIT_KHR,
    eVideoEncodeDstKHR = VK_BUFFER_USAGE_VIDEO_ENCODE_DST_BIT_KHR,
    eVideoEncodeSrcKHR = VK_BUFFER_USAGE_VIDEO_ENCODE_SRC_BIT_KHR,
#endif /*VK_ENABLE_BETA_EXTENSIONS*/
    transform_feedback_buffer_ext= VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT,
    transform_feedback_counter_buffer_ext = VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT,
    conditional_rendering_ext = VK_BUFFER_USAGE_CONDITIONAL_RENDERING_BIT_EXT,
    acceleration_structure_build_input_read_only_khr = VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR,
    acceleration_structure_storage_khr = VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR,
    shader_binding_table_khr = VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR,
    ray_tracing_nv = VK_BUFFER_USAGE_RAY_TRACING_BIT_NV,
    shader_device_address_ext = VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT_EXT,
    shader_device_address_khr = VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT_KHR,
    // clang-format on
};

template<typename vk_handle_t>
class vulkan_object
{
public:

    vulkan_object() = default;

    vulkan_object(const vulkan_object&) = delete;
    vulkan_object& operator=(const vulkan_object&) = delete;

    virtual ~vulkan_object() = default;

public:

	vk_handle_t handle() const noexcept { return _handle; }

	virtual bool is_valid() const noexcept { return _handle != nullptr; }

protected:

    vk_handle_t _handle = nullptr;

};

#endif
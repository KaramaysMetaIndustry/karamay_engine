#ifndef _KANAS_FLAG_BITS_H_
#define _KANAS_FLAG_BITS_H_

#include "Core/CoreLibrary.h"
#include "KanasCoreMacros.h"
#include "public/vulkan_core.h"
#include "public/json.h"

_KANAS_CORE_BEGIN

template<typename VK_ENUM_T>
struct vulkan_enum
{

};

struct image_layout
{
    enum class t
    {
        undefined = VK_IMAGE_LAYOUT_UNDEFINED,
        general = VK_IMAGE_LAYOUT_GENERAL,
        color_attachment_optimal = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        depth_stencil_attachment_optimal = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
        depth_stencil_read_only_optimal = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
        shader_read_only_optimal = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        transfer_src_optimal = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
        transfer_dst_optimal = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        preinitialized = VK_IMAGE_LAYOUT_PREINITIALIZED,
        depth_read_only_stencil_attachment_optimal = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL,
        depth_attachment_stencil_read_only_optimal = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL,
        depth_attachment_optimal = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
        depth_read_only_optimal = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
        stencil_attachment_attachment_optimal = VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL,
        stencil_read_only_optimal = VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL,
        present_src = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
    };

    t v{ t::undefined };

    [[nodiscard]] VkImageLayout raw() const
    {
        return static_cast<VkImageLayout>(v);
    }

    image_layout() = default;

    image_layout(image_layout::t val) : v(val) {}

};

struct attachment_store_op
{
    enum class t
    {
        store = VK_ATTACHMENT_STORE_OP_STORE,
        dont_care = VK_ATTACHMENT_STORE_OP_DONT_CARE,
        none_qcom = VK_ATTACHMENT_STORE_OP_NONE_QCOM
    };

    t v{ t::dont_care };

    [[nodiscard]] VkAttachmentStoreOp raw() const
    {
        return static_cast<VkAttachmentStoreOp>(v);
    }

    attachment_store_op() = default;

    explicit attachment_store_op(attachment_store_op::t val) : v(val) {}
};



struct attachment_load_op
{
    enum class t
    {
        load = VK_ATTACHMENT_LOAD_OP_LOAD,
        clear = VK_ATTACHMENT_LOAD_OP_CLEAR,
        dont_care = VK_ATTACHMENT_LOAD_OP_DONT_CARE
    };

    t v{ t::dont_care };

    [[nodiscard]] VkAttachmentLoadOp raw() const
    {
        return static_cast<VkAttachmentLoadOp>(v);
    }

    attachment_load_op() = default;

    explicit attachment_load_op(attachment_load_op::t val) : v(val) {}

};

struct sample_count
{
    enum class t
    {
        count_1 = VK_SAMPLE_COUNT_1_BIT,
        count_2 = VK_SAMPLE_COUNT_2_BIT,
        count_4 = VK_SAMPLE_COUNT_4_BIT,
        count_8 = VK_SAMPLE_COUNT_8_BIT,
        count_16 = VK_SAMPLE_COUNT_16_BIT,
        count_32 = VK_SAMPLE_COUNT_32_BIT,
        count_64 = VK_SAMPLE_COUNT_64_BIT
    };

    t v{ t::count_1 };

    [[nodiscard]] constexpr VkSampleCountFlagBits raw() const
    {
        return static_cast<VkSampleCountFlagBits>(v);
    }

    sample_count() = default;

    explicit sample_count(sample_count::t val) : v(val) {}
};


template<typename FLAG_T>
struct vulkan_flags
{
	[[nodiscard]] VkFlags get() const
	{
		return flags;
	}

    void set(image_layout lay) const
    {

    }

	void reset()
	{
		flags = 0;
	}

	void clone(FLAG_T InFlags)
	{
		flags = InFlags;
	}

	bool is_subset_of(FLAG_T InFlags)
	{
		return false;
	}

protected:

	VkFlags flags{ 0 };
};

#define DECAL_FLAG(FUNCTION_NAME, VK_BIT)\
auto& set_##FUNCTION_NAME##(bool active = true)\
{\
	flags |= active ? (VK_BIT) : 0;\
	return *this;\
}\
bool is_##FUNCTION_NAME##_active() const\
{\
	return flags & VK_BIT;\
}

struct memory_property_flags : public vulkan_flags<memory_property_flags>
{
	DECAL_FLAG(device_local, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
	DECAL_FLAG(host_visible, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
	DECAL_FLAG(host_coherent, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
	DECAL_FLAG(host_cached, VK_MEMORY_PROPERTY_HOST_CACHED_BIT)
	DECAL_FLAG(lazily_alllocated, VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT)
	DECAL_FLAG(protected_memory, VK_MEMORY_PROPERTY_PROTECTED_BIT)
};

struct image_usage_flags : public vulkan_flags<image_usage_flags>
{
	DECAL_FLAG(transfer_src, VK_IMAGE_USAGE_TRANSFER_SRC_BIT)
	DECAL_FLAG(transfer_dst, VK_IMAGE_USAGE_TRANSFER_DST_BIT)
	DECAL_FLAG(sampled, VK_IMAGE_USAGE_SAMPLED_BIT)
	DECAL_FLAG(storage, VK_IMAGE_USAGE_STORAGE_BIT)
	DECAL_FLAG(color_attachment, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT)
	DECAL_FLAG(depth_stencil_attachment, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
	DECAL_FLAG(transient_attachment, VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT)
	DECAL_FLAG(input_attachment, VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT)
};

struct buffer_usage_flags : public vulkan_flags<buffer_usage_flags>
{
	DECAL_FLAG(transfer_src, VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
	DECAL_FLAG(transfer_dst, VK_BUFFER_USAGE_TRANSFER_DST_BIT)
	DECAL_FLAG(uniform_texel_buffer, VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT)
	DECAL_FLAG(storage_texel_buffer, VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT)
	DECAL_FLAG(uniform_buffer, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
	DECAL_FLAG(storage_buffer, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT)
	DECAL_FLAG(index_buffer, VK_BUFFER_USAGE_INDEX_BUFFER_BIT)
	DECAL_FLAG(vertex_buffer, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT)
	DECAL_FLAG(indirect_buffer, VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT)
	DECAL_FLAG(shader_device_address, VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT)
};

struct pipeline_stage_flags : public vulkan_flags<pipeline_stage_flags>
{
	DECAL_FLAG(top_of_pipe, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT)
	DECAL_FLAG(draw_indirect, VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT)
	DECAL_FLAG(vertex_input, VK_PIPELINE_STAGE_VERTEX_INPUT_BIT)
	DECAL_FLAG(vertex_shader, VK_PIPELINE_STAGE_VERTEX_SHADER_BIT)
	DECAL_FLAG(tessellation_control_shader, VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT)
	DECAL_FLAG(tessellation_evaluation_shader, VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT)
	DECAL_FLAG(geometry_shader, VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT)
	DECAL_FLAG(fragment_shader, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT)
	DECAL_FLAG(early_fragment_tests, VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT)
	DECAL_FLAG(late_fragment_tests, VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT)
	DECAL_FLAG(color_attachment_output, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT)
	DECAL_FLAG(compute_shader, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT)
	DECAL_FLAG(transfer, VK_PIPELINE_STAGE_TRANSFER_BIT)
	DECAL_FLAG(bottom_of_pipe, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT)
	DECAL_FLAG(host, VK_PIPELINE_STAGE_HOST_BIT)
	DECAL_FLAG(all_graphics, VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT)
	DECAL_FLAG(all_commands, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT)
};

struct shader_stage_flags : public vulkan_flags<shader_stage_flags>
{
	DECAL_FLAG(vertex, VK_SHADER_STAGE_VERTEX_BIT)
    DECAL_FLAG(tessellation_control, VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT)
    DECAL_FLAG(tessellation_evaluation, VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT)
    DECAL_FLAG(geometry, VK_SHADER_STAGE_GEOMETRY_BIT)
    DECAL_FLAG(fragment, VK_SHADER_STAGE_FRAGMENT_BIT)
    DECAL_FLAG(compute, VK_SHADER_STAGE_COMPUTE_BIT)
    DECAL_FLAG(all_graphics, VK_SHADER_STAGE_ALL_GRAPHICS)
    DECAL_FLAG(all, VK_SHADER_STAGE_ALL)
    DECAL_FLAG(raygen, VK_SHADER_STAGE_RAYGEN_BIT_KHR)
    DECAL_FLAG(any_hit, VK_SHADER_STAGE_ANY_HIT_BIT_KHR)
    DECAL_FLAG(closest_hit, VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR)
    DECAL_FLAG(miss, VK_SHADER_STAGE_MISS_BIT_KHR)
    DECAL_FLAG(intersection, VK_SHADER_STAGE_INTERSECTION_BIT_KHR)
    DECAL_FLAG(callable, VK_SHADER_STAGE_CALLABLE_BIT_KHR)
};

struct access_flags : public vulkan_flags<access_flags>
{
	DECAL_FLAG(indirect_command_read, VK_ACCESS_INDIRECT_COMMAND_READ_BIT)
	DECAL_FLAG(index_read, VK_ACCESS_INDEX_READ_BIT)
	DECAL_FLAG(vertex_attribute_read, VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT)
	DECAL_FLAG(uniform_read, VK_ACCESS_UNIFORM_READ_BIT)
	DECAL_FLAG(input_attachment_read, VK_ACCESS_INPUT_ATTACHMENT_READ_BIT)
	DECAL_FLAG(shader_read, VK_ACCESS_SHADER_READ_BIT)
	DECAL_FLAG(shader_write, VK_ACCESS_SHADER_WRITE_BIT)
	DECAL_FLAG(color_attachment_read, VK_ACCESS_COLOR_ATTACHMENT_READ_BIT)
	DECAL_FLAG(color_attachment_write, VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT)
	DECAL_FLAG(depth_stencil_attachment_read, VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT)
	DECAL_FLAG(depth_stencil_attachment_write, VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT)
	DECAL_FLAG(transfer_read, VK_ACCESS_TRANSFER_READ_BIT)
	DECAL_FLAG(transfer_write, VK_ACCESS_TRANSFER_WRITE_BIT)
	DECAL_FLAG(host_read, VK_ACCESS_HOST_READ_BIT)
	DECAL_FLAG(host_write, VK_ACCESS_HOST_WRITE_BIT)
	DECAL_FLAG(memory_read, VK_ACCESS_MEMORY_READ_BIT)
	DECAL_FLAG(memory_write, VK_ACCESS_MEMORY_WRITE_BIT)
};

struct dependency_flags : public vulkan_flags<dependency_flags>
{
	DECAL_FLAG(by_region, VK_DEPENDENCY_BY_REGION_BIT)
	DECAL_FLAG(device_group, VK_DEPENDENCY_DEVICE_GROUP_BIT)
	DECAL_FLAG(view_local, VK_DEPENDENCY_VIEW_LOCAL_BIT)
};

struct command_buffer_reset_flags : public vulkan_flags<command_buffer_reset_flags>
{
	DECAL_FLAG(release_resources, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT)
};

struct command_buffer_usage_flags : public vulkan_flags<command_buffer_usage_flags>
{
	DECAL_FLAG(one_time_submit, VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT)
	DECAL_FLAG(render_pass_continue, VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT)
	DECAL_FLAG(simultaneous_use, VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT)
};

struct query_control_flags : public vulkan_flags<query_control_flags>
{
	DECAL_FLAG(precise, VK_QUERY_CONTROL_PRECISE_BIT)
};

struct query_pipeline_statistic_flags : public vulkan_flags<query_pipeline_statistic_flags>
{
	DECAL_FLAG(input_assembly_vertices,VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_VERTICES_BIT)
	DECAL_FLAG(input_assembly_primitives,VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_PRIMITIVES_BIT)
	DECAL_FLAG(vertex_shader_invocations,VK_QUERY_PIPELINE_STATISTIC_VERTEX_SHADER_INVOCATIONS_BIT)
	DECAL_FLAG(geometry_shader_invocations,VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_INVOCATIONS_BIT)
	DECAL_FLAG(geometry_shader_primitives,VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_PRIMITIVES_BIT)
	DECAL_FLAG(clipping_invocations,VK_QUERY_PIPELINE_STATISTIC_CLIPPING_INVOCATIONS_BIT)
	DECAL_FLAG(clipping_primitives,VK_QUERY_PIPELINE_STATISTIC_CLIPPING_PRIMITIVES_BIT)
	DECAL_FLAG(fragment_shader_invocations,VK_QUERY_PIPELINE_STATISTIC_FRAGMENT_SHADER_INVOCATIONS_BIT)
	DECAL_FLAG(tessellation_control_shader_patches,VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_CONTROL_SHADER_PATCHES_BIT)
	DECAL_FLAG(tessellation_evaluation_shader_invocations,VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_EVALUATION_SHADER_INVOCATIONS_BIT)
	DECAL_FLAG(compute_shader_invocations,VK_QUERY_PIPELINE_STATISTIC_COMPUTE_SHADER_INVOCATIONS_BIT)
};

struct framebuffer_create_flags : public vulkan_flags<framebuffer_create_flags>
{
	DECAL_FLAG(imageless, VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT)
};


enum class PipelineStageFlagBits
{
	TransformFeedbackEXT = VK_PIPELINE_STAGE_TRANSFORM_FEEDBACK_BIT_EXT,
	ConditionalRenderingEXT = VK_PIPELINE_STAGE_CONDITIONAL_RENDERING_BIT_EXT,
	AccelerationStructureBuildKHR = VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR,
	RayTracingShaderKHR = VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR,
	ShadingRateImage = VK_PIPELINE_STAGE_SHADING_RATE_IMAGE_BIT_NV,
	TaskShaderNV = VK_PIPELINE_STAGE_TASK_SHADER_BIT_NV,
	MeshShaderNV = VK_PIPELINE_STAGE_MESH_SHADER_BIT_NV,

	FragmentDensityProcessEXT = VK_PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT_EXT,
	CommandPrepocessNV = VK_PIPELINE_STAGE_COMMAND_PREPROCESS_BIT_NV,
	NoneKHR = VK_PIPELINE_STAGE_NONE_KHR,
	RayTracingShaderNV = VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_NV,
	AccelerationStructureBuildNV = VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_NV,
	FragmentShadingRateAttachmentKHR = VK_PIPELINE_STAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR,
	MaxEnum = VK_PIPELINE_STAGE_FLAG_BITS_MAX_ENUM
};

enum class CommandBufferLevel : std::uint32_t
{
	Primary = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
	Secondary = VK_COMMAND_BUFFER_LEVEL_SECONDARY,
	MaxEnum = VK_COMMAND_BUFFER_LEVEL_MAX_ENUM
};

enum class EDescriptorType
{
	Sampler = VK_DESCRIPTOR_TYPE_SAMPLER,
	CombinedImageSampler = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
	SampledImage = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
	StorageImage = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
	UniformTexelBuffer = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER,
	StorageTexelBuffer = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,
	UniformBuffer = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
	StorageBuffer = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
	UniformBufferDynamic = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
	StorageBufferDynamic = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC,
	InputAttachment = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,
	InlineUniformBlock = VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT,
	AccelerationStructure = VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR,
	MutableValue = VK_DESCRIPTOR_TYPE_MUTABLE_VALVE,
	None = VK_DESCRIPTOR_TYPE_MAX_ENUM
};

_KANAS_CORE_END


void Test()
{
	kanas::core::access_flags().set_host_read().get();

	kanas::core::query_pipeline_statistic_flags().set_compute_shader_invocations().get();
	kanas::core::query_control_flags().set_precise();

	std::ifstream f("example.json");
	nlohmann::json json_data = nlohmann::json::parse(f);
}

#endif
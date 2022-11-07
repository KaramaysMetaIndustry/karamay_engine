#include "pipeline.h"
#include "pipeline_cache.h"
#include "pipeline_layout.h"
#include "buffer.h"
#include "pooled_object/command_buffer.h"
#include "shader_module.h"

graphics_pipeline::graphics_pipeline(device& dev) : pipeline(dev)
{
}

graphics_pipeline::~graphics_pipeline()
{
    deallocate();
}

bool graphics_pipeline::allocate(pipeline_cache* cache, pipeline_layout* layout)
{
    VkGraphicsPipelineCreateInfo _create_info;
    _create_info.sType;

    auto _ret = vkCreateGraphicsPipelines(_dev.handle(), cache->handle(), 1, &_create_info, nullptr, &_handle);

    if (_ret != VkResult::VK_SUCCESS)
    {
        return false;
    }
    return true;
}

void graphics_pipeline::draw(command_buffer* recorder, uint32 vertex_count, uint32 instance_count, uint32 first_vertex, uint32 first_instance)
{
    vkCmdDraw(recorder->handle(), vertex_count, instance_count, first_vertex, first_instance);
}

void graphics_pipeline::draw_indirect(command_buffer* recorder, buffer* buf, uint64 size, uint32 draw_count, uint32 stride)
{
    vkCmdDrawIndirect(recorder->handle(), buf->handle(), size, draw_count, stride);
}

void graphics_pipeline::draw_indirect_count(command_buffer* recorder, buffer* buf, uint64 offset, buffer* count_buf, uint64 count_offset, uint32 max_draw_count, uint32 stride)
{
    vkCmdDrawIndirectCount(recorder->handle(), buf->handle(), offset, count_buf->handle(), count_offset, max_draw_count, stride);
}

void graphics_pipeline::draw_indexed(command_buffer* recorder, uint32 index_count, uint32 instance_count, uint32 first_index, int32 vertex_offset, uint32 first_instance)
{
    vkCmdDrawIndexed(recorder->handle(), index_count, instance_count, first_index, vertex_offset, first_instance);
}

void graphics_pipeline::draw_indexed_indirect(command_buffer* recorder, buffer* buf, uint64 offset, uint32 draw_count, uint32 stride)
{
    vkCmdDrawIndexedIndirect(recorder->handle(), buf->handle(), offset, draw_count, stride);
}

void graphics_pipeline::draw_indexed_indirect_count(command_buffer* recorder, buffer* buf, uint64 offset, buffer* count_buf, uint64 count_offset, uint32 max_draw_count, uint32 stride)
{
    vkCmdDrawIndexedIndirectCount(recorder->handle(), buf->handle(), offset, count_buf->handle(), count_offset, max_draw_count, stride);
}

ray_tracing_pipeline::ray_tracing_pipeline(device& dev) : pipeline(dev)
{
}

ray_tracing_pipeline::~ray_tracing_pipeline()
{
}

#include "deferred_operation.h"
#include "Pipeline.h"
#include "Pipeline.h"

bool ray_tracing_pipeline::allocate(pipeline_cache* cache, pipeline_layout* layout, deferred_operation* deferred_op, uint32 max_ray_recursion_depth)
{
    VkRayTracingPipelineCreateInfoKHR _create_info;
    _create_info.sType = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_KHR;
    _create_info.maxPipelineRayRecursionDepth = max_ray_recursion_depth;
    _create_info.layout;
    _create_info.pStages;
    _create_info.stageCount;
    _create_info.flags;
    _create_info.groupCount;
    _create_info.pGroups;
    _create_info.pDynamicState;
    _create_info.pLibraryInfo;
    _create_info.pLibraryInterface;

    device_khr_func(vkCreateRayTracingPipelinesKHR)(_dev.handle(), deferred_op->handle(), cache->handle(), 1, &_create_info, nullptr, &_handle);

    return false;
}

void ray_tracing_pipeline::trace_rays(command_buffer* recorder, uint32 width, uint32 height, uint32 depth)
{
    VkStridedDeviceAddressRegionKHR _raygen_shader_binding_table;
    _raygen_shader_binding_table.deviceAddress;
    _raygen_shader_binding_table.size;
    _raygen_shader_binding_table.stride;
    VkStridedDeviceAddressRegionKHR _miss_shader_binding_table;
    VkStridedDeviceAddressRegionKHR _hit_shader_binding_table;
    VkStridedDeviceAddressRegionKHR _callable_shader_binding_table;
    device_khr_func(vkCmdTraceRaysKHR)(
        recorder->handle(), 
        &_raygen_shader_binding_table, 
        &_miss_shader_binding_table, 
        &_hit_shader_binding_table, 
        &_callable_shader_binding_table, 
        width, height, depth
    );
}

void ray_tracing_pipeline::trace_rays_indirect(command_buffer* recorder)
{
    VkStridedDeviceAddressRegionKHR _raygen_shader_binding_table;
    _raygen_shader_binding_table.deviceAddress;
    _raygen_shader_binding_table.size;
    _raygen_shader_binding_table.stride;
    VkStridedDeviceAddressRegionKHR _miss_shader_binding_table;
    VkStridedDeviceAddressRegionKHR _hit_shader_binding_table;
    VkStridedDeviceAddressRegionKHR _callable_shader_binding_table;

    VkDeviceAddress _add;

    device_khr_func(vkCmdTraceRaysIndirectKHR)(
        recorder->handle(),
        &_raygen_shader_binding_table,
        &_miss_shader_binding_table,
        &_hit_shader_binding_table,
        &_callable_shader_binding_table,
        _add
    );
}

bool mesh_pipeline::allocate(pipeline_cache* cache, pipeline_layout* layout)
{
    VkGraphicsPipelineCreateInfo _create_info;
    return false;
}

void mesh_pipeline::draw(command_buffer* recorder, uint32 task_count, uint32 first_task)
{
    device_khr_func(vkCmdDrawMeshTasksNV)(recorder->handle(), task_count, first_task);
}

void mesh_pipeline::draw_indirect(command_buffer* recorder, buffer* buf, uint64 size, uint32 draw_count, uint32 stride)
{
    device_khr_func(vkCmdDrawMeshTasksIndirectNV)(recorder->handle(), buf->handle(), size, draw_count, stride);
}

void mesh_pipeline::draw_indirect_count(command_buffer* recorder)
{
    //device_khr_func(vkCmdDrawMeshTasksIndirectCountNV)(recorder->handle(), )
}

compute_pipeline::compute_pipeline(device& dev) : pipeline(dev)
{
}

compute_pipeline::~compute_pipeline()
{
}

bool compute_pipeline::allocate(pipeline_cache* cache, pipeline_layout* layout, shader_module* compute_shader_module)
{
    if (!cache || !layout || !compute_shader_module)
    {
        return false;
    }

    VkPipelineShaderStageCreateInfo _shader_stage_create_info;
    _shader_stage_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    _shader_stage_create_info.flags;
    _shader_stage_create_info.module = compute_shader_module->handle();
    _shader_stage_create_info.pName = "main";
    _shader_stage_create_info.pSpecializationInfo = nullptr;
    _shader_stage_create_info.stage = VkShaderStageFlagBits::VK_SHADER_STAGE_COMPUTE_BIT;

    VkComputePipelineCreateInfo _create_info;
    _create_info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
    _create_info.flags;
    _create_info.layout = layout->handle();
    _create_info.stage = _shader_stage_create_info;
    VkResult _result = vkCreateComputePipelines(_dev.handle(), cache->handle(), 1, &_create_info, nullptr, &_handle);
    
    if (_result != VkResult::VK_SUCCESS)
    {
        return false;
    }
    return true;
}

void compute_pipeline::dispatch(command_buffer* recorder, uint32 group_count_x, uint32 group_count_y, uint32 group_count_z)
{
    vkCmdDispatch(recorder->handle(), group_count_x, group_count_y, group_count_z);
}

void compute_pipeline::dispatch_base(command_buffer* recorder, uint32 base_group_x, uint32 base_group_y, uint32 base_group_z, uint32 group_count_x, uint32 group_count_y, uint32 group_count_z)
{
    vkCmdDispatchBase(recorder->handle(), base_group_x, base_group_y, base_group_z, group_count_x, group_count_y, group_count_z);
}

void compute_pipeline::dispatch_indirect(command_buffer* recorder, buffer* buf, uint64 size)
{
    vkCmdDispatchIndirect(recorder->handle(), buf->handle(), size);
}

pipeline::pipeline(device& dev) : device_object(dev)
{
}

pipeline::~pipeline()
{
    deallocate();
}

void pipeline::deallocate()
{
    if (_handle)
    {
        vkDestroyPipeline(_dev.handle(), _handle, nullptr);
        _handle = nullptr;
    }
}

void pipeline::bind(command_buffer* recorder, VkPipelineBindPoint bind_point)
{
    vkCmdBindPipeline(recorder->handle(), bind_point, _handle);
}



#include "pipeline.h"
#include "pipeline_cache.h"
#include "pipeline_layout.h"

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

    auto _ret = vkCreateGraphicsPipelines(_device.handle(), cache->handle(), 1, &_create_info, nullptr, &_handle);

    if (_ret != VkResult::VK_SUCCESS)
    {
        return false;
    }
    return true;
}

void graphics_pipeline::draw(command_buffer* recorder, uint32 vertex_count, uint32 instance_count, uint32 first_vertex, uint32 first_instance)
{
}

bool ray_tracing_pipeline::allocate(pipeline_cache* cache, pipeline_layout* layout, uint32 max_ray_recursion_depth)
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

    //vkCreateRayTracingPipelinesKHR(_device.handle(), {}, cache->handle(), 1, &_create_info, nullptr, &_handle);

    return false;
}

void ray_tracing_pipeline::trace_rays(command_buffer* recorder)
{
}

void ray_tracing_pipeline::trace_rays_indirect(command_buffer* recorder)
{
}

bool mesh_pipeline::allocate(pipeline_cache* cache, pipeline_layout* layout)
{
    VkGraphicsPipelineCreateInfo _create_info;


    return false;
}

void mesh_pipeline::draw(command_buffer* recorder)
{
}

void mesh_pipeline::draw_indirect(command_buffer* recorder)
{
}

bool compute_pipeline::allocate(pipeline_cache* cache, pipeline_layout* layout)
{
    VkComputePipelineCreateInfo _create_info;

    return false;
}

pipeline::pipeline(device& dev) : device_object(dev)
{
}

void pipeline::deallocate()
{
    vkDestroyPipeline(_device.handle(), _handle, nullptr);
    _handle = nullptr;
}

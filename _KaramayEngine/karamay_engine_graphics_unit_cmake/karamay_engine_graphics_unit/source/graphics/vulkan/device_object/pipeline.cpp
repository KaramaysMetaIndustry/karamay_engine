#include "pipeline.h"

bool graphics_pipeline::allocate(pipeline_cache* cache, pipeline_layout* layout)
{
    return false;
}

void graphics_pipeline::deallocate()
{
}

bool ray_tracing_pipeline::allocate(pipeline_cache* cache, pipeline_layout* layout)
{
    return false;
}

void ray_tracing_pipeline::deallocate()
{
}

void ray_tracing_pipeline::trace_rays(command_buffer* recorder)
{
}

void ray_tracing_pipeline::trace_rays_indirect(command_buffer* recorder)
{
}

bool mesh_pipeline::allocate(pipeline_cache* cache, pipeline_layout* layout)
{
    return false;
}

void mesh_pipeline::deallocate()
{
}

void mesh_pipeline::draw(command_buffer* recorder)
{
}

void mesh_pipeline::draw_indirect(command_buffer* recorder)
{
}

bool compute_pipeline::allocate(pipeline_cache* cache, pipeline_layout* layout)
{
    return false;
}

void compute_pipeline::deallocate()
{
}
